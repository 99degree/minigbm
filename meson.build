##### TRUNK 1 START: Project setup, includes, common vars, and source groups #####

# Copyright George Chan gchan9527@gmail.com
# Use of this source code is governed by a BSD-style license.

project('minigbm', ['c', 'cpp'],
  version: '1.1.0',
  default_options: ['c_std=c99', 'cpp_std=c++20', 'warning_level=2']
)

cc = meson.get_compiler('c')

cpu_map = {
  'arm':     'arch-arm-armv7-a-neon',
  'aarch64': 'arch-arm64-armv8-a',
  'x86':     'arch-x86',
  'x86_64':  'arch-x86_64'
}

cpu_family = host_machine.cpu_family()

# Cosmetic rename for display (optional)
cpu_name = (cpu_family == 'aarch64') ? 'arm64' : cpu_family

inst_name = cpu_map.get(cpu_family, '')

message('CPU name: ' + cpu_name)
message('Instruction dir: ' + inst_name)

ndk_root = get_option('ndk_root')
if ndk_root == ''
  ndk_root = meson.get_external_property('ndk_root', '')
endif

if ndk_root == ''
  error('You must set ndk_root either in the cross file or with -Dndk_root=...')
endif

# Usually mapper5 stable-c only available for v34
sdk_ver = meson.get_external_property('sdk_ver', '')
message('sdk_ver: ' + sdk_ver)

if sdk_ver == ''
  sdk_ver = meson.get_external_property('SDK_VER', '')
  message('sdk_ver: ' + sdk_ver)
endif

if sdk_ver == ''
  sdk_ver = get_option('sdk_ver')
  message('sdk_ver: ' + sdk_ver)
endif

if sdk_ver == ''
  sdk_ver = get_option('SDK_VER')
  message('sdk_ver: ' + sdk_ver)
endif

if sdk_ver == '' 
    error('You must set SDK_VER/sdk_ver either in the cross file or with -Dsdk_ver=... OR -Dsdk_VER=...')
endif

# For Same Process like mapper

# Supposed vndk is checkout at below
#./usr/android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/aarch64-linux-android/27/libz.so
#./usr/android-ndk-r27d/prebuilt/vndk/v30/x86_64/arch-x86_64/shared/vndk-core/android.hardware.graphics.allocator@4.0.so
vndk_sp = join_paths(ndk_root,'prebuilt/vndk/', 'v' + sdk_ver, cpu_name, inst_name,'shared/vndk-sp/')
message('vndk_sp: ' + vndk_sp)

vndk_llndk_stub = join_paths(ndk_root,'prebuilt/vndk/', 'v' + sdk_ver, cpu_name, inst_name,'shared/llndk-stub/')
vndk_core = join_paths(ndk_root,'prebuilt/vndk/', 'v' + sdk_ver, cpu_name, inst_name,'shared/vndk-core/')

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
  #
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/common/aidl/android.hardware.common-V2-ndk-source/gen/include/'),
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/frameworks/native/libs/binder/ndk/include_platform/'),
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/allocator/4.0/android.hardware.graphics.allocator@4.0_genc++_headers/gen/'),
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/generated-headers/hardware/interfaces/graphics/common/aidl/android.hardware.graphics.common-V4-ndk-source/gen/include/'),
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/libhidl/transport/include/'),

  # framework and libhwbinder both have IBinder.h
  join_paths(ndk_root, 'prebuilt/vndk/v34/arm64/include/system/libhwbinder/include/'),
  # local shim includes
  join_paths('.', 'include/stable-c-v34/include'),
  join_paths('.', 'include/stable-c-v34/implutils/include/'),
  join_paths('.', 'include/')
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

common_link_args = []
nosym_link_args = [
  '-Wl,-rpath,' + vndk_sp,
  '-Wl,-rpath,' + vndk_llndk_stub,
]
#nosym_link_args = ['-Wl,--unresolved-symbols=ignore-all']
#common_link_args = ['-Wl,--unresolved-symbols=ignore-all']

# Try to find system libdrm first, fall back to subproject if missing
libdrm_dep = dependency(
  'libdrm',
  version: '>=2.4.100',
  required: true,
  fallback: ['libdrm', 'libdrm_dep'],
  static: true
)

liblog_dep = cc.find_library(
  'liblog',
  required: true,
)

