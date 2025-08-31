#include <cstdint>
#include <cstddef>
#include <string>
#include <stdarg.h>

namespace android {

// ───────────── RefBase ─────────────
class RefBase {
public:
    RefBase() {}
    virtual ~RefBase() {}

    virtual void onFirstRef() {}
    virtual void onLastStrongRef(const void*) {}
    virtual bool onIncStrongAttempted(uint32_t, const void*) { return true; }
    virtual void onLastWeakRef(const void*) {}

    void incStrong(const void*) {}
    void decStrong(const void*) {}
    int32_t getStrongCount() const { return 1; }
};

// Dummy subclass to force vtable emission
class DummyRefBase : public RefBase {
public:
    DummyRefBase() = default;
    ~DummyRefBase() override = default;
};

// ───────────── Logging ─────────────
extern "C" void __android_log_print(int, const char*, const char*, ...) {}
extern "C" void __android_log_write(int, const char*, const char*) {}
extern "C" void __android_log_vprint(int, const char*, const char*, va_list) {}

void ALOGE(const char* fmt, ...) {}
void ALOGW(const char* fmt, ...) {}
void ALOGI(const char* fmt, ...) {}
void ALOGD(const char* fmt, ...) {}

} // namespace android

// Force symbol emission
extern "C" void __emit_refbase_symbols__() {
    android::DummyRefBase dummy;
    android::ALOGE("RefBase stub active");
}
