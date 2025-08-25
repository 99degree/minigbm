##### TRUNK 1 START: Project setup, includes, common vars, and source groups #####

# Copyright George Chan gchan9527@gmail.com
# Use of this source code is governed by a BSD-style license.

project('minigbm', ['c', 'cpp'],
  version: '1.1.0',
  default_options: ['c_std=c99', 'cpp_std=c++20', 'warning_level=2']
)

ndk_root = get_option('ndk_root')
if ndk_root == ''
  ndk_root = meson.get_external_property('ndk_root', '')
endif

if ndk_root == ''
  error('You must set ndk_root either in the cross file or with -Dndk_root=...')
endif

# Define all available drivers in one place
_all_drivers = [
  'amdgpu', 'i915', 'xe', 'meson', 'msm', 'vc4',
  'mediatek', 'rockchip', 'virtgpu', 'radeon', 'arcvm', 'generic', 'intel'
]

# Read the option from meson_options.txt (or fallback to default)
drivers = get_option('drivers')
if drivers.length() == 0
  drivers = _all_drivers
endif

cpu_family = host_machine.cpu_family()

# === Include directories ===
inc = include_directories('.')

# Extended include paths for Android VNDK v34
# Each path below has a comment describing what headers it provides
inc_extra_v34 = include_directories(
  # android-base/unique_fd.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/libbase/include/'),
  # system/core/libsystem/
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libsystem/'),
  # hardware/gralloc.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/hardware/libhardware/include/'),
  # system/graphics-base-v1.0.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libsystem/include/'),
  # sync/sync.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libsync/include'),
  # libvndksupport
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libvndksupport/include'),
  # libsysutils
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libsysutils/'),
  # graphics.common-V4 AIDL headers
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/aidl/android.hardware.graphics.common-V4-ndk-source/gen/include/'),
  # libcutils
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libcutils/include'),
  # log/log.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/logging/liblog/include_vndk/'),
  # BufferDescriptorInfo.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/allocator/aidl/android.hardware.graphics.allocator-V2-ndk-source/gen/include/'),
  # graphics.common@1.2
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/1.2/android.hardware.graphics.common@1.2_genc++_headers/gen/'),
  # graphics.common@1.1
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/1.1/android.hardware.graphics.common@1.1_genc++_headers/gen/'),
  # graphics.common@1.0
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/1.0/android.hardware.graphics.common@1.0_genc++_headers/gen/'),
  # Hidlsupport.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/libhidl/base/include/'),
  # utils/Error.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/core/libutils/include'),
  # fmq/MQDescriptorBase.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/libfmq/base/'),
  # IMapper 4.0
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/mapper/4.0/android.hardware.graphics.mapper@4.0_genc++_headers/gen/'),
  # IBase 1.0
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/system/libhidl/transport/base/1.0/android.hidl.base@1.0_genc++_headers/gen/'),
  # IServiceNotification 1.0
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/system/libhidl/transport/manager/1.0/android.hidl.manager@1.0_genc++_headers/gen/'),
  # gralloctypes/Gralloc4.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/gralloc/types/include/'),
  # system/window.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/nativewindow/include/'),
  # nativebase.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/nativebase/include/'),
  # local shim includes
  join_paths('.', 'include/stable-c-v34/include'),
  join_paths('.', 'include/stable-c-v34/implutils/include/')
)

if target_machine.system() == 'android'
  inc_extra = inc_extra_v34
else
  inc_extra = []
endif

# === Common flags and settings ===
common_cflags = [
  '-D_GNU_SOURCE=1',
  '-D_FILE_OFFSET_BITS=64',
  '-Wall', '-Wsign-compare', '-Wpointer-arith', '-Wcast-qual', '-Wcast-align',
  '-Wno-unused-parameter'
]

generic_cflags = ['-DHAS_DMABUF_SYSTEM_HEAP']
intel_cflags   = ['-DDRV_I915', '-DDRV_XE']
meson_cflags   = ['-DDRV_MESON']
msm_cflags     = ['-DDRV_MSM', '-DQCOM_DISABLE_COMPRESSED_NV12', '-DHAS_DMABUF_SYSTEM_HEAP']
arcvm_cflags   = ['-DVIRTIO_GPU_NEXT']

common_link_args = ['-Wl,--unresolved-symbols=ignore-all']

# Try to find system libdrm first, fall back to subproject if missing
libdrm_dep = dependency(
  'libdrm',
  version: '>=2.4.100',
  required: false,
  fallback: ['libdrm', 'libdrm_dep'],
  static: true
)

common_deps = [
  libdrm_dep,
  dependency('libcutils', required: false),
  dependency('liblog', required: false)
]

# === Common source groups ===
core_sources = files(
  'amdgpu.c',
  'backend_mock.c',
  'drv.c',
  'drv_array_helpers.c',
  'drv_helpers.c',
  'dumb_driver.c',
  'mediatek.c',
  'msm.c',
  'rockchip.c',
  'vc4.c',
  'virtgpu.c',
  'virtgpu_cross_domain.c',
  'virtgpu_virgl.c',
  'xe.c'
)

gralloc_common_sources = files(
  'cros_gralloc/cros_gralloc_buffer.cc',
  'cros_gralloc/cros_gralloc_driver.cc',
  'cros_gralloc/cros_gralloc_helpers.cc',
  'cros_gralloc/mapper_stablec/Mapper.cpp'
)

gralloc0_sources = files()  # currently empty

