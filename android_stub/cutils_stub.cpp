#include <cutils/properties.h>
#include <cutils/trace.h>

extern "C" {

int
property_get(const char *key, char *value, const char *default_value)
{
   return 0;
}

void
atrace_begin_body(const char * /*name*/)
{
}

void
atrace_end_body()
{
}

void
atrace_init()
{
}

uint64_t
atrace_get_enabled_tags()
{
   return ATRACE_TAG_NOT_READY;
}

// android_stub/libnativehandle_stub.c
// Stubs for native_handle_* helpers

struct native_handle;

struct native_handle* native_handle_create(int numFds, int numInts) {
    (void)numFds; (void)numInts;
    return 0; // NULL
}

struct native_handle* native_handle_clone(const struct native_handle* handle) {
    (void)handle;
    return 0; // NULL
}

int native_handle_close(const struct native_handle* handle) {
    (void)handle;
    return 0; // success
}

int native_handle_delete(struct native_handle* handle) {
    (void)handle;
    return 0; // success
}

int native_handle_init(void*, int, int) {
 return 0;
}

}
