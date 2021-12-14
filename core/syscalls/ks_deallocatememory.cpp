#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <memory/memory_table.hpp>
#include <quark.hpp>
#include <types.hpp>

SUBSYSCALL ks_deallocatememory(void **buffer)
{

    if (buffer == nullptr)
    {
        return;
    }
    auto answer = allocated_memory_table.search(
        [buffer](auto search_term) { return search_term.is_reserved && search_term.memory == *buffer; });

    if (answer.valid)
    {
    }
}
