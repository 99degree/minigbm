/*
 * Copyright 2020 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <android/hardware/graphics/allocator/4.0/IAllocator.h>
#include <android/hardware/graphics/mapper/4.0/IMapper.h>
#include <android/hardware/graphics/allocator/4.0/BnHwAllocator.h>
#include <hidl/HidlTransportSupport.h>
#include <log/log.h>

#include <memory>

#include <hidl/HidlSupport.h>

#include "cros_gralloc/cros_gralloc_driver.h"
#include "cros_gralloc/cros_gralloc_helpers.h"

class CrosGralloc4Allocator : public BnHwAllocator {
  public:
    CrosGralloc4Allocator() = default;

//    const std::type_info& _force_typeinfo_IAllocator =
//        typeid(::android::hardware::graphics::allocator::V4_0::IAllocator);

    android::hardware::Return<void> allocate(const android::hardware::hidl_vec<uint8_t>& descriptor,
                                             uint32_t count, allocate_cb hidl_cb) override;

    android::hardware::graphics::mapper::V4_0::Error init();

    /* must add this to avoid calling base type, thus will cross __1 and __ndk1 boundry */
    android::hardware::Return<void> interfaceChain(interfaceChain_cb _hidl_cb) {
        // This is the list of fully qualified interface names
        // from most derived to base
        _hidl_cb({
            "android.hardware.graphics.allocator@4.0::IAllocator",
            "android.hidl.base@1.0::IBase"
        });
        return ::android::hardware::Void();
    }

    android::hardware::Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) {
        _hidl_cb("android.hardware.graphics.allocator@4.0::IAllocator");
        return ::android::hardware::Void();
    }

    android::hardware::Return<void> getHashChain(getHashChain_cb _hidl_cb) {
        std::array<uint8_t, 32> hash1 = { /* SHA-256 of IAllocator@4.0 HAL */ };
        std::array<uint8_t, 32> hash2 = { /* SHA-256 of IBase HAL */ };

        android::hardware::hidl_vec<android::hardware::hidl_array<uint8_t, 32>> vec;
        vec.resize(2);
        vec[0] = hash1;
        vec[1] = hash2;

        _hidl_cb(vec);
        return ::android::hardware::Void();
    }

    android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) {
        ::android::hidl::base::V1_0::DebugInfo info = {};
        info.pid = getpid();
        info.ptr = reinterpret_cast<uint64_t>(this);
#if defined(__LP64__)
        info.arch = ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_64BIT;
#else
        info.arch = ::android::hidl::base::V1_0::DebugInfo::Architecture::IS_32BIT;
#endif
        _hidl_cb(info);
        return ::android::hardware::Void();
    }

  //android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) override;

  private:
    android::hardware::graphics::mapper::V4_0::Error allocate(
            const android::hardware::graphics::mapper::V4_0::IMapper::BufferDescriptorInfo&
                    description,
            uint32_t* outStride, android::hardware::hidl_handle* outHandle);

    std::shared_ptr<cros_gralloc_driver> mDriver;
};
