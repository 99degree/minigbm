// ======================================================================
// Plane Layout Utilities — Public API 34 + Legacy YV12 Support + Shim
// Drop‑in replacement, self‑contained, NDK‑v34‑friendly
// ======================================================================

#include <android/hardware_buffer.h>
#include <android/native_window.h>
#include <utils/Errors.h>
#include <vector>
#include <cstdint>

// ---- Compatibility Guards ----

// If AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM_SRGB is missing in your NDK,
// alias it to the plain UNORM variant.
#ifndef AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM_SRGB
#define AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM_SRGB AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM
#endif

// If WINDOW_FORMAT_YV12 is missing, define it from the FOURCC code.
#ifndef WINDOW_FORMAT_YV12
#define WINDOW_FORMAT_YV12 0x32315659 // 'YV12'
#endif

// Bring android::status_t and constants into the current scope.
using android::status_t;
using android::OK;
using android::BAD_VALUE;

namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {

enum ComponentType {
    COMPONENT_R,
    COMPONENT_G,
    COMPONENT_B,
    COMPONENT_A,
    COMPONENT_Y,
    COMPONENT_CB,
    COMPONENT_CR,
    COMPONENT_DEPTH,
    COMPONENT_STENCIL
};

struct PlaneLayoutComponent {
    int32_t component;
    int32_t bitsPerPixel;
    int32_t offsetInBits;
};

struct PlaneLayout {
    int64_t offsetInBytes;
    int64_t strideInBytes;
    int64_t widthInSamples;
    int64_t heightInSamples;
    std::vector<PlaneLayoutComponent> components;
};

} } } } } // namespace closing

using aidl::android::hardware::graphics::common::PlaneLayout;
using aidl::android::hardware::graphics::common::PlaneLayoutComponent;
using aidl::android::hardware::graphics::common::ComponentType;

// ---- Format Table Helpers ----

struct FormatLayoutSpec {
    uint32_t format;
    std::vector<PlaneLayout> planes;
};

inline PlaneLayout makeRGBA8888(uint32_t width, uint32_t height) {
    PlaneLayout p{};
    p.offsetInBytes = 0;
    p.strideInBytes = width * 4;
    p.widthInSamples = width;
    p.heightInSamples = height;
    p.components = {
        {ComponentType::COMPONENT_R, 8, 0},
        {ComponentType::COMPONENT_G, 8, 8},
        {ComponentType::COMPONENT_B, 8, 16},
        {ComponentType::COMPONENT_A, 8, 24}
    };
    return p;
}

inline PlaneLayout makeRGB565(uint32_t width, uint32_t height) {
    PlaneLayout p{};
    p.offsetInBytes = 0;
    p.strideInBytes = width * 2;
    p.widthInSamples = width;
    p.heightInSamples = height;
    p.components = {
        {ComponentType::COMPONENT_R, 5, 11},
        {ComponentType::COMPONENT_G, 6, 5},
        {ComponentType::COMPONENT_B, 5, 0}
    };
    return p;
}

inline std::vector<FormatLayoutSpec> buildFormatLayoutTable(uint32_t width,
                                                            uint32_t height) {
    return {
        { AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM,
          { makeRGBA8888(width, height) } },
        { AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM_SRGB,
          { makeRGBA8888(width, height) } },
        { AHARDWAREBUFFER_FORMAT_R5G6B5_UNORM,
          { makeRGB565(width, height) } }
    };
}

// ---- Core Implementation ----

inline std::vector<PlaneLayout> getPlaneLayouts(uint32_t format,
                                                uint32_t width,
                                                uint32_t height) {
    std::vector<PlaneLayout> layouts;

    if (format == WINDOW_FORMAT_YV12) {
        PlaneLayout yPlane{};
        yPlane.offsetInBytes = 0;
        yPlane.strideInBytes = (width + 15) & ~15;
        yPlane.widthInSamples = width;
        yPlane.heightInSamples = height;
        yPlane.components.push_back({ComponentType::COMPONENT_Y, 8, 0});

        PlaneLayout uPlane{};
        uPlane.offsetInBytes = yPlane.strideInBytes * height;
        uPlane.strideInBytes = ((width / 2) + 15) & ~15;
        uPlane.widthInSamples = width / 2;
        uPlane.heightInSamples = height / 2;
        uPlane.components.push_back({ComponentType::COMPONENT_CB, 8, 0});

        PlaneLayout vPlane{};
        vPlane.offsetInBytes = uPlane.offsetInBytes +
                               uPlane.strideInBytes * (height / 2);
        vPlane.strideInBytes = ((width / 2) + 15) & ~15;
        vPlane.widthInSamples = width / 2;
        vPlane.heightInSamples = height / 2;
        vPlane.components.push_back({ComponentType::COMPONENT_CR, 8, 0});

        return {yPlane, uPlane, vPlane};
    }

    auto table = buildFormatLayoutTable(width, height);
    for (const auto& spec : table) {
        if (spec.format == format) {
            return spec.planes;
        }
    }

    return layouts;
}

// ---- Shim Adapter ----

struct MyPlaneLayoutComponent {
    int32_t component;
    int32_t bitsPerPixel;
    int32_t offsetInBits;
};

struct MyPlaneLayout {
    int64_t offsetInBytes;
    int64_t strideInBytes;
    int64_t widthInSamples;
    int64_t heightInSamples;
    std::vector<MyPlaneLayoutComponent> components;
};

static MyPlaneLayout toMyLayout(const PlaneLayout& in) {
    MyPlaneLayout out;
    out.offsetInBytes  = in.offsetInBytes;
    out.strideInBytes  = in.strideInBytes;
    out.widthInSamples = in.widthInSamples;
    out.heightInSamples= in.heightInSamples;
    out.components.reserve(in.components.size());
    for (const auto& c : in.components) {
        out.components.push_back({
            c.component,
            c.bitsPerPixel,
            c.offsetInBits
        });
    }
    return out;
}

inline status_t getPlaneLayouts(uint32_t format,
                                uint32_t width,
                                uint32_t height,
                                std::vector<MyPlaneLayout>* outLayouts) {
    if (!outLayouts) return BAD_VALUE;
    auto layouts = ::getPlaneLayouts(format, width, height);
    outLayouts->clear();
    outLayouts->reserve(layouts.size());
    for (const auto& l : layouts) {
        outLayouts->push_back(toMyLayout(l));
    }
    return OK;
}

// ======================================================================
// End of file
// ======================================================================
