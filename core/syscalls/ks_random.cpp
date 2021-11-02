#include <core/ksnucleus.hpp>
#include <utils.hpp>

SYSCALL ks_random(void *buffer, size_t length)
{
    constexpr auto rand_buffer_size = 0xff;
    constexpr auto gen =
        (__TIME__[__SIZEOF_POINTER__] ^ __DATE__[__SIZEOF_FLOAT__] ^ __FILE__[__SIZEOF_INT__]) % rand_buffer_size;
    static Array<uint8_t, rand_buffer_size> rand_buffer;

    for (size_t i = 0; i < length; i++)
    {

        size_t pos = gen * length % rand_buffer_size;
        rand_buffer[pos % rand_buffer_size] ^= gen;

        reinterpret_cast<uint8_t *>(buffer)[i] = rand_buffer[pos];
    }
}