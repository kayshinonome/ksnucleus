#include <utils.hpp>
#include <types.hpp>

extern "C"
{
    void *memset(void *bufptr, int value, size_t size)
    {
        set_memory(reinterpret_cast<uint8_t *>(bufptr), static_cast<uint8_t>(value), size);
        return bufptr;
    }
}
