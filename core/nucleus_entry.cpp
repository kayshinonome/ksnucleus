#include <arch/x86/cpuid.hpp>
#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <math.hpp>
#include <types.hpp>
#include <video/framebuffer.hpp>

extern "C"
{
    __attribute__((used)) void nucleus_entry()
    {
        // Create buffer, filled with zero
        Array<uint8_t, 10> buffer{};

        // Get the buffer length
        size_t length = buffer.length();

        // Construct a array to hold the syscall arguments
        Array<void *, 2> arg_list{&buffer, &length};

        // Make the syscall to fill the buffer with random numbers
        mk_syscall(reinterpret_cast<void **>(&arg_list), KsSyscallID::RANDOM);

        // Sort the buffer
        buffer.sort([](const uint8_t &x, const uint8_t &y) { return sin(pow(x, y)) > sin(x * y); });
        // Array<Array<uint8_t, 2>, 2> array2d = {{2, 2}, {2, 2}};
    }
}