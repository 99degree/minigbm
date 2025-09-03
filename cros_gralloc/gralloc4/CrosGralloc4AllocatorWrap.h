#include <android/hardware/graphics/allocator/4.0/IAllocator.h>
#include <android/hardware/graphics/mapper/4.0/IMapper.h>
#include <android/hardware/graphics/allocator/4.0/BnHwAllocator.h>
#include <hidl/HidlTransportSupport.h>
#include <log/log.h>

 #include <memory>

#include <hidl/HidlSupport.h>

#include "cros_gralloc/cros_gralloc_driver.h"
#include "cros_gralloc/cros_gralloc_helpers.h"

namespace android {
namespace hardware {
namespace graphics {
namespace allocator {
namespace V4_0 {

using ::android::sp;

class CrosGralloc4AllocatorWrap final : public BnHwAllocator {
public:
    // Construct with a concrete IAllocator implementation.
    explicit CrosGralloc4AllocatorWrap(const sp<IAllocator>& impl)
        : BnHwAllocator(impl) {}

    // No copying.
    CrosGralloc4AllocatorWrap(const CrosGralloc4AllocatorWrap&) = delete;
    CrosGralloc4AllocatorWrap& operator=(const CrosGralloc4AllocatorWrap&) = delete;

    // Defaulted destructor is fine; base cleans up.
    ~CrosGralloc4AllocatorWrap() override = default;
};

}  // namespace V4_0
}  // namespace allocator
}  // namespace graphics
}  // namespace hardware
}  // namespace android
