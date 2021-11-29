#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <math.hpp>
#include <types.hpp>

SUBSYSCALL ks_random(void *buffer, size_t length)
{
    constexpr auto rand_buffer_size = 0xff;
    constexpr char gen =
        (__TIME__[__SIZEOF_POINTER__] ^ __DATE__[__SIZEOF_FLOAT__] ^ __FILE__[__SIZEOF_INT__]) % rand_buffer_size;

    // Since its static, I will lock it with Atomic
    static Array<Atomic<uint8_t>, rand_buffer_size> rand_buffer;

    for (size_t i = 0; i < length; i++)
    {

        auto pos = gen * length % rand_buffer_size;
        rand_buffer[pos % rand_buffer_size] ^= sin(gen * i);
        rand_buffer[pos % rand_buffer_size] += sin(gen * i);

        reinterpret_cast<Atomic<uint8_t> *>(buffer)[i] = rand_buffer[pos];
    }
}