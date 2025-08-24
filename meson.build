#
# Copyright George Chan gchan9527@gmail.com
#
project('minigbm', ['c', 'cpp'], version: '1.0', default_options: ['cpp_std=c++20'])

cpu_family = host_machine.cpu_family()

# Include directories
inc = include_directories('.')
extra_include = get_option('extra_include')
ndk_include = get_option('ndk_include')

# get-around ndk directory not as below but empty
if get_option('ndk_include') == ''
  ndk_include = '/usr/android-ndk-r27d/'
endif

inc_extra_v34 = include_directories(
#this is yet to verify
#  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/system/core/liblog/',
#  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/system/core/libhardware/',
#
# provide android-base/unique_fd.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/system/libbase/include/'),
# below are available for v34 sdk
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/system/core/libsystem/'),
# provide hardware/gralloc.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/hardware/libhardware/include/'),
# provide system/graphics-base-v1.0.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/system/core/libsystem/include/'),
# provide sync/sync.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/system/core/libsync/include'),
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/system/core/libvndksupport/include'),
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/system/core/libsysutils/'),
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/aidl/android.hardware.graphics.common-V4-ndk-source/gen/include/'), 
   join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/system/core/libcutils/include'),
# provide log/log.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/system/logging/liblog/include_vndk/'),
# missing BufferDescriptorInfo.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/allocator/aidl/android.hardware.graphics.allocator-V2-ndk-source/gen/include/'),
# 1.2/Type.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/1.2/android.hardware.graphics.common@1.2_genc++_headers/gen/'),
# 1.1/Type.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/1.1/android.hardware.graphics.common@1.1_genc++_headers/gen/'),
# 1.0/Type.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/1.0/android.hardware.graphics.common@1.0_genc++_headers/gen/'),
# Hidlsupport.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/system/libhidl/base/include/'),
# utils/Error.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/system/core/libutils/include'),
# fmq/MQDescriptorBase.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/system/libfmq/base/'),
# 4.0/IMapper.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/mapper/4.0/android.hardware.graphics.mapper@4.0_genc++_headers/gen/'),
# 1.0/IBase.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/generated-headers/system/libhidl/transport/base/1.0/android.hidl.base@1.0_genc++_headers/gen/'),
# 1.0/IServiceNotification.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/generated-headers/system/libhidl/transport/manager/1.0/android.hidl.manager@1.0_genc++_headers/gen/'),
# gralloctypes/Gralloc4.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/gralloc/types/include/'),
# system/window.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/nativewindow/include/'),
# nativebase.h
  join_paths(ndk_include, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/nativebase/include/'),
# 2-last thing is ndk
  join_paths(ndk_include, 'toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/'),
# last is our shim
  join_paths('.', 'include/'),
  join_paths(extra_include, 'include'),
  join_paths(extra_include, 'include/libdrm'),
  join_paths('.', 'include/stable-c-v34/include'),
  join_paths('.', 'include/stable-c-v34/implutils/include/'),
)

inc_extra = inc_extra_v34

# Platform-specific flags
generic_cflags = ['-DHAS_DMABUF_SYSTEM_HEAP']
intel_cflags = ['-DDRV_I915', '-DDRV_XE']
meson_cflags = ['-DDRV_MESON']
msm_cflags = ['-DDRV_MSM', '-DQCOM_DISABLE_COMPRESSED_NV12', '-DHAS_DMABUF_SYSTEM_HEAP']
arcvm_cflags = ['-DVIRTIO_GPU_NEXT']

# Core source files
core_sources = files(
  'amdgpu.c', 'backend_mock.c', 'drv.c', 'drv_array_helpers.c',
  'drv_helpers.c', 'dumb_driver.c', 'mediatek.c',
  'msm.c', 'rockchip.c', 'vc4.c', 'virtgpu.c',
  'virtgpu_cross_domain.c', 'virtgpu_virgl.c', 'xe.c'
)

special_source = files('i915.c')

gralloc_common_sources = files(
#  'mapper2/MiniGbmDriver.cpp',
#  'mapper2/MiniGbmDriver_meta.cpp',
#  'mapper2/MiniGbmMapperV5.cpp',
  'cros_gralloc/cros_gralloc_buffer.cc',
  'cros_gralloc/cros_gralloc_driver.cc',
  'cros_gralloc/cros_gralloc_helpers.cc',
  'cros_gralloc/mapper_stablec/Mapper.cpp'
#  'Mapper_ndk2.cpp'
)

gralloc0_sources = files(
#  'mapper2/Gralloc0MiniGbmWrapper.cpp',
#  'mapper2/Gralloc0MiniGbmWrapper_impl.cpp',
#   'cros_gralloc/gralloc0/gralloc0.cc',
)

# Dependencies
drm_dep = dependency('libdrm', static: true, method: 'pkg-config')
cutils_dep = dependency('libcutils', required: false)
log_dep = dependency('liblog', required: false)

# libgbm
libgbm = library('gbm',
  sources: core_sources + files('gbm.c', 'gbm_helpers.c', 'minigbm_helpers.c'),
  include_directories: [inc, inc_extra],
  dependencies: [drm_dep, cutils_dep, log_dep],
  link_args: ['-Wl,--unresolved-symbols=ignore-all'],
  install: true
)

# Generic gralloc
libminigbm_gralloc = library('minigbm_gralloc',
  sources: core_sources + gralloc_common_sources,
  include_directories: [inc, inc_extra],
  c_args: generic_cflags,
  dependencies: [drm_dep, cutils_dep, log_dep],
  link_args: ['-Wl,--unresolved-symbols=ignore-all'],
  install: true
)

libminigbm_gralloc_dep = declare_dependency(link_with: libminigbm_gralloc)

gralloc_minigbm = library('gralloc.minigbm',
  sources: gralloc0_sources,
  include_directories: [inc, inc_extra],
  dependencies: [libminigbm_gralloc_dep],
  link_args: ['-Wl,--unresolved-symbols=ignore-all'],
  install: true
)

# Intel gralloc (only for x86/x86_64)
if cpu_family == 'x86' or cpu_family == 'x86_64'
  libminigbm_gralloc_intel = library('minigbm_gralloc_intel',
    sources: core_sources + special_source + gralloc_common_sources,
    include_directories: [inc, inc_extra],
    c_args: intel_cflags + ['-msse2'],
    link_args: ['-Wl,--unresolved-symbols=ignore-all'],
    install: true
  )

  libminigbm_gralloc_intel_dep = declare_dependency(link_with: libminigbm_gralloc_intel)

  gralloc_minigbm_intel = library('gralloc.minigbm_intel',
    sources: gralloc0_sources,
    include_directories: inc,
    dependencies: [libminigbm_gralloc_intel_dep],
    link_args: ['-Wl,--unresolved-symbols=ignore-all'],
    install: true
  )
endif

# Meson gralloc
libminigbm_gralloc_meson = library('minigbm_gralloc_meson',
  sources: core_sources + gralloc_common_sources,
  include_directories: [inc, inc_extra],
  c_args: meson_cflags,
  link_args: ['-Wl,--unresolved-symbols=ignore-all'],
  install: true
)

libminigbm_gralloc_meson_dep = declare_dependency(link_with: libminigbm_gralloc_meson)

gralloc_minigbm_meson = library('gralloc.minigbm_meson',
  sources: gralloc0_sources,
  include_directories: [inc, inc_extra],
  dependencies: [libminigbm_gralloc_meson_dep],
  link_args: ['-Wl,--unresolved-symbols=ignore-all'],
  install: true
)

# MSM gralloc
libminigbm_gralloc_msm = library('minigbm_gralloc_msm',
  sources: core_sources + gralloc_common_sources,
  include_directories: [inc, inc_extra],
  c_args: msm_cflags,
  link_args: ['-Wl,--unresolved-symbols=ignore-all'],
  install: true
)

libminigbm_gralloc_msm_dep = declare_dependency(link_with: libminigbm_gralloc_msm)

gralloc_minigbm_msm = library('gralloc.minigbm_msm',
  sources: gralloc0_sources,
  include_directories: [inc, inc_extra],
  dependencies: [libminigbm_gralloc_msm_dep],
  link_args: ['-Wl,--unresolved-symbols=ignore-all'],
  install: true
)

# ARCVM gralloc
libminigbm_gralloc_arcvm = library('minigbm_gralloc_arcvm',
  sources: core_sources + gralloc_common_sources,
  include_directories: [inc, inc_extra],
  c_args: arcvm_cflags,
  link_args: ['-Wl,--unresolved-symbols=ignore-all'],
  install: true
)

libminigbm_gralloc_arcvm_dep = declare_dependency(link_with: libminigbm_gralloc_arcvm)

gralloc_minigbm_arcvm = library('gralloc.minigbm_arcvm',
  sources: gralloc0_sources,
  include_directories: inc,
  dependencies: [libminigbm_gralloc_arcvm_dep],
  link_args: ['-Wl,--unresolved-symbols=ignore-all'],
  install: true
)
