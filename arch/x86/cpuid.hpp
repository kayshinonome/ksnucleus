#pragma once
#include <array.hpp>
#include <types.hpp>

void inline cpuid(size_t *eax, size_t *ebx, size_t *ecx, size_t *edx)
{
    // ecx is often an input as well as an output.
    asm volatile("cpuid" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "0"(*eax), "2"(*ecx));
}

/**
 * @brief Get the highest function parameter of cpuid
 *
 * @return uint32_t
 */
uint32_t inline highest_function_parameter()
{
    size_t eax = 0;
    size_t unused = 0;
    cpuid(&eax, &unused, &unused, &unused);
    return eax;
}

/**
 * @brief Get the manufacturer_id
 *
 * @param buffer
 */
void inline manufacturer_id(Array<char, 12> buffer)
{
    size_t eax = 0;
    constexpr auto word_size = sizeof(size_t);

    // Load directly into the buffer from the cpuid helper function
    cpuid(&eax, reinterpret_cast<size_t *>(buffer.raw()), reinterpret_cast<size_t *>(buffer.raw() + (word_size * 2)),
          reinterpret_cast<size_t *>(buffer.raw() + word_size));
}
