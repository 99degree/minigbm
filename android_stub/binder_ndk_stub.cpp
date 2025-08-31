#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <android/binder_parcel.h>
#include <android/binder_ibinder.h>
#include <android/binder_status.h>
#include <android/binder_ibinder.h>
#include <android/binder_parcel.h>
#include <android/binder_status.h>
#include <hidl/HidlSupport.h>

extern "C" {

// ---- Service manager ----
binder_exception_t AServiceManager_addService(AIBinder* /*binder*/, const char* /*instance*/) {
    return EX_NONE;
}
AIBinder* AServiceManager_getService(const char* /*instance*/) { return nullptr; }
AIBinder* AServiceManager_waitForService(const char* /*instance*/) { return nullptr; }

// ---- Process / threadpool ----
void ABinderProcess_startThreadPool() {}
void ABinderProcess_joinThreadPool() {}
bool ABinderProcess_setThreadPoolMaxThreadCount(uint32_t /*numThreads*/) { return true; }
bool ABinderProcess_setThreadPoolMaxThreadCountWithPriority(uint32_t /*numThreads*/, int /*priority*/) { return true; }

// ---- IBinder basics ----
AIBinder* AIBinder_new(const AIBinder_Class* /*clazz*/, void* /*userData*/) { return nullptr; }
void AIBinder_decStrong(AIBinder* /*binder*/) {}
void AIBinder_incStrong(AIBinder* /*binder*/) {}
binder_status_t AIBinder_ping(AIBinder* /*binder*/) { return STATUS_OK; }
binder_status_t AIBinder_dump(AIBinder* /*binder*/, int /*fd*/, const char** /*args*/, uint32_t /*numArgs*/) { return STATUS_OK; }
binder_status_t AIBinder_linkToDeath(AIBinder* /*binder*/, AIBinder_DeathRecipient* /*recipient*/, void* /*cookie*/) { return STATUS_OK; }
binder_status_t AIBinder_unlinkToDeath(AIBinder* /*binder*/, AIBinder_DeathRecipient* /*recipient*/, void* /*cookie*/) { return STATUS_OK; }

// ---- Parcel basics ----
binder_status_t AParcel_writeInt32(AParcel* /*parcel*/, int32_t /*value*/) { return STATUS_OK; }
binder_status_t AParcel_readInt32(const AParcel* /*parcel*/, int32_t* /*value*/) { return STATUS_OK; }
binder_status_t AParcel_writeString(AParcel* /*parcel*/, const char* /*string*/, int32_t /*length*/) { return STATUS_OK; }
binder_status_t AParcel_readString(const AParcel* /*parcel*/, void* /*stringData*/, AParcel_stringAllocator /*allocator*/) { return STATUS_OK; }
binder_status_t AParcel_writeStatusHeader(AParcel* /*parcel*/, const AStatus* /*status*/) { return STATUS_OK; }
binder_status_t AParcel_readStatusHeader(const AParcel* /*parcel*/, AStatus** /*status*/) { return STATUS_OK; }

binder_status_t AParcel_setDataPosition(const AParcel* /*parcel*/, int32_t /*position*/) { return STATUS_OK; }
int32_t AParcel_getDataPosition(const AParcel* /*parcel*/) { return 0; }
int32_t AParcel_dataSize(const AParcel* /*parcel*/) { return 0; }

// ---- Status ----
AStatus* AStatus_newOk() { return nullptr; }
AStatus* AStatus_fromStatus(binder_status_t /*status*/) { return nullptr; }
void AStatus_delete(AStatus* /*status*/) {}
binder_status_t AStatus_getStatus(const AStatus* /*status*/) { return STATUS_OK; }

} // extern "C"

extern "C" {

// ---- Parcel array helpers ----
binder_status_t AParcel_readParcelableArray(const AParcel* parcel, void* arrayData,
                                            AParcel_parcelableArrayAllocator allocator,
                                            AParcel_readParcelableElement elementReader) { return STATUS_OK; }
binder_status_t AParcel_writeParcelableArray(AParcel* parcel, const void* arrayData, int32_t length,
                                             AParcel_writeParcelableElement elementWriter) { return STATUS_OK; }
binder_status_t AParcel_readInt32Array(const AParcel* /*parcel*/, void* /*arrayData*/, AParcel_int32ArrayAllocator /*allocator*/) { return STATUS_OK; }
binder_status_t AParcel_writeInt32Array(AParcel* /*parcel*/, const int32_t* /*array*/, int32_t /*length*/) { return STATUS_OK; }

// ---- Parcel FD helpers ----
binder_status_t AParcel_readParcelFileDescriptor(const AParcel* /*parcel*/, int* /*fd*/) { return STATUS_OK; }
binder_status_t AParcel_writeParcelFileDescriptor(AParcel* /*parcel*/, int /*fd*/) { return STATUS_OK; }

// ---- Binder object helpers ----
void* AIBinder_getUserData(AIBinder* /*binder*/) { return nullptr; }
binder_status_t AIBinder_prepareTransaction(AIBinder* /*binder*/, AParcel** /*inParcel*/) { return STATUS_OK; }

// ---- Status helpers ----
bool AStatus_isOk(const AStatus* /*status*/) { return true; }

// ---- Byte/bool helpers ----
binder_status_t AParcel_readByteArray(const AParcel* /*parcel*/, void* /*arrayData*/, AParcel_byteArrayAllocator /*allocator*/) { return STATUS_OK; }
binder_status_t AParcel_writeBool(AParcel* /*parcel*/, bool /*value*/) { return STATUS_OK; }
binder_status_t AParcel_writeByteArray(AParcel* parcel, const int8_t* arrayData, int32_t length)  { return STATUS_OK; }
// ---- Lifecycle ----
void AParcel_delete(AParcel* /*parcel*/) {}

} // extern "C"

// binder_ndk_stubs.cpp
#include <android/binder_ibinder.h>
#include <android/binder_parcel.h>
#include <android/binder_status.h>

extern "C" {

// Status helpers
AStatus* AStatus_fromServiceSpecificError(int32_t /*serviceSpecific*/) {
    return nullptr;
}

// Binder functions
//binder_status_t AIBinder_transact(AIBinder* /*binder*/, transaction_code_t /*code*/,
//                                  AParcel* /*in*/, AParcel* /*out*/, binder_flags_t /*flags*/) 
binder_status_t AIBinder_transact(AIBinder* binder, transaction_code_t code, AParcel** in,
                                  AParcel** out, binder_flags_t flags)
{
    return STATUS_UNKNOWN_ERROR;
}

bool AIBinder_isRemote(const AIBinder* binder)
{
    return false;
}

binder_status_t AIBinder_setInheritRt(AIBinder* /*binder*/, bool /*inherit*/) {
    return STATUS_UNKNOWN_ERROR;
}

//void AIBinder_associateClass(AIBinder* /*binder*/, const AIBinder_Class* /*clazz*/) {}
bool AIBinder_associateClass(AIBinder* binder, const AIBinder_Class* clazz) {
    return 0;
}

AIBinder_Weak* AIBinder_Weak_new(AIBinder* /*binder*/) {
    return nullptr;
}

AIBinder* AIBinder_Weak_promote(AIBinder_Weak* /*weak*/) {
    return nullptr;
}

void AIBinder_Weak_delete(AIBinder_Weak* /*weak*/) {}

// Parcel helpers
binder_status_t AParcel_readBool(const AParcel* /*parcel*/, bool* /*value*/) {
    return STATUS_UNKNOWN_ERROR;
}

binder_status_t AParcel_writeStrongBinder(AParcel* /*parcel*/, AIBinder* /*binder*/) {
    return STATUS_UNKNOWN_ERROR;
}

binder_status_t AParcel_readStrongBinder(const AParcel* /*parcel*/, AIBinder** /*binder*/) {
    return STATUS_UNKNOWN_ERROR;
}

// Parcel int64 helpers
binder_status_t AParcel_readInt64(const AParcel* /*parcel*/, int64_t* /*value*/) {
    return STATUS_UNKNOWN_ERROR;
}

binder_status_t AParcel_writeInt64(AParcel* /*parcel*/, int64_t /*value*/) {
    return STATUS_UNKNOWN_ERROR;
}

// Binder class helpers
AIBinder_Class* AIBinder_Class_define(const char* /*interfaceDescriptor*/,
                                      AIBinder_Class_onCreate /*onCreate*/,
                                      AIBinder_Class_onDestroy /*onDestroy*/,
                                      AIBinder_Class_onTransact /*onTransact*/) {
    return nullptr;
}

} // extern "C"

#ifndef AIBinder_Class_onDump
typedef binder_status_t (*AIBinder_Class_onDump)(
    AIBinder* binder, int fd, const char** args, uint32_t numArgs);
#endif

extern "C" {
void AIBinder_Class_setOnDump(AIBinder_Class* /*clazz*/,
                              AIBinder_Class_onDump /*onDump*/) {
    // no-op
}
}
