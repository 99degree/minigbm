// Minimal stub implementations to satisfy HIDL base symbols without linking libhidlbase/libutils.
// Drop this entire file into your build and compile as a single TU.

#include <utils/RefBase.h>
#include <hidl/HidlSupport.h>
#include <android/hidl/base/1.0/IBase.h>
#include <cutils/native_handle.h>
#include <string>
#include <hidl/HidlSupport.h>
//#include <hidl/IBase.h>

using ::android::hardware::Return;
using ::android::hardware::hidl_handle;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hidl::base::V1_0::DebugInfo;

//
// ---- RefBase stubs ----
// Place before namespace android::hidl::base
//
namespace android {

RefBase::~RefBase() {}

void RefBase::onFirstRef() {}
void RefBase::onLastStrongRef(const void*) {}
bool RefBase::onIncStrongAttempted(uint32_t, const void*) { return false; }
void RefBase::onLastWeakRef(const void*) {}

} // namespace android

//
// ---- IBase stubs ----
//
namespace android {
namespace hidl {
namespace base {
namespace V1_0 {

Return<void> IBase::interfaceChain(interfaceChain_cb) { return Return<void>(); }
Return<void> IBase::interfaceDescriptor(interfaceDescriptor_cb) { return Return<void>(); }
Return<void> IBase::getHashChain(getHashChain_cb) { return Return<void>(); }
Return<void> IBase::debug(const hidl_handle&, const hidl_vec<hidl_string>&) { return Return<void>(); }
Return<void> IBase::setHALInstrumentation() { return Return<void>(); }
Return<bool> IBase::linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>&, uint64_t) { return false; }
Return<bool> IBase::unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>&) { return false; }
Return<void> IBase::ping() { return Return<void>(); }
Return<void> IBase::getDebugInfo(getDebugInfo_cb) { return Return<void>(); }
Return<void> IBase::notifySyspropsChanged() { return Return<void>(); }

} // namespace V1_0
} // namespace base
} // namespace hidl
} // namespace android

//
// ---- hidl_string stubs ----
//
namespace android {
namespace hardware {

// Commonly referenced constructors/destructor/operators
hidl_string::hidl_string() {}
hidl_string::hidl_string(const char* /*s*/) {}
hidl_string::hidl_string(const hidl_string& /*other*/) {}
hidl_string::hidl_string(hidl_string&& /*other*/) noexcept {}
hidl_string::~hidl_string() {}

hidl_string& hidl_string::operator=(const hidl_string& /*other*/) { return *this; }
hidl_string& hidl_string::operator=(hidl_string&& /*other*/) noexcept { return *this; }

// Optional conversion used by some code paths
hidl_string::operator std::string() const {
    return std::string();
}

} // namespace hardware
} // namespace android

//
// ---- hidl_handle stubs ----
//
namespace android {
namespace hardware {

hidl_handle::hidl_handle() {}
hidl_handle::~hidl_handle() {}
hidl_handle::hidl_handle(const native_handle* /*handle*/) {}
hidl_handle::hidl_handle(const hidl_handle& /*other*/) {}
hidl_handle::hidl_handle(hidl_handle&& /*other*/) noexcept {}
hidl_handle& hidl_handle::operator=(const hidl_handle& /*other*/) { return *this; }
hidl_handle& hidl_handle::operator=(hidl_handle&& /*other*/) noexcept { return *this; }

const native_handle* hidl_handle::getNativeHandle() const { return nullptr; }
void hidl_handle::setTo(native_handle* /*handle*/, bool /*shouldOwn*/) {}

} // namespace hardware
} // namespace android

//
// ---- RPC threadpool stubs ----
//
namespace android {
namespace hardware {
void configureRpcThreadpool(unsigned long /*maxThreads*/, bool /*callerWillJoin*/) {}
void joinRpcThreadpool() {}
} // namespace hardware
} // namespace android


// hidlbase_stub.cpp
#include <hidl/HidlTransportSupport.h>
#include <hidl/Status.h>
#include <hidl/ServiceManagement.h>
#include <utils/StrongPointer.h>
#include <utils/RefBase.h>

using namespace android;
using namespace android::hardware;

// ---- Threadpool control ----
void configureRpcThreadpool(size_t /*maxThreads*/, bool /*callerWillJoin*/) {}
void joinRpcThreadpool() {}

// ---- Service manager ----
//sp<IServiceManager> defaultServiceManager() { return nullptr; }
bool registerPassthroughServiceImplementation(const std::string& /*serviceName*/) { return false; }
bool registerPassthroughServiceImplementation(const std::string& /*serviceName*/, const std::string& /*instance*/) { return false; }

// ---- IBase helpers ----
//Return<bool> android::hidl::base::V1_0::IBase::linkToDeath(const sp<hidl_death_recipient>& /*recipient*/, uint64_t /*cookie*/) { return true; }
//Return<bool> android::hidl::base::V1_0::IBase::unlinkToDeath(const sp<hidl_death_recipient>& /*recipient*/) { return true; }

// ---- Status ----
//void Status::setException(int32_t /*exceptionCode*/, const std::string& /*message*/) {}
//void Status::setTransactionError(int32_t /*transactionError*/) {}

// ---- StrongPointer / RefBase stubs ----
void RefBase::incStrong(const void* /*id*/) const {}
void RefBase::decStrong(const void* /*id*/) const {}

// Add to your existing stubs.cpp
namespace android {
namespace hardware {
namespace details {

void logAlwaysFatal(char const* /*msg*/) {
    // no-op: real version logs and aborts
}

} // namespace details
} // namespace hardware
} // namespace android

#include <hidl/HidlSupport.h>

namespace android {
namespace hardware {

const char* hidl_string::c_str() const {
    // Return an empty string in the stub build
    return "";
}

} // namespace hardware
} // namespace android

// Stub for android::hardware::details::return_status::~return_status()

namespace android {
namespace hardware {
namespace details {

return_status::~return_status() {
    // no-op stub
}

} // namespace details
} // namespace hardware
} // namespace android
