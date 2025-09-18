#include <vndk/window.h>

extern "C" {

AHardwareBuffer *
ANativeWindowBuffer_getHardwareBuffer(ANativeWindowBuffer *anwb)
{
   return nullptr;
}

void
AHardwareBuffer_acquire(AHardwareBuffer *buffer)
{
}

void
AHardwareBuffer_release(AHardwareBuffer *buffer)
{
}

void
AHardwareBuffer_describe(const AHardwareBuffer *buffer,
                         AHardwareBuffer_Desc *outDesc)
{
}

int
AHardwareBuffer_allocate(const AHardwareBuffer_Desc *desc,
                         AHardwareBuffer **outBuffer)
{
   return 0;
}

int
AHardwareBuffer_isSupported(const AHardwareBuffer_Desc* desc)
{
   return 0;
}

const native_handle_t *
AHardwareBuffer_getNativeHandle(const AHardwareBuffer *buffer)
{
   return NULL;
}

void
ANativeWindow_acquire(ANativeWindow *window)
{
}

void
ANativeWindow_release(ANativeWindow *window)
{
}

int32_t
ANativeWindow_getFormat(ANativeWindow *window)
{
   return 0;
}

int
ANativeWindow_setSwapInterval(ANativeWindow *window, int interval)
{
   return 0;
}

int
ANativeWindow_query(const ANativeWindow *window,
                    ANativeWindowQuery query,
                    int *value)
{
   return 0;
}

int
ANativeWindow_dequeueBuffer(ANativeWindow *window,
                            ANativeWindowBuffer **buffer,
                            int *fenceFd)
{
   return 0;
}

int
ANativeWindow_queueBuffer(ANativeWindow *window,
                          ANativeWindowBuffer *buffer,
                          int fenceFd)
{
   return 0;
}

int ANativeWindow_cancelBuffer(ANativeWindow* window,
                               ANativeWindowBuffer* buffer,
                               int fenceFd) {
   return 0;
}

int
ANativeWindow_setUsage(ANativeWindow *window, uint64_t usage)
{
   return 0;
}

int
ANativeWindow_setSharedBufferMode(ANativeWindow *window,
                                  bool sharedBufferMode)
{
   return 0;
}

native_handle_t* native_handle_create(int numFds, int numInts) {
	return 0;
}

native_handle_t* native_handle_clone(const native_handle_t* handle) {
    return (native_handle_t*)handle;
}

int native_handle_close(const native_handle_t* handle) {
    // Stub: pretend to close file descriptors
    return 0;
}

int native_handle_delete(native_handle_t* handle) {
    return 0;
}
}