# Leave it here once replace NDK version we can remove it.
# needs property_get
libcutils_dep = cc.find_library(
  'libcutils',
  required: true,
  dirs: [vndk_llndk_stub, vndk_sp, vndk_core]
)

# The libraries you want to look up
libnames = ['libnativewindow', 'libsync']

# Too bad libsync dont have sync_wait in NDK version.
# This file depends on Mapper@4.0 and many more....actually can
# eliminate them to have a true NDK build
if sdk_ver >= '34'
  libnames += 'libcutils'
  libnames += 'libgralloctypes'
  libnames += 'libhidlbase'
endif

# Start with any existing deps
common_deps = [libdrm_dep, liblog_dep]

# Add results from find_library for each name
foreach libname : libnames
  dep = cc.find_library(libname,
    required: true,
    dirs: [vndk_llndk_stub, vndk_sp, vndk_core]
  )
  if dep.found()
    common_deps += dep
  endif
endforeach

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

cros_gralloc_common_sources = files(
  'cros_gralloc/cros_gralloc_buffer.cc',
  'cros_gralloc/cros_gralloc_driver.cc',
  'cros_gralloc/cros_gralloc_helpers.cc',
)

mapper5_common_source = []

# Only add Mapper5 stable-c API for sdk v34
# This file depends on Mapper@4.0
if sdk_ver >= '34'
  mapper5_common_source = files(
    'cros_gralloc/mapper_stablec/Mapper.cpp',
  )
endif

if sdk_ver == '34'
  mapper5_common_source = files(
    'cros_gralloc/mapper_stablec/Plane.cpp',
    'cros_gralloc/String_shim.cpp',
  )
endif

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

# === global define ===
libminigbm_gralloc = []
libminigbm_gralloc_intel = []
libminigbm_gralloc_meson = []
libminigbm_gralloc_msm = []
libminigbm_gralloc_arcvm = []

# === libgbm ===
libgbm = library('gbm',
  sources: core_sources + libgbm_sources,
  include_directories: [inc, inc_extra],
  c_args: common_cflags,
  link_args: [common_link_args, nosym_link_args],
  dependencies: [libdrm_dep, liblog_dep, libcutils_dep],
  install: true
)

####### from now on it will add Mapper5 into main lib.

# === Generic gralloc ===
libminigbm_gralloc = library('minigbm_gralloc',
  sources: [core_sources, cros_gralloc_common_sources,
		mapper5_common_source, libminigbm_gralloc_sources],
  include_directories: [inc, inc_extra],
  c_args: common_cflags + generic_cflags,
  link_args: [common_link_args, nosym_link_args],
  dependencies: common_deps,
  install: true,
  install_dir : join_paths(get_option('libdir'), 'hw')
)

# === Mapper use this dep ===
libminigbm_gralloc_dep = declare_dependency(
  link_with : libminigbm_gralloc,
#  include_directories : inc_minigbm
)

gralloc_minigbm = library('gralloc.minigbm',
  sources: gralloc0_sources + gralloc_minigbm_sources,
  include_directories: [inc, inc_extra],
  dependencies: [declare_dependency(link_with: libminigbm_gralloc)],
  link_args: common_link_args,
  install: true,
  install_dir : join_paths(get_option('libdir'), 'hw')
)

# === Intel gralloc (x86/x86_64 only) ===
if 'intel' in drivers and cpu_family in ['x86', 'x86_64']
  libminigbm_gralloc_intel = library('minigbm_gralloc_intel',
    sources: [
		core_sources,
		libminigbm_gralloc_intel_sources,
		cros_gralloc_common_sources,
#		libminigbm_gralloc_intel
		mapper5_common_source
	     ],
    include_directories: [inc, inc_extra],
    c_args: common_cflags + intel_cflags + ['-msse2'],
    link_args: common_link_args,
    dependencies: common_deps,
    install: true,
    install_dir : join_paths(get_option('libdir'), 'hw')
  )

  gralloc_minigbm_intel = library('gralloc.minigbm_intel',
    sources: gralloc0_sources + gralloc_minigbm_intel_sources,
    include_directories: [inc, inc_extra],
    dependencies: [declare_dependency(link_with: libminigbm_gralloc_intel)],
    link_args: common_link_args,
    install: true,
    install_dir : join_paths(get_option('libdir'), 'hw')
  )
