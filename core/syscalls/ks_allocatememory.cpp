#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <core/quark.hpp>
#include <memory/memory_table.hpp>
#include <types.hpp>

SUBSYSCALL ks_allocatememory(void **buffer, uint32_t size)
{
    if (buffer == nullptr)
    {
        ks_fission("Attempt to allocate with nullptr");
    }

    if (size == 0)
    {
        *buffer = nullptr;
        return;
    }
}