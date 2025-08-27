// ==== TRUNK 1/N ==== START ====
// Headers & namespace scaffolding

#include <android/hardware_buffer.h>
#include <vector>
#include <cstdint>

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
    int32_t component;    // ComponentType
    int32_t bitsPerPixel; // bits per sample for this component
    int32_t offsetInBits; // bit offset within a pixel sample
};

struct PlaneLayout {
    int64_t offsetInBytes;
    int64_t strideInBytes;
    int64_t widthInSamples;
    int64_t heightInSamples;
    std::vector<PlaneLayoutComponent> components;
};

} } } } }

using aidl::android::hardware::graphics::common::PlaneLayout;
using aidl::android::hardware::graphics::common::PlaneLayoutComponent;
using aidl::android::hardware::graphics::common::ComponentType;

// ==== TRUNK 1/N ==== END ====
// ==== TRUNK 2/N ==== START ====
// Function definition and initial RGBA‑family formats

bool getPlaneLayouts(const AHardwareBuffer_Desc& desc,
                     std::vector<PlaneLayout>* out) {
    out->clear();

    // Helper lambda for 4‑component interleaved formats
    auto pushRGBA = [&](size_t bpp, int rOff, int gOff, int bOff, int aOff) {
        PlaneLayout plane{};
        plane.offsetInBytes = 0;
        plane.strideInBytes = static_cast<int64_t>(desc.stride * bpp);
        plane.widthInSamples = desc.width;
        plane.heightInSamples = desc.height;
        plane.components = {
            { ComponentType::COMPONENT_R, 8, rOff },
            { ComponentType::COMPONENT_G, 8, gOff },
            { ComponentType::COMPONENT_B, 8, bOff },
            { ComponentType::COMPONENT_A, 8, aOff }
        };
        out->push_back(std::move(plane));
    };

    switch (desc.format) {
    case AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM:
    case AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM_SRGB:
        pushRGBA(4, 0, 8, 16, 24);
        return true;

    case AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM:
    case AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM_SRGB:
        // RGBX uses the same memory layout as RGBA; alpha is ignored
        pushRGBA(4, 0, 8, 16, 24);
        return true;

    case AHARDWAREBUFFER_FORMAT_R16G16B16A16_FLOAT:
        // Each component is 16 bits (half float)
        pushRGBA(8, 0, 16, 32, 48);
        return true;

    case AHARDWAREBUFFER_FORMAT_R10G10B10A2_UNORM: {
        PlaneLayout plane{};
        plane.offsetInBytes = 0;
        plane.strideInBytes = static_cast<int64_t>(desc.stride * 4);
        plane.widthInSamples = desc.width;
        plane.heightInSamples = desc.height;
        plane.components = {
            { ComponentType::COMPONENT_R, 10, 0 },
            { ComponentType::COMPONENT_G, 10, 10 },
            { ComponentType::COMPONENT_B, 10, 20 },
            { ComponentType::COMPONENT_A,  2, 30 }
        };
        out->push_back(std::move(plane));
        return true;
    }
// ==== TRUNK 2/N ==== END ====
// ==== TRUNK 3/N ==== START ====

// RGB565
case AHARDWAREBUFFER_FORMAT_R5G6B5_UNORM: {
    PlaneLayout plane{};
    plane.offsetInBytes = 0;
    plane.strideInBytes = static_cast<int64_t>(desc.stride * 2);
    plane.widthInSamples = desc.width;
    plane.heightInSamples = desc.height;
    plane.components = {
        { ComponentType::COMPONENT_R, 5, 11 },
        { ComponentType::COMPONENT_G, 6, 5 },
        { ComponentType::COMPONENT_B, 5, 0 }
    };
    out->push_back(std::move(plane));
    return true;
}

// YUV 4:2:0, bi‑planar (NV12)
case AHARDWAREBUFFER_FORMAT_YCbCr_420_888:
case AHARDWAREBUFFER_FORMAT_Y8Cb8Cr8_420: {
    // Plane 0: Y
    PlaneLayout y{};
    y.offsetInBytes = 0;
    y.strideInBytes = static_cast<int64_t>(desc.stride);
    y.widthInSamples = desc.width;
    y.heightInSamples = desc.height;
    y.components = { { ComponentType::COMPONENT_Y, 8, 0 } };
    out->push_back(std::move(y));

    // Plane 1: CbCr interleaved
    PlaneLayout uv{};
    uv.offsetInBytes = y.strideInBytes * desc.height;
    uv.strideInBytes = static_cast<int64_t>(desc.stride);
    uv.widthInSamples = desc.width / 2;
    uv.heightInSamples = desc.height / 2;
    uv.components = {
        { ComponentType::COMPONENT_CB, 8, 0 },
        { ComponentType::COMPONENT_CR, 8, 8 }
    };
    out->push_back(std::move(uv));

    return true;
}

// YV12 (Y + V + U)
case AHARDWAREBUFFER_FORMAT_YV12: {
    PlaneLayout y{};
    y.offsetInBytes = 0;
    y.strideInBytes = static_cast<int64_t>(desc.stride);
    y.widthInSamples = desc.width;
    y.heightInSamples = desc.height;
    y.components = { { ComponentType::COMPONENT_Y, 8, 0 } };
    out->push_back(std::move(y));

    size_t y_size = y.strideInBytes * desc.height;
    size_t c_stride = ((desc.stride / 2) + 15) & ~15; // 16‑byte aligned

    PlaneLayout v{};
    v.offsetInBytes = y_size;
    v.strideInBytes = c_stride;
    v.widthInSamples = desc.width / 2;
    v.heightInSamples = desc.height / 2;
    v.components = { { ComponentType::COMPONENT_CR, 8, 0 } };
    out->push_back(std::move(v));

    PlaneLayout u{};
    u.offsetInBytes = y_size + c_stride * (desc.height / 2);
    u.strideInBytes = c_stride;
    u.widthInSamples = desc.width / 2;
    u.heightInSamples = desc.height / 2;
    u.components = { { ComponentType::COMPONENT_CB, 8, 0 } };
    out->push_back(std::move(u));

    return true;
}

// ==== TRUNK 3/N ==== END ====
// ==== TRUNK 4/N ==== START ====

// P010 (Y + UV, each 16‑bit, 4:2:0)
case AHARDWAREBUFFER_FORMAT_YCbCr_P010: {
    // Plane 0: Y (16 bits per sample)
    PlaneLayout y{};
    y.offsetInBytes = 0;
    y.strideInBytes = static_cast<int64_t>(desc.stride * 2);
    y.widthInSamples = desc.width;
    y.heightInSamples = desc.height;
    y.components = { { ComponentType::COMPONENT_Y, 16, 0 } };
    out->push_back(std::move(y));

    // Plane 1: UV (interleaved, 16 bits each)
    PlaneLayout uv{};
    uv.offsetInBytes = y.strideInBytes * desc.height;
    uv.strideInBytes = static_cast<int64_t>(desc.stride * 2);
    uv.widthInSamples = desc.width / 2;
    uv.heightInSamples = desc.height / 2;
    uv.components = {
        { ComponentType::COMPONENT_CB, 16, 0 },
        { ComponentType::COMPONENT_CR, 16, 16 }
    };
    out->push_back(std::move(uv));

    return true;
}

// Depth 16‑bit
case AHARDWAREBUFFER_FORMAT_D16_UNORM: {
    PlaneLayout depth{};
    depth.offsetInBytes = 0;
    depth.strideInBytes = static_cast<int64_t>(desc.stride * 2);
    depth.widthInSamples = desc.width;
    depth.heightInSamples = desc.height;
    depth.components = { { ComponentType::COMPONENT_DEPTH, 16, 0 } };
    out->push_back(std::move(depth));
    return true;
}

// Depth 24 + Stencil 8
case AHARDWAREBUFFER_FORMAT_D24_UNORM_S8_UINT: {
    PlaneLayout depthStencil{};
    depthStencil.offsetInBytes = 0;
    depthStencil.strideInBytes = static_cast<int64_t>(desc.stride * 4);
    depthStencil.widthInSamples = desc.width;
    depthStencil.heightInSamples = desc.height;
    depthStencil.components = {
        { ComponentType::COMPONENT_DEPTH, 24, 0 },
        { ComponentType::COMPONENT_STENCIL, 8, 24 }
    };
    out->push_back(std::move(depthStencil));
    return true;
}

// Depth 32‑bit float
case AHARDWAREBUFFER_FORMAT_D32_FLOAT: {
    PlaneLayout depth{};
    depth.offsetInBytes = 0;
    depth.strideInBytes = static_cast<int64_t>(desc.stride * 4);
    depth.widthInSamples = desc.width;
    depth.heightInSamples = desc.height;
    depth.components = { { ComponentType::COMPONENT_DEPTH, 32, 0 } };
    out->push_back(std::move(depth));
    return true;
}

// Default: unsupported format
default:
    return false;
}
// ==== TRUNK 4/N ==== END ====
// ==== TRUNK 5/N ==== START ====

// End of getPlaneLayouts function
} // closes getPlaneLayouts

