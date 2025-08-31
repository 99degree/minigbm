#ARCH=arm64 LDFLAGS=-L/tmp/drm-static/lib/ \
#CFLAGS='-I/tmp/drm-static/include -D__ANDROID__ -I/usr/android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/ -I/home/user/sources/platform_system_core/libcutils/include_outside_system/' \
#CC=/usr/android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android33-clang \
#make

#rm /tmp/minigbm/lib/*.a
#rm /tmp/minigbm/lib/*.so
#find -name "*.so" -exec rm {} \;
#find -name "*.a" -exec rm {} \;
#find -name "libgallium_dri.*" -exec rm -r {} \;

#
#	-Ddrivers=msm

#  meson compile -C build-android minigbm_gralloc minigbm_gralloc_intel minigbm_gralloc_meson minigbm_gralloc_msm
#        -Ddefault_library=static \


# must build shared library first otherwise the binary linked with internal
# library will be shared. but that is not very handy in android case.
# supposed to have executable bin linked to sys lib only.
# dont introduce the shared library with internal lib as is.
# so shared lib like the mapper5 stable-c is shared library and best is to make
# if shared lib and build first.

# then we rebuild for all with static lib for libdrm and minigbm itself.
# such that the execute binary dont rely on minigbm shared lib so file.
    meson setup --reconfigure "build-android" \
        --prefix=/tmp/minigbm \
        --cross-file "../build-crossfile" \
        -Dndk_root=/usr/android-ndk-r27d/ \
        --force-fallback-for=libdrm \
        -Dlibdrm:default_library=static \
        -Dlibdrm:freedreno-kgsl=true \
        -Dlibdrm:intel=auto \
        -Dlibdrm:radeon=auto \
        -Dlibdrm:amdgpu=auto \
        -Dlibdrm:nouveau=auto \
        -Dlibdrm:vmwgfx=enabled \
        -Dlibdrm:omap=enabled \
        -Dlibdrm:freedreno=enabled \
        -Dlibdrm:tegra=enabled \
        -Dlibdrm:etnaviv=enabled \
        -Dlibdrm:exynos=enabled \
        -Dlibdrm:vc4=enabled

          ninja -C "build-android" install
