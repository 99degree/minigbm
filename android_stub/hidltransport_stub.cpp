// StubHidlTransportV34.h
#pragma once

#include <android/hidl/base/1.0/IBase.h>
#include <hidl/Status.h>
#include <hidl/MQDescriptor.h>
#include <hidl/HidlSupport.h>
#include <utils/RefBase.h>
#include <hidl/LegacySupport.h>  // For registerAsService, etc.

namespace android {
namespace hardware {

using android::sp;
using android::hardware::hidl_string;
using android::hardware::hidl_vec;
using android::hardware::Return;
using android::hardware::Void;
using android::hidl::base::V1_0::IBase;

class StubBaseV34 : public IBase {
public:
    Return<void> interfaceChain(interfaceChain_cb _hidl_cb) override {
        _hidl_cb({ "android.hidl.base@1.0::IBase" });
        return Void();
    }

    Return<void> debug(const hidl_handle&, const hidl_vec<hidl_string>&) override {
        return Void();
    }

    Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) override {
        _hidl_cb("android.hidl.base@1.0::IBase");
        return Void();
    }

    Return<void> getHashChain(getHashChain_cb _hidl_cb) override {
        _hidl_cb({});
        return Void();
    }

    Return<void> setHALInstrumentation() override {
        return Void();
    }

    Return<bool> linkToDeath(const sp<hidl_death_recipient>&, uint64_t) override {
        return false;
    }

    Return<void> ping() override {
        return Void();
    }

    Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) override {
        _hidl_cb({});
        return Void();
    }

    Return<void> notifySyspropsChanged() override {
        return Void();
    }

    Return<bool> unlinkToDeath(const sp<hidl_death_recipient>&) override {
        return false;
    }

    // Optional: stub out registerAsService if needed
    android::status_t registerAsService(const std::string& name = "default") {
        // No-op stub
        return android::OK;
    }
};

}  // namespace hardware
}  // namespace android
