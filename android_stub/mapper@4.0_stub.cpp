// imapper4_symbols_stub.cpp
// Priority headers: VNDK/NDK/HIDL
#include <android/hardware/graphics/mapper/4.0/IMapper.h>
#include <hidl/HidlSupport.h>
#include <hidl/Status.h>
#include <utils/StrongPointer.h>

namespace ah = ::android::hardware;
namespace mapper4 = ::android::hardware::graphics::mapper::V4_0;

// ---------- IBase virtuals (inherited by IMapper) ----------

ah::Return<void>
mapper4::IMapper::interfaceChain(interfaceChain_cb cb) {
    cb({ "android.hardware.graphics.mapper@4.0::IMapper",
         "android.hidl.base@1.0::IBase" });
    return {};
}

ah::Return<void>
mapper4::IMapper::debug(const ah::hidl_handle&, const ah::hidl_vec<ah::hidl_string>&) {
    return {};
}

ah::Return<void>
mapper4::IMapper::interfaceDescriptor(interfaceDescriptor_cb cb) {
    cb("android.hardware.graphics.mapper@4.0::IMapper");
    return {};
}

ah::Return<void>
mapper4::IMapper::getHashChain(getHashChain_cb cb) {
    cb(ah::hidl_vec<ah::hidl_array<uint8_t, 32>>{});
    return {};
}

ah::Return<void>
mapper4::IMapper::setHALInstrumentation() {
    return {};
}

ah::Return<bool>
mapper4::IMapper::linkToDeath(const ::android::sp<ah::hidl_death_recipient>&, uint64_t) {
    return false;
}

ah::Return<void>
mapper4::IMapper::ping() {
    return {};
}

ah::Return<void>
mapper4::IMapper::getDebugInfo(getDebugInfo_cb cb) {
    cb({});
    return {};
}

ah::Return<void>
mapper4::IMapper::notifySyspropsChanged() {
    return {};
}

ah::Return<bool>
mapper4::IMapper::unlinkToDeath(const ::android::sp<ah::hidl_death_recipient>&) {
    return false;
}

// ---------- IMapper@4.0 virtuals ----------

ah::Return<void>
mapper4::IMapper::createDescriptor(const BufferDescriptorInfo&, createDescriptor_cb cb) {
    cb(Error::NONE, ah::hidl_vec<uint8_t>{});
    return {};
}

ah::Return<void>
mapper4::IMapper::importBuffer(const ah::hidl_handle&, importBuffer_cb cb) {
    cb(Error::NONE, nullptr);
    return {};
}

ah::Return<mapper4::Error>
mapper4::IMapper::freeBuffer(void*) {
    return Error::NONE;
}

ah::Return<mapper4::Error>
mapper4::IMapper::validateBufferSize(void*, const BufferDescriptorInfo&, uint32_t) {
    return Error::NONE;
}

ah::Return<void>
mapper4::IMapper::getTransportSize(void*, getTransportSize_cb cb) {
    cb(Error::NONE, 0u, 0u);
    return {};
}

ah::Return<void>
mapper4::IMapper::flushLockedBuffer(void*, flushLockedBuffer_cb cb) {
    cb(Error::NONE, ah::hidl_handle{});
    return {};
}

ah::Return<mapper4::Error>
mapper4::IMapper::rereadLockedBuffer(void*) {
    return Error::NONE;
}

// Lock / Unlock

ah::Return<void>
mapper4::IMapper::lock(void*,
                       uint64_t,
                       const mapper4::IMapper::Rect&,
                       const ah::hidl_handle&,
                       lock_cb cb) {
    cb(Error::NONE, nullptr);
    return {};
}

ah::Return<void>
mapper4::IMapper::unlock(void*, unlock_cb cb) {
    cb(Error::NONE, ah::hidl_handle{});
    return {};
}

// Dumps

ah::Return<void>
mapper4::IMapper::dumpBuffer(void*, dumpBuffer_cb cb) {
    mapper4::IMapper::BufferDump dump{};
    cb(Error::NONE, dump);
    return {};
}

ah::Return<void>
mapper4::IMapper::dumpBuffers(dumpBuffers_cb cb) {
    cb(Error::NONE, ah::hidl_vec<mapper4::IMapper::BufferDump>{});
    return {};
}

// Capabilities / queries

ah::Return<void>
mapper4::IMapper::isSupported(const BufferDescriptorInfo&, isSupported_cb cb) {
    cb(Error::NONE, true);
    return {};
}

ah::Return<void>
mapper4::IMapper::getReservedRegion(void*, getReservedRegion_cb cb) {
    cb(Error::NONE, nullptr, 0u);
    return {};
}

ah::Return<void>
mapper4::IMapper::listSupportedMetadataTypes(listSupportedMetadataTypes_cb cb) {
    cb(Error::NONE, ah::hidl_vec<mapper4::IMapper::MetadataTypeDescription>{});
    return {};
}

// Metadata get/set

ah::Return<void>
mapper4::IMapper::get(void*,
                      const mapper4::IMapper::MetadataType&,
                      get_cb cb) {
    cb(Error::NONE, ah::hidl_vec<uint8_t>{});
    return {};
}

ah::Return<mapper4::Error>
mapper4::IMapper::set(void*,
                      const mapper4::IMapper::MetadataType&,
                      const ah::hidl_vec<uint8_t>&) {
    return Error::NONE;
}

// From descriptor info -> metadata blob

ah::Return<void>
mapper4::IMapper::getFromBufferDescriptorInfo(const BufferDescriptorInfo&,
                                              const mapper4::IMapper::MetadataType&,
                                              getFromBufferDescriptorInfo_cb cb) {
    cb(Error::NONE, ah::hidl_vec<uint8_t>{});
    return {};
}
