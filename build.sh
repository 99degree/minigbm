#ARCH=arm64 LDFLAGS=-L/tmp/drm-static/lib/ \
#CFLAGS='-I/tmp/drm-static/include -D__ANDROID__ -I/usr/android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/ -I/home/user/sources/platform_system_core/libcutils/include_outside_system/' \
#CC=/usr/android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android33-clang \
#make

    meson setup "build-android" \
	--prefix=/tmp/mesa \
	--cross-file "../build-crossfile" \
	-Ddefault_library=static \
	-Dndk_include=/usr/android-ndk-r27d/ \
	--force-fallback-for=libdrm \
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