// Optional: helper to dump a PlaneLayout for debugging
#include <iostream>

static void printPlaneLayouts(const std::vector<PlaneLayout>& layouts) {
    for (size_t i = 0; i < layouts.size(); ++i) {
        const auto& p = layouts[i];
        std::cout << "Plane " << i
                  << ": offset=" << p.offsetInBytes
                  << " stride=" << p.strideInBytes
                  << " width=" << p.widthInSamples
                  << " height=" << p.heightInSamples << "\n";
        for (const auto& c : p.components) {
            std::cout << "    Component " << c.component
                      << ": bits=" << c.bitsPerPixel
                      << " offsetBits=" << c.offsetInBits << "\n";
        }
    }
}

// Example usage
/*
#include <android/hardware_buffer.h>

AHardwareBuffer* buffer = nullptr;
AHardwareBuffer_Desc desc{};
AHardwareBuffer_allocate(&(AHardwareBuffer_Desc){
    .width = 1920,
    .height = 1080,
    .layers = 1,
    .format = AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM,
    .usage = AHARDWAREBUFFER_USAGE_CPU_READ_RARELY | AHARDWAREBUFFER_USAGE_GPU_SAMPLED_IMAGE
}, &buffer);

AHardwareBuffer_describe(buffer, &desc);

std::vector<PlaneLayout> layouts;
if (getPlaneLayouts(desc, &layouts)) {
    printPlaneLayouts(layouts);
} else {
    std::cout << "Unsupported format\n";
}

AHardwareBuffer_release(buffer);
*/

// ==== TRUNK 5/N ==== END ====
