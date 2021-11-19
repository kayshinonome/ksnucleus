#include <types.hpp>
#include <utils.hpp>

extern "C"
{
    void *memcpy(void *dest, const void *src, size_t size)
    {
        copy_memory(reinterpret_cast<const uint8_t *>(src), reinterpret_cast<uint8_t *>(dest), size);
        return dest;
    }
}