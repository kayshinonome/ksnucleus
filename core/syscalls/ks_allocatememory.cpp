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

    // FIXME: Make a quark call to make a actual memory table
    Memory_Table<10> hardware_memory_table{};
    hardware_memory_table[0] = {.memory = reinterpret_cast<void *>(0), .block_length = 1024, .is_reserved = false};
    auto result = hardware_memory_table.search(
        [size](auto search_term) { return (search_term.block_length <= size) && search_term.is_reserved; });

    if (!result.valid)
    {
        *buffer = nullptr;
    	return;
    }


}
