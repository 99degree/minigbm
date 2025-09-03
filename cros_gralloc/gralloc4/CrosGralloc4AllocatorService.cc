/*
 * Copyright 2020 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#define LOG_TAG "AllocatorService"

#include <hidl/LegacySupport.h>

#include "CrosGralloc4Allocator.h"
#include "CrosGralloc4AllocatorWrap.h"

using android::sp;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::hardware::graphics::mapper::V4_0::Error;
using android::hardware::graphics::allocator::V4_0::IAllocator;
using android::hardware::graphics::allocator::V4_0::CrosGralloc4AllocatorWrap;

int main(int, char**) {
    sp<IAllocator> allocator = new CrosGralloc4Allocator();

    // Call init() on the implementation before wrapping it
    if (static_cast<CrosGralloc4Allocator*>(allocator.get())->init()
            != android::hardware::graphics::mapper::V4_0::Error::NONE) {
        ALOGE("Allocator init failed");
        return -EINVAL;
    }

    sp<CrosGralloc4AllocatorWrap> wrap = new CrosGralloc4AllocatorWrap(allocator);

#if 0
    if (allocator->init() != Error::NONE) {
        ALOGE("Failed to initialize IAllocator 4.0 service.");
        return -EINVAL;
    }
#endif

    configureRpcThreadpool(4, true /* callerWillJoin */);
    if (allocator->registerAsService() != android::NO_ERROR) {
        ALOGE("Failed to register graphics IAllocator 4.0 service.");
        return -EINVAL;
    }

    ALOGI("IAllocator 4.0 service is initialized.");
    android::hardware::joinRpcThreadpool();
    ALOGI("IAllocator 4.0 service is terminating.");
    return 0;
}

extern "C" {
//    const std::type_info* _ZTIN7android8hardware8graphics9allocator4V4_010IAllocatorE =
//        &typeid(::android::hardware::graphics::allocator::V4_0::IAllocator);
}
