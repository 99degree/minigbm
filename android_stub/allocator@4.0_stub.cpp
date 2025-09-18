#include <android/hardware/graphics/allocator/4.0/IAllocator.h>
#include <android/hidl/base/1.0/IBase.h>
#include <utils/Errors.h>

using ::android::hardware::Return;
using ::android::hardware::hidl_handle;
using ::android::hardware::hidl_vec;
using ::android::hardware::hidl_string;
using ::android::hidl::base::V1_0::DebugInfo;

namespace android {
namespace hardware {
namespace graphics {
namespace allocator {
namespace V4_0 {

// IBase overrides redeclared in IAllocator
Return<void> IAllocator::interfaceChain(interfaceChain_cb) { return Return<void>(); }
Return<void> IAllocator::interfaceDescriptor(interfaceDescriptor_cb) { return Return<void>(); }
Return<void> IAllocator::getHashChain(getHashChain_cb) { return Return<void>(); }
Return<void> IAllocator::debug(const hidl_handle&, const hidl_vec<hidl_string>&) { return Return<void>(); }
Return<void> IAllocator::setHALInstrumentation() { return Return<void>(); }
Return<bool> IAllocator::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>&, uint64_t) { return false; }
Return<bool> IAllocator::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>&) { return false; }
Return<void> IAllocator::ping() { return Return<void>(); }
Return<void> IAllocator::getDebugInfo(getDebugInfo_cb) { return Return<void>(); }
Return<void> IAllocator::notifySyspropsChanged() { return Return<void>(); }

// IAllocator-specific
Return<void> IAllocator::allocate(const hidl_vec<uint8_t>&, uint32_t, allocate_cb) {
    return Return<void>();
}

// Non-virtual helper present in generated headers
::android::status_t IAllocator::registerAsService(const std::string& /*serviceName*/) {
    return 0; // OK
}

} // namespace V4_0
} // namespace allocator
} // namespace graphics
} // namespace hardware
} // namespace android