# === Dedicated per-target source groups ===
libgbm_sources                 = files('gbm.c', 'gbm_helpers.c', 'minigbm_helpers.c')
libminigbm_gralloc_sources     = files()
gralloc_minigbm_sources        = files()

libminigbm_gralloc_intel_sources = files('i915.c')  # Intel-specific
gralloc_minigbm_intel_sources    = files()

libminigbm_gralloc_meson_sources = files()
gralloc_minigbm_meson_sources    = files()

libminigbm_gralloc_msm_sources   = files()
gralloc_minigbm_msm_sources      = files()

libminigbm_gralloc_arcvm_sources = files()
gralloc_minigbm_arcvm_sources    = files()

##### TRUNK 1 END #####
##### TRUNK 2 START: Target definitions using shared common_* variables #####

# === libgbm ===
libgbm = library('gbm',
  sources: core_sources + libgbm_sources,
  include_directories: [inc, inc_extra],
  c_args: common_cflags,
  link_args: common_link_args,
  dependencies: common_deps,
  install: true
)

# === Generic gralloc ===
libminigbm_gralloc = library('minigbm_gralloc',
  sources: core_sources + gralloc_common_sources + libminigbm_gralloc_sources,
  include_directories: [inc, inc_extra],
  c_args: common_cflags + generic_cflags,
  link_args: common_link_args,
  dependencies: common_deps,
  install: true
)

gralloc_minigbm = library('gralloc.minigbm',
  sources: gralloc0_sources + gralloc_minigbm_sources,
  include_directories: [inc, inc_extra],
  dependencies: [declare_dependency(link_with: libminigbm_gralloc)],
  link_args: common_link_args,
  install: true
)

# === Intel gralloc (x86/x86_64 only) ===
if 'intel' in drivers and cpu_family in ['x86', 'x86_64']
  libminigbm_gralloc_intel = library('minigbm_gralloc_intel',
    sources: core_sources + libminigbm_gralloc_intel_sources + gralloc_common_sources,
    include_directories: [inc, inc_extra],
    c_args: common_cflags + intel_cflags + ['-msse2'],
    link_args: common_link_args,
    dependencies: common_deps,
    install: true
  )

  gralloc_minigbm_intel = library('gralloc.minigbm_intel',
    sources: gralloc0_sources + gralloc_minigbm_intel_sources,
    include_directories: [inc, inc_extra],
    dependencies: [declare_dependency(link_with: libminigbm_gralloc_intel)],
    link_args: common_link_args,
    install: true
  )
endif

# === Meson gralloc ===
if 'meson' in drivers
  libminigbm_gralloc_meson = library('minigbm_gralloc_meson',
    sources: core_sources + libminigbm_gralloc_meson_sources + gralloc_common_sources,
    include_directories: [inc, inc_extra],
    c_args: common_cflags + meson_cflags,
    link_args: common_link_args,
    dependencies: common_deps,
    install: true
  )

  gralloc_minigbm_meson = library('gralloc.minigbm_meson',
    sources: gralloc0_sources + gralloc_minigbm_meson_sources,
    include_directories: [inc, inc_extra],
    dependencies: [declare_dependency(link_with: libminigbm_gralloc_meson)],
    link_args: common_link_args,
    install: true
  )
endif

# === MSM gralloc ===
if 'msm' in drivers
  libminigbm_gralloc_msm = library('minigbm_gralloc_msm',
    sources: core_sources + libminigbm_gralloc_msm_sources + gralloc_common_sources,
    include_directories: [inc, inc_extra],
    c_args: common_cflags + msm_cflags,
    link_args: common_link_args,
    dependencies: common_deps,
    install: true
  )

  gralloc_minigbm_msm = library('gralloc.minigbm_msm',
    sources: gralloc0_sources + gralloc_minigbm_msm_sources,
    include_directories: [inc, inc_extra],
    dependencies: [declare_dependency(link_with: libminigbm_gralloc_msm)],
    link_args: common_link_args,
    install: true
  )
endif

##### TRUNK 2 END #####
##### TRUNK 3 START: ARCVM targets, header installs, and pkg-config #####

# === ARCVM gralloc ===
if 'arcvm' in drivers
  libminigbm_gralloc_arcvm = library('minigbm_gralloc_arcvm',
    sources: core_sources + libminigbm_gralloc_arcvm_sources + gralloc_common_sources,
    include_directories: [inc, inc_extra],
    c_args: common_cflags + arcvm_cflags,
    link_args: common_link_args,
    dependencies: common_deps,
    install: true
  )

  gralloc_minigbm_arcvm = library('gralloc.minigbm_arcvm',
    sources: gralloc0_sources + gralloc_minigbm_arcvm_sources,
    include_directories: [inc, inc_extra],
    dependencies: [declare_dependency(link_with: libminigbm_gralloc_arcvm)],
    link_args: common_link_args,
    install: true
  )
endif

# === Header installs ===
install_headers('gbm.h', subdir: '')
install_headers('minigbm_helpers.h', subdir: 'minigbm')
install_headers('cros_gralloc/cros_gralloc_buffer.h', subdir: 'cros_gralloc')

# === pkg-config file ===
pkgconf = configure_file(
  output: 'gbm.pc',
  configuration: {
    'prefix': get_option('prefix'),
    'includedir': join_paths(get_option('prefix'), get_option('includedir')),
    'libdir': join_paths(get_option('prefix'), get_option('libdir')),
    'version': meson.project_version()
  },
  input: 'gbm.pc.in'
)
install_data(pkgconf, install_dir: join_paths(get_option('libdir'), 'pkgconfig'))

##### TRUNK 3 END #####
