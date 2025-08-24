ARCH=arm64 LDFLAGS=-L/tmp/drm-static/lib/ \
CFLAGS='-I/tmp/drm-static/include -D__ANDROID__ -I/usr/android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/ -I/home/user/sources/platform_system_core/libcutils/include_outside_system/' \
CC=/usr/android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android33-clang \
make
