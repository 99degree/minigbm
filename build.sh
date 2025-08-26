#ARCH=arm64 LDFLAGS=-L/tmp/drm-static/lib/ \
#CFLAGS='-I/tmp/drm-static/include -D__ANDROID__ -I/usr/android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/ -I/home/user/sources/platform_system_core/libcutils/include_outside_system/' \
#CC=/usr/android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android33-clang \
#make

    meson  setup --reconfigure "build-android" \
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

#  meson compile -C build-android android.hardware.graphics.allocator-service.minigbm
#        -Ddefault_library=static \
          ninja -C "build-android" install
