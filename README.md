# Android MiniGBM

This repo is clone from Android repo main branch[1] and with my own change to make it
out-of-tree build by meson. For further info about Mesa3D Vulkan driver please refer to [4] for github action prebuilt binary.

## Caution
This is for only compile test. Not tested with actual device, dont use for daily drive.

## Intro
There are some changes added without modify any of original code.
Inorder to make the library works with Android 14+ with Mapper V5 stable-c api,
Mapper.cpp is also compiled into main library. If there is no other user,
The library itself can work under mapper.minigbm_msm.so domain.

The Makefile itself is for built Linux and easily for cross build. \
The meson is explicitly for Android oot build. Especially for below:

- gralloc.minigbm.so
- gralloc.minigbm_msm.so
...and many...

## Further work
- There is possible to compile ndk and without vndk but not go into deep. 
- Test it with AOSP and MSM phone device is prefereable. 
- There are possibly components, feel free to add into meson.build file.
- Pack them into as an apex file and let install easy like adb install minigbm.apex
- Pack mesa3d vulkan driver as apex file as well then we can use AOSP/LineageOS build easily.

## Compile
Before compile minigbm, libdrm is needed as libdrm.a this case.
> - git clone https://gitlab.freedesktop.org/mesa/drm.git --depth=1 
> - cd drm 
> - wget https://github.com/99degree/android-mesa-build/raw/refs/heads/master/android-drm-aarch64 
> - meson setup "build-android" \ \
            --prefix=/tmp/drm-static \ \
            --cross-file "android-drm-aarch64" \ \
            -Ddefault_library=static \ \
            -Dintel=disabled \ \
            -Dradeon=disabled \ \
            -Damdgpu=disabled \ \
            -Dnouveau=disabled \ \
            -Dvmwgfx=disabled \ \
            -Dfreedreno=enabled \ \
            -Dvc4=disabled \ \
            -Detnaviv=disabled \ \
            -Dfreedreno-kgsl=true
>  - ninja -C "build-android" install

This is for compiling exclusively *MSM/QCOM* platform. Other platform change above accordingly.

You also need to modify the ndk/vndk location too. 
> curl https://dl.google.com/android/repository/android-ndk-r27d-linux.zip --output android-ndk-r27d-linux.zip &> /dev/null \
> echo "Extracting android-ndk to a folder ..."  \
> unzip android-ndk-r27d-linux.zip &> /dev/null  \
> sudo mv -r android-ndk-r27d /usr/

Since vndk is tricky, so below is just for reference:\
>  git clone -b sdk-release --depth=1 https://android.googlesource.com/platform/prebuilts/vndk/v34

Assumed Android-ndk is installed into /usr/android-ndk-r27d/
>  mkdir -p /usr/android-ndk-r27d/prebuilt/vndk
>  cp v34 /usr/android-ndk-r27d/prebuilt/vndk -r
>  ls

Mine is looked like below since I checked out vndk v30 to v34
> ls /usr/android-ndk-r27d/prebuilt/vndk/  \
> v30  v31  v32  v33  v34

To start compile, type below or just directly checkout my tree:
>  git clone -b main --depth 6 https://android.googlesource.com/platform/external/minigbm \
>  cd minigbm \
>  git add remote 99degree \
>  git fetch 99degree local-main \
>  git merge 99degree/local-main \
>  wget https://github.com/99degree/android-mesa-build/raw/refs/heads/master/android-aarch64  \

Make change to cross build file android-aarch64, those ndk path etc are needed to change.
>  meson setup build-android --prefix=/tmp/minigbm -Dextra_include=/tmp/drm-static/ --cross-file  android-aarch64 \
>  ninja -C build-android install

_OR_ if your NDK is located at /usr/share/android-ndk-r27d/ then you can add meson option -Dndk_include as below:
> meson setup build-android
>    -Dndk_include=/usr/share/android-ndk-r27d/ \ \
>    --prefix=/tmp/minigbm \ \
>    -Dextra_include=/tmp/drm-static/ \ \
>    --cross-file  android-aarch64 \ \
> ninja -C build-android install

_AND_ vndk has to be in this arrangement:
> SOME_FOLDER/android-ndk-r27d/prebuilt/vndk/v34


So all generated library is located at /tmp/minigbm/lib/

According to Google AOSP decision, the minigbm repo might have some arrangement \
that main is not the latest one, please check. Also above merge maybe fail but \
if fetch depth > 30 possibly fix the merge problem.

Meson build will generate for all platform as individual library but it \
statically link with *msm/qcom* + generic backend libdrm only so this is \
a potential problem. Fix it by enable all platform for libdrm above.

### Generated files
Listed below are generated files, rename it for use case. Dont for get to use \
patchelf to change so name. Or possibly modify meson.build for a proper name.

- libgbm.so
- libgralloc.minigbm.so
- libgralloc.minigbm_arcvm.so
- libgralloc.minigbm_meson.so
- libgralloc.minigbm_msm.so
- libminigbm_gralloc.so
- libminigbm_gralloc_arcvm.so
- libminigbm_gralloc_meson.so
- libminigbm_gralloc_msm.so

Generally speaking libminigbm_gralloc_msm.so is the one for use. Look at its \
size tells the main body of minigbm is lived inside this library. With the \
IMapper V5 stable-c api, this library can directly used as vendor mapper library \
for Android 14+ so make it mapper.minigbm_msm.so as best pratice.

Some tools are needed:
-    vndk34, url[2]
-    android-ndk, prefer r27d [3]
-    some ordinary linux tools:
>    libxrandr-dev libxxf86vm-dev libxcb-*-dev libx11-xcb-dev libxfixes-dev libdrm-dev libx11-dev
>    glslang-tools libclc-18-dev libclc-18 gcc-13-aarch64-linux-gnu

Note: 
- ndk r27c is not android 14+ compatible, so ndk r27d LTS is prefered.
- vndk 34 is last one support out-of-tree build and first one to introduce Mapper5 stable-c api

## Install
From Copilot, below is needed once to use it:
> setprop debug.mapper.impl minigbm

Then patch libminigbm_gralloc.so with mapper.minigbm.so as so name then rename it.

Since the library have generic backend and msm backend so for msm device:
> setprop debug.mapper.impl minigbm_msm

Or patch libminigbm_gralloc_msm.so with mapper.minigbm_msm.so as so name then rename it.

Supposed to use libminigbm_gralloc_msm.so and patchelf with mapper.minigbm.so is \
best option for both generic(emulator) and msm device. And debug.mapper.impl with minigbm \
Such that will fall back to generic backend if not msm device.

This mapper.minigbm_msm.so can be either in /vendor/lib64/hw/ or /odm/lib64/hw/
The odm path is prefereable since creating odm dynamic partition is easy and small enough \
to flash and need not modify vendor partition. Resently custom ROM odm partition are nearly empty ;)

Dont forget to add mapper.minigbm.xml to vintf/

## Reference
[1]https://android.googlesource.com/platform/external/minigbm/+/refs/heads/main \
[2]https://android.googlesource.com/platform/prebuilts/vndk/v34/ \
[3]https://dl.google.com/android/repository/android-ndk-r27d-linux.zip
[4]https://github.com/99degree/android-mesa-build/actions/
