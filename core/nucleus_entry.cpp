#include <core/ksnucleus.hpp>
#include <utils.hpp>
#include <video/rendering.hpp>

extern "C"
{
    __attribute__((used)) void nucleus_entry()
    {

        // Buffer to fill randomly
        Array<uint8_t, 101> buffer{};

        // Length of the buffer
        size_t length = buffer.length();

        // Arg structure fo r the syscall to read
        Array<void *, 2> arg_array{&buffer, &length};

        // This isn't how this should be used, but this is for testing
        mk_syscall(reinterpret_cast<void **>(&arg_array), KsSyscallID::RANDOM);

        Framebuffer<uint8_t, 8, 8> a;
    }
}