// libcxx_stub.c
__attribute__((visibility("default")))
void __libcxx_stub_symbol(void) {
    // no-op
}

extern "C" void __cxa_pure_virtual() {
    // This should never be called — abort to be safe
    __builtin_trap();
}
