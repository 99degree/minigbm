// FIXME: your file license if you have one

#include "Allocator.h"

namespace android {
namespace hardware {
namespace graphics {
namespace allocator {
namespace V4_0 {
namespace implementation {

// Methods from ::android::hardware::graphics::allocator::V4_0::IAllocator follow.
Return<void> Allocator::allocate(const hidl_vec<uint8_t>& descriptor, uint32_t count, allocate_cb _hidl_cb) {
    // TODO implement
    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

//IAllocator* HIDL_FETCH_IAllocator(const char* /* name */) {
    //return new Allocator();
//}
//
}  // namespace implementation
}  // namespace V4_0
}  // namespace allocator
}  // namespace graphics
}  // namespace hardware
}  // namespace android