endif

# === Meson gralloc ===
if 'meson' in drivers
  libminigbm_gralloc_meson = library('minigbm_gralloc_meson',
    sources: [
                core_sources,
                libminigbm_gralloc_meson_sources,
                cros_gralloc_common_sources,
#                libminigbm_gralloc_meson
		mapper5_common_source
             ],
    include_directories: [inc, inc_extra],
    c_args: common_cflags + meson_cflags,
    link_args: [common_link_args, nosym_link_args],
    dependencies: common_deps,
    install: true,
    install_dir : join_paths(get_option('libdir'), 'hw')
  )

  gralloc_minigbm_meson = library('gralloc.minigbm_meson',
    sources: gralloc0_sources + gralloc_minigbm_meson_sources,
    include_directories: [inc, inc_extra],
    dependencies: [declare_dependency(link_with: libminigbm_gralloc_meson)],
    link_args: common_link_args,
    install: true,
    install_dir : join_paths(get_option('libdir'), 'hw')
  )
endif

# === MSM gralloc ===
if 'msm' in drivers
  libminigbm_gralloc_msm = library('minigbm_gralloc_msm',
    sources: [
                core_sources,
                libminigbm_gralloc_msm_sources,
                cros_gralloc_common_sources,
#                libminigbm_gralloc_msm
		mapper5_common_source
             ],
    include_directories: [inc, inc_extra],
    c_args: common_cflags + msm_cflags,
    link_args: [common_link_args, nosym_link_args],
    dependencies: common_deps,
    install: true,
    install_dir : join_paths(get_option('libdir'), 'hw')
  )

  gralloc_minigbm_msm = library('gralloc.minigbm_msm',
    sources: gralloc0_sources + gralloc_minigbm_msm_sources,
    include_directories: [inc, inc_extra],
    dependencies: [declare_dependency(link_with: libminigbm_gralloc_msm)],
    link_args: common_link_args,
    install: true,
    install_dir : join_paths(get_option('libdir'), 'hw')
  )
endif

##### TRUNK 2 END #####
##### TRUNK 3 START: ARCVM targets, header installs, and pkg-config #####

