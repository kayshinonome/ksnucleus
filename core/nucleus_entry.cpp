#include <arch/x86/cpuid.hpp>
#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <types.hpp>
#include <video/framebuffer.hpp>

extern "C"
{
    __attribute__((used)) void nucleus_entry()
    {
        Array<uint8_t, 10> sort_test{};
        Array<uint8_t, 10> buffer{};
        size_t length = buffer.length();
        Array<void *, 2> arg_list{&buffer, &length};
        mk_syscall(reinterpret_cast<void **>(&arg_list), KsSyscallID::RANDOM);
        buffer.sort([](const uint8_t &first, const uint8_t &second) { return first > second; });
    }
}