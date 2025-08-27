// property_get_shim.c
// Minimal libcutils-compatible shim for NDK builds.
// Provides: int property_get(const char* key, char* value, const char* default_value)

#include <sys/system_properties.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// Notes:
// - Caller must provide `value` buffer sized at least PROP_VALUE_MAX.
// - Returns number of bytes copied (excluding trailing NUL), or 0 if not set and no default.

int property_get(const char* key, char* value, const char* default_value) {
    if (!value) return 0;                    // no output buffer
    value[0] = '\0';

    if (!key || key[0] == '\0') {
        // Invalid key: just apply default if present
        if (default_value) {
            size_t dlen = strnlen(default_value, PROP_VALUE_MAX - 1);
            memcpy(value, default_value, dlen);
            value[dlen] = '\0';
            return (int)dlen;
        }
        return 0;
    }

    // Try to read the real system property
    char buf[PROP_VALUE_MAX];
    int len = __system_property_get(key, buf);  // Available in the NDK
    if (len > 0) {
        // len includes neither NUL nor overflow; ensure NUL terminate
        if ((size_t)len >= PROP_VALUE_MAX) len = PROP_VALUE_MAX - 1;
        memcpy(value, buf, (size_t)len);
        value[len] = '\0';
        return len;
    }

    // Not found: copy default if provided
    if (default_value) {
        size_t dlen = strnlen(default_value, PROP_VALUE_MAX - 1);
        memcpy(value, default_value, dlen);
        value[dlen] = '\0';
        return (int)dlen;
    }

    return 0;
}

#ifdef __cplusplus
} // extern "C"
#endif