# === ARCVM gralloc ===
if 'arcvm' in drivers
  libminigbm_gralloc_arcvm = library('minigbm_gralloc_arcvm',
    sources: [
                core_sources,
                libminigbm_gralloc_arcvm_sources,
                cros_gralloc_common_sources,
#                libminigbm_gralloc_arcvm
		mapper5_common_source
             ],
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

# --- File groups ---
minigbm_gralloc4_allocator_files = files(
  'cros_gralloc/gralloc4/CrosGralloc4Allocator.cc',
  'cros_gralloc/gralloc4/CrosGralloc4AllocatorService.cc',
  'cros_gralloc/gralloc4/CrosGralloc4Utils.cc',
  'property_get_shim.c'
)

minigbm_gralloc4_mapper_files = files(
  'cros_gralloc/gralloc4/CrosGralloc4Mapper.cc',
  'cros_gralloc/gralloc4/CrosGralloc4Utils.cc',
)

# --- Common defaults ---
common_includes = include_directories('.')
common_cflags = ['-Wno-sign-compare']

# All your HIDL lib names in one place
hidl_libs = [
  'android.hardware.graphics.mapper@4.0',
  'android.hardware.graphics.allocator@4.0',
  'android.hardware.graphics.allocator-V2-ndk',
  'android.hidl.base@1.0',
  'libgralloctypes',
  'libhidlbase',
  'libbase',
  'libutils',
  'liblog',
]

# Collect deps, skipping missing ones
common_hidl_deps = []
foreach name : hidl_libs
  dep = cc.find_library(name, required: false, dirs: [vndk_llndk_stub, vndk_sp, vndk_core])
  if dep.found()
    common_hidl_deps += dep
  else
    message('lib not found:' + name)
  endif
endforeach  

# --- libminigbm_gralloc4_utils ---
libminigbm_gralloc4_utils = library(
  'minigbm_gralloc4_utils',
  'cros_gralloc/gralloc4/CrosGralloc4Utils.cc',
  'cros_gralloc/String_shim.cpp',
  include_directories : [common_includes, inc_extra,],
  dependencies : [
    common_hidl_deps,
    common_deps,
  ],
  link_with : libminigbm_gralloc,
  link_args: [common_link_args, nosym_link_args],
  install : true
)

# --- Allocator defaults ---
#allocator_defaults_deps = common_deps + [
#  dependency('android.hardware.graphics.allocator@4.0', required : true),
#]

# --- allocator service binaries ---
executable(
  'android.hardware.graphics.allocator@4.0-service.minigbm',
  minigbm_gralloc4_allocator_files,
  link_with : [libminigbm_gralloc,],
  include_directories : [common_includes, inc_extra],
  dependencies : common_deps + common_hidl_deps + [ dependency('libminigbm_gralloc', required : false) ],
  cpp_args: common_cflags,
  c_args: common_cflags,
  link_args: [common_link_args, nosym_link_args],
  install : true,
  install_dir : join_paths(get_option('libexecdir'), 'hw')
)

if 'msm' in drivers
executable(
  'android.hardware.graphics.allocator@4.0-service.minigbm_msm',
  minigbm_gralloc4_allocator_files,
  link_with : libminigbm_gralloc_msm,
  include_directories : [common_includes, inc_extra],
  dependencies : common_deps + common_hidl_deps + [ dependency('libminigbm_gralloc_msm', required : false) ],
  link_args: [common_link_args, nosym_link_args],
  install : true,
  install_dir : join_paths(get_option('libexecdir'), 'hw')
)
endif

if 'arcvm' in drivers
executable(
  'android.hardware.graphics.allocator@4.0-service.minigbm_arcvm',
  minigbm_gralloc4_allocator_files,
  link_with : libminigbm_gralloc_arcvm,
  include_directories : [common_includes, inc_extra],
  dependencies : [
	common_deps,
	common_hidl_deps,
	dependency('libminigbm_gralloc_arcvm', required : false),
  ],
  link_args: common_link_args,
  install : true,
  install_dir : join_paths(get_option('libexecdir'), 'hw')
)
endif

# Intel variant (only for x86/x86_64)
if host_machine.cpu_family() in ['x86', 'x86_64']
  executable(
    'android.hardware.graphics.allocator@4.0-service.minigbm_intel',
    minigbm_gralloc4_allocator_files,
    link_with : libminigbm_gralloc_intel,
    include_directories : [common_includes, inc_extra],
    dependencies : [
	common_deps,
	common_hidl_deps,
	dependency('libminigbm_gralloc_intel', required : false),
    ],
    link_args: common_link_args,
    install : true,
    install_dir : join_paths(get_option('libexecdir'), 'hw')
  )
endif

# --- Mapper shared libraries ---
shared_lib_mapper_minigbm = library(
  'android.hardware.graphics.mapper@4.0-impl.minigbm',
  minigbm_gralloc4_mapper_files,
  include_directories : [common_includes, inc_extra],
  dependencies : [
	common_deps,
	common_hidl_deps,
	dependency('libminigbm_gralloc', required : false),
  ],
  link_with : libminigbm_gralloc,
  link_args : [common_link_args, nosym_link_args],
  install : true,
  install_dir : join_paths(get_option('libdir'), 'hw')
)

if 'msm' in drivers
shared_lib_mapper_msm = library(
  'android.hardware.graphics.mapper@4.0-impl.minigbm_msm',
  minigbm_gralloc4_mapper_files,
  include_directories : [common_includes, inc_extra],
  dependencies : [
	common_deps,
	common_hidl_deps,
	dependency('libminigbm_gralloc_msm', required : false),
   ],
  link_with : libminigbm_gralloc_msm,
  link_args : [common_link_args, nosym_link_args],
  install : true,
  install_dir : join_paths(get_option('libdir'), 'hw')
)
endif

if 'arcvm' in drivers
shared_lib_mapper_arcvm = library(
  'android.hardware.graphics.mapper@4.0-impl.minigbm_arcvm',
  minigbm_gralloc4_mapper_files,
  include_directories : [common_includes, inc_extra],
  dependencies : [
	common_deps,
	common_hidl_deps,
	dependency('libminigbm_gralloc_arcvm', required : false),
  ],
  link_with : libminigbm_gralloc_arcvm,
  link_args : common_link_args,
  install : true,
  install_dir : join_paths(get_option('libdir'), 'hw')
)
endif

if host_machine.cpu_family() in ['x86', 'x86_64']
  shared_lib_mapper_intel = library(
    'android.hardware.graphics.mapper@4.0-impl.minigbm_intel',
    minigbm_gralloc4_mapper_files,
    include_directories : [common_includes, inc_extra],
    dependencies : [
	common_deps,
	common_hidl_deps,
	dependency('libminigbm_gralloc_intel', required : false),
    ],
    link_with : libminigbm_gralloc_intel,
    link_args : common_link_args,
    install : true,
    install_dir : join_paths(get_option('libdir'), 'hw')
  )
endif

# --- Install VINTF fragments and init_rc files ---
install_data('cros_gralloc/gralloc4/android.hardware.graphics.allocator@4.0.xml',
  install_dir : join_paths(get_option('datadir'), 'vintf')
)
install_data('cros_gralloc/gralloc4/android.hardware.graphics.mapper@4.0.xml',
  install_dir : join_paths(get_option('datadir'), 'vintf')
)

install_data('cros_gralloc/gralloc4/android.hardware.graphics.allocator@4.0-service.minigbm.rc',
  install_dir : join_paths(get_option('sysconfdir'), 'init')
)
install_data('cros_gralloc/gralloc4/android.hardware.graphics.allocator@4.0-service.minigbm_msm.rc',
  install_dir : join_paths(get_option('sysconfdir'), 'init')
)
install_data('cros_gralloc/gralloc4/android.hardware.graphics.allocator@4.0-service.minigbm_arcvm.rc',
  install_dir : join_paths(get_option('sysconfdir'), 'init')
)
if host_machine.cpu_family() in ['x86', 'x86_64']
  install_data('cros_gralloc/gralloc4/android.hardware.graphics.allocator@4.0-service.minigbm_intel.rc',
    install_dir : join_paths(get_option('sysconfdir'), 'init')
  )
endif

# Shared library dependencies (pkg-config or system)
dep_allocator_ndk = dependency('android.hardware.graphics.allocator-V2-ndk', required : false)
dep_mapper4       = dependency('android.hardware.graphics.mapper@4.0', required : false)
dep_libbase       = dependency('libbase', required : false)
dep_binder_ndk    = dependency('libbinder_ndk', required : false)
dep_gralloctypes  = dependency('libgralloctypes', required : false)
dep_hidlbase      = dependency('libhidlbase', required : false)
dep_log           = dependency('liblog', required : false)
#dep_minigbm_gralloc = dependency('libminigbm_gralloc', required : false)
#dep_minigbm_utils   = dependency('libminigbm_gralloc4_utils', required : false)

# Static library dependencies (built in-tree or via subproject)
#dep_aidlcommonsupport = dependency('libaidlcommonsupport', required : false)

# Group them for convenience
all_aosp_deps = [
  dep_allocator_ndk,
  dep_mapper4,
  dep_libbase,
  dep_binder_ndk,
  dep_gralloctypes,
  dep_hidlbase,
  dep_log,
#  dep_minigbm_gralloc,
#  dep_minigbm_utils,
  #dep_aidlcommonsupport,
]


# Shared libraries
shared_libs = [
  'android.hardware.graphics.allocator-V2-ndk',
  'android.hardware.graphics.mapper@4.0',
  'libbase',
  'libbinder_ndk',
  'libgralloctypes',
  'libhidlbase',
  'liblog',
  'libminigbm_gralloc',
  'libminigbm_gralloc4_utils',
]

srcs = files(
  'cros_gralloc/aidl/Allocator.cpp',
  'cros_gralloc/aidl/Main.cpp',
  'cros_gralloc/aidl/NativeHandle.cpp',
)

# Binary target
executable(
  'android.hardware.graphics.allocator-service.minigbm',
  srcs,
  include_directories : [inc_extra,],
  link_with : [libminigbm_gralloc4_utils,],
# suppose all libdrm symbols are gone through minigbm and libminigbm_gralloc4_utils will
# link with minigbm statically.
#  link_with : [libdrm_dep,],
  dependencies : [all_aosp_deps, libminigbm_gralloc_dep, libdrm_dep,],
  link_args: [common_link_args, nosym_link_args],
  install : true,
  install_dir : join_paths(get_option('libexecdir'), 'hw')
  #install_dir : join_paths(get_option('libdir'), 'hw')
)

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
