// stub_gralloctype.cpp — Trunk 1
#include <cstdint>
#include <vector>
#include <string>
#include <optional>
#include <android/hardware/graphics/common/1.2/types.h>

namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {
struct Rect;
struct XyColor;
struct Smpte2086;
struct Cta861_3;
struct PlaneLayout;
struct PlaneLayoutComponent;
struct ExtendableType;
} // namespace common
} // namespace graphics
} // namespace hardware
} // namespace android
} // namespace aidl

namespace android {
namespace hardware {

template <typename T>
class hidl_vec;

namespace graphics {
namespace common {
namespace V1_2 {
enum class PixelFormat : int32_t;
} // namespace V1_2
} // namespace common

namespace mapper {
namespace V4_0 {
struct IMapper {
  struct MetadataType;
  struct BufferDescriptorInfo;
};
} // namespace V4_0
} // namespace mapper
} // namespace graphics
} // namespace hardware
} // namespace android

namespace android {
namespace gralloc4 {

struct InputHidlVec;
struct OutputHidlVec;

template <typename T>
inline void zero_out(T* p) { }

template <typename T>
inline void reset_opt(std::optional<T>* p) { }

// === Initial decode/encode functions ===
int decodeCrop(const ::android::hardware::hidl_vec<uint8_t>&,
               std::vector<::aidl::android::hardware::graphics::common::Rect>* ) { return 0; }

int decodeName(const ::android::hardware::hidl_vec<uint8_t>&,
               std::string* ) { return 0; }

int decodeRect(::android::gralloc4::InputHidlVec*,
               ::aidl::android::hardware::graphics::common::Rect* ) { return 0; }

int encodeCrop(const std::vector<::aidl::android::hardware::graphics::common::Rect>&,
               ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeName(const std::string&,
               ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeRect(const ::aidl::android::hardware::graphics::common::Rect&,
               ::android::gralloc4::OutputHidlVec* ) { return 0; }
// === Scalar decoders/encoders by MetadataType ===
int decodeFloat(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                const ::android::hardware::hidl_vec<uint8_t>&,
                float* out) { zero_out(out); return 0; }

int decodeInt32(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                const ::android::hardware::hidl_vec<uint8_t>&,
                int* out) { zero_out(out); return 0; }

int decodeInt64(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                const ::android::hardware::hidl_vec<uint8_t>&,
                long* out) { zero_out(out); return 0; }

int decodeUint32(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                 const ::android::hardware::hidl_vec<uint8_t>&,
                 unsigned int* out) { zero_out(out); return 0; }

int decodeUint64(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                 const ::android::hardware::hidl_vec<uint8_t>&,
                 unsigned long* out) { zero_out(out); return 0; }

int decodeDouble(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                 const ::android::hardware::hidl_vec<uint8_t>&,
                 double* out) { zero_out(out); return 0; }

int decodeString(::android::gralloc4::InputHidlVec*,
                 std::string* out) { return 0; }

int decodeString(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                 const ::android::hardware::hidl_vec<uint8_t>&,
                 std::string* out) { return 0; }

// === Scalar encoders ===
int encodeFloat(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                float,
                ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeInt32(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                int,
                ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeInt64(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                long,
                ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeUint32(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                 unsigned int,
                 ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeUint64(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                 unsigned long,
                 ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeDouble(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                 double,
                 ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeString(const ::android::hardware::graphics::mapper::V4_0::IMapper::MetadataType&,
                 const std::string&,
                 ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeString(const std::string&,
                 ::android::gralloc4::OutputHidlVec* ) { return 0; }
// === Width / Height / Usage / LayerCount / AllocationSize / ProtectedContent / BufferId ===
int decodeUsage(const ::android::hardware::hidl_vec<uint8_t>&,
                unsigned long* out) { zero_out(out); return 0; }

int decodeWidth(const ::android::hardware::hidl_vec<uint8_t>&,
                unsigned long* out) { zero_out(out); return 0; }

int decodeHeight(const ::android::hardware::hidl_vec<uint8_t>&,
                 unsigned long* out) { zero_out(out); return 0; }

int decodeLayerCount(const ::android::hardware::hidl_vec<uint8_t>&,
                     unsigned long* out) { zero_out(out); return 0; }

int decodeAllocationSize(const ::android::hardware::hidl_vec<uint8_t>&,
                         unsigned long* out) { zero_out(out); return 0; }

int decodeProtectedContent(const ::android::hardware::hidl_vec<uint8_t>&,
                           unsigned long* out) { zero_out(out); return 0; }

int decodeBufferId(const ::android::hardware::hidl_vec<uint8_t>&,
                   unsigned long* out) { zero_out(out); return 0; }

// Encoders for the above
int encodeUsage(unsigned long,
                ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeWidth(unsigned long,
                ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeHeight(unsigned long,
                 ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeLayerCount(unsigned long,
                     ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeAllocationSize(unsigned long,
                         ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeBufferId(unsigned long,
                   ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

// === Byte vector helpers ===
int decodeByteVector(::android::gralloc4::InputHidlVec*,
                     std::vector<uint8_t>* out) { return 0; }

int encodeByteVector(const std::vector<uint8_t>&,
                     ::android::gralloc4::OutputHidlVec* ) { return 0; }
// === Interlaced helpers ===
int decodeInterlaced(const ::android::hardware::hidl_vec<uint8_t>&,
                     ::aidl::android::hardware::graphics::common::ExtendableType* ) { return 0; }

int encodeInterlaced(const ::aidl::android::hardware::graphics::common::ExtendableType&,
                     ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int getInterlacedName(const ::aidl::android::hardware::graphics::common::ExtendableType& ) { return 0; }

int isStandardInterlaced(const ::aidl::android::hardware::graphics::common::ExtendableType& ) { return 0; }

int getStandardInterlacedValue(const ::aidl::android::hardware::graphics::common::ExtendableType& ) { return 0; }

// === Compression helpers ===
int decodeCompression(const ::android::hardware::hidl_vec<uint8_t>&,
                      ::aidl::android::hardware::graphics::common::ExtendableType* ) { return 0; }

int encodeCompression(const ::aidl::android::hardware::graphics::common::ExtendableType&,
                      ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int getCompressionName(const ::aidl::android::hardware::graphics::common::ExtendableType& ) { return 0; }

int isStandardCompression(const ::aidl::android::hardware::graphics::common::ExtendableType& ) { return 0; }

int getStandardCompressionValue(const ::aidl::android::hardware::graphics::common::ExtendableType& ) { return 0; }

// === Chroma siting helpers ===
int decodeChromaSiting(const ::android::hardware::hidl_vec<uint8_t>&,
                       ::aidl::android::hardware::graphics::common::ExtendableType* ) { return 0; }

int encodeChromaSiting(const ::aidl::android::hardware::graphics::common::ExtendableType&,
                       ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int getChromaSitingName(const ::aidl::android::hardware::graphics::common::ExtendableType& ) { return 0; }

int isStandardChromaSiting(const ::aidl::android::hardware::graphics::common::ExtendableType& ) { return 0; }

int getStandardChromaSitingValue(const ::aidl::android::hardware::graphics::common::ExtendableType& ) { return 0; }
// === Plane layout helpers ===
int decodePlaneLayout(::android::gralloc4::InputHidlVec*,
                      ::aidl::android::hardware::graphics::common::PlaneLayout* ) { return 0; }

int encodePlaneLayout(const ::aidl::android::hardware::graphics::common::PlaneLayout&,
                      ::android::gralloc4::OutputHidlVec* ) { return 0; }

int clearPlaneLayouts(std::vector<::aidl::android::hardware::graphics::common::PlaneLayout>* v) {
    return 0;
}

int decodePlaneLayouts(const ::android::hardware::hidl_vec<uint8_t>&,
                       std::vector<::aidl::android::hardware::graphics::common::PlaneLayout>* v) {
    return 0;
}

int encodePlaneLayouts(const std::vector<::aidl::android::hardware::graphics::common::PlaneLayout>&,
                       ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int decodePlaneLayoutsHelper(::android::gralloc4::InputHidlVec*,
                             std::vector<::aidl::android::hardware::graphics::common::PlaneLayout>* v) {
    return 0;
}

int encodePlaneLayoutsHelper(const std::vector<::aidl::android::hardware::graphics::common::PlaneLayout>&,
                             ::android::gralloc4::OutputHidlVec* ) { return 0; }

// === Plane layout component helpers ===
int decodePlaneLayoutComponent(::android::gralloc4::InputHidlVec*,
                               ::aidl::android::hardware::graphics::common::PlaneLayoutComponent* ) { return 0; }

int encodePlaneLayoutComponent(const ::aidl::android::hardware::graphics::common::PlaneLayoutComponent&,
                               ::android::gralloc4::OutputHidlVec* ) { return 0; }

int decodePlaneLayoutComponents(::android::gralloc4::InputHidlVec*,
                                std::vector<::aidl::android::hardware::graphics::common::PlaneLayoutComponent>* v) {
    return 0;
}

int encodePlaneLayoutComponents(const std::vector<::aidl::android::hardware::graphics::common::PlaneLayoutComponent>&,
                                ::android::gralloc4::OutputHidlVec* ) { return 0; }

int isStandardPlaneLayoutComponentType(const ::aidl::android::hardware::graphics::common::ExtendableType& ) { return 0; }

int getPlaneLayoutComponentTypeName(const ::aidl::android::hardware::graphics::common::ExtendableType& ) { return 0; }

int getStandardPlaneLayoutComponentTypeValue(const ::aidl::android::hardware::graphics::common::ExtendableType& ) { return 0; }
// === Crop vector helpers ===
int clearCrop(std::vector<::aidl::android::hardware::graphics::common::Rect>* v) {
    return 0;
}

int decodeCropHelper(::android::gralloc4::InputHidlVec*,
                     std::vector<::aidl::android::hardware::graphics::common::Rect>* v) {
    return 0;
}

int encodeCropHelper(const std::vector<::aidl::android::hardware::graphics::common::Rect>&,
                     ::android::gralloc4::OutputHidlVec* ) { return 0; }

// === CTA‑861.3 helpers ===
int decodeCta861_3(const ::android::hardware::hidl_vec<uint8_t>&,
                   std::optional<::aidl::android::hardware::graphics::common::Cta861_3>* out) {
    return 0;
}

int encodeCta861_3(const std::optional<::aidl::android::hardware::graphics::common::Cta861_3>&,
                   ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int decodeCta861_3Helper(::android::gralloc4::InputHidlVec*,
                         ::aidl::android::hardware::graphics::common::Cta861_3* ) { return 0; }

int encodeCta861_3Helper(const ::aidl::android::hardware::graphics::common::Cta861_3&,
                         ::android::gralloc4::OutputHidlVec* ) { return 0; }

// === SMPTE 2086 helpers ===
int decodeSmpte2086(const ::android::hardware::hidl_vec<uint8_t>&,
                    std::optional<::aidl::android::hardware::graphics::common::Smpte2086>* out) {
    return 0;
}

int encodeSmpte2086(const std::optional<::aidl::android::hardware::graphics::common::Smpte2086>&,
                    ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int decodeSmpte2086Helper(::android::gralloc4::InputHidlVec*,
                          ::aidl::android::hardware::graphics::common::Smpte2086* ) { return 0; }

int encodeSmpte2086Helper(const ::aidl::android::hardware::graphics::common::Smpte2086&,
                          ::android::gralloc4::OutputHidlVec* ) { return 0; }

// === SMPTE 2094 helpers ===
int decodeSmpte2094_10(const ::android::hardware::hidl_vec<uint8_t>&,
                       std::optional<std::vector<uint8_t>>* out) {
    return 0;
}

int decodeSmpte2094_40(const ::android::hardware::hidl_vec<uint8_t>&,
                       std::optional<std::vector<uint8_t>>* out) {
    return 0;
}
// === SMPTE 2094 encoders ===
int encodeSmpte2094_10(const std::optional<std::vector<uint8_t>>&,
                       ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

int encodeSmpte2094_40(const std::optional<std::vector<uint8_t>>&,
                       ::android::hardware::hidl_vec<uint8_t>* ) { return 0; }

// === Any other trailing helpers from your list could go here ===
// (If your demangled.txt had more, add them above before closing namespaces)

// Dummy status_t type if not already defined
using status_t = int32_t;

// Dummy struct for BufferDescriptorInfo if not already defined
struct BufferDescriptorInfo {
    // add fields if needed for compilation
};

// Stub implementation
status_t decodeBufferDescriptorInfo(
    const ::android::hardware::hidl_vec<uint8_t>& /*descriptor*/,
    ::android::hardware::graphics::mapper::V4_0::IMapper::BufferDescriptorInfo* /*outInfo*/) {
    // No-op stub: does nothing, returns success
    return 0;
}

} // namespace hardware
} // namespace android

// Add missing type placeholders if not defined in your branch
namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {
    enum class Dataspace : int32_t {};
    enum class BlendMode : int32_t {};
} // namespace common
} // namespace graphics
} // namespace hardware
} // namespace android
} // namespace aidl

namespace android {
namespace gralloc4 {

// === Additional stubs for missing symbols ===

int encodeBufferDescriptorInfo(
    const ::android::hardware::graphics::mapper::V4_0::IMapper::BufferDescriptorInfo& /*info*/,
    ::android::hardware::hidl_vec<uint8_t>* /*out*/) {
    return 0;
}

int encodePixelFormatRequested(
    const ::android::hardware::graphics::common::V1_2::PixelFormat& /*fmt*/,
    ::android::hardware::hidl_vec<uint8_t>* /*out*/) {
    return 0;
}

int encodePixelFormatFourCC(
    unsigned int /*fourcc*/,
    ::android::hardware::hidl_vec<uint8_t>* /*out*/) {
    return 0;
}

int encodePixelFormatModifier(
    unsigned long /*modifier*/,
    ::android::hardware::hidl_vec<uint8_t>* /*out*/) {
    return 0;
}

int encodeProtectedContent(
    unsigned long /*prot*/,
    ::android::hardware::hidl_vec<uint8_t>* /*out*/) {
    return 0;
}

int encodeDataspace(
    const ::aidl::android::hardware::graphics::common::Dataspace& /*ds*/,
    ::android::hardware::hidl_vec<uint8_t>* /*out*/) {
    return 0;
}

int encodeBlendMode(
    const ::aidl::android::hardware::graphics::common::BlendMode& /*bm*/,
    ::android::hardware::hidl_vec<uint8_t>* /*out*/) {
    return 0;
}

int decodeBlendMode(
    const ::android::hardware::hidl_vec<uint8_t>& /*in*/,
    ::aidl::android::hardware::graphics::common::BlendMode* /*out*/) {
    return 0;
}

int decodeDataspace(
    const ::android::hardware::hidl_vec<uint8_t>& /*in*/,
    ::aidl::android::hardware::graphics::common::Dataspace* /*out*/) {
    return 0;
}

} // namespace gralloc4
} // namespace android
