#if 0
// hidl_string_shim.cpp
#include <string>
#include <cstring>

namespace android {
namespace hardware {

struct hidl_string {
    std::string _data;

    hidl_string() = default;
    hidl_string(const char* s) : _data(s ? s : "") {}
    hidl_string(const std::string& s) : _data(s) {}

    const char* c_str() const { return _data.c_str(); }
    size_t size() const { return _data.size(); }

    // Only keep this operator — matches mangled symbol in libc++
    operator std::__ndk1::basic_string<char,
                                       std::__ndk1::char_traits<char>,
                                       std::__ndk1::allocator<char>>() const {
        return { _data.c_str(), _data.size() };
    }
};

} // namespace hardware
} // namespace android
#endif

#if 0
// String_shim.cpp — drop‑in to satisfy missing conversion operator
#include <android/hardware/hidl_string.h>
#include <string>

namespace android {
namespace hardware {

// Out‑of‑line definition for the conversion operator
// Matches: android::hardware::hidl_string::operator std::__ndk1::basic_string<...>() const
operator std::__ndk1::basic_string<char,
                                   std::__ndk1::char_traits<char>,
                                   std::__ndk1::allocator<char>>() const {
    return { this->c_str(), this->size() };
}

} // namespace hardware
} // namespace android

#endif
// String_shim.cpp – minimal ABI‑compatible stand‑in
#if 0
#include <string>

namespace android {
namespace hardware {

struct hidl_string {
    std::string _data;

    hidl_string() = default;
    hidl_string(const char* s) : _data(s ? s : "") {}
    hidl_string(const std::string& s) : _data(s) {}

    const char* c_str() const { return _data.c_str(); }
    size_t size() const { return _data.size(); }

    // This is the exact operator signature the linker is missing
    operator std::__ndk1::basic_string<char,
                                       std::__ndk1::char_traits<char>,
                                       std::__ndk1::allocator<char>>() const {
        return { _data.c_str(), _data.size() };
    }
};

} // namespace hardware
} // namespace android

//android::hardware::hidl_string::operator std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char>>() const
#endif
// FauxHidlString.h
#pragma once
#include <string>

namespace android {
namespace hardware {

// Minimal shim with same name & namespace as real hidl_string
class hidl_string {
public:
    // underlying storage
    std::string data_;

    // ctors
    hidl_string() = default;
    hidl_string(const char* s) : data_(s ? s : "") {}
    hidl_string(const std::string& s) : data_(s) {}
    
    // assignment
    hidl_string& operator=(const char* s) {
        data_ = (s ? s : "");
        return *this;
    }
    hidl_string& operator=(const std::string& s) {
        data_ = s;
        return *this;
    }

    // c_str accessor (matches HIDL API)
    const char* c_str() const noexcept { return data_.c_str(); }
    
    // size accessor
    size_t size() const noexcept { return data_.size(); }
    
    // implicit conversion to std::string if desired
    operator std::string() const { return data_; }
};

} // namespace hardware
} // namespace android

