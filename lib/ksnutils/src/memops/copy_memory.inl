#pragma once

#include <utils.hpp>

template <typename T> void copy_memory(const T src[], T dest[], size_t count)
{
    // No operation needs to happen here
    if (count == 0 || src == dest)
    {
        return;
    }

    const size_t total_elements = sizeof(T) * count;
    const size_t left_over = total_elements % sizeof(size_t);
    const size_t mem_to_cpy = total_elements - left_over;

    for (size_t x = 0, len = mem_to_cpy / sizeof(size_t); x < len; x++)
    {
        *(reinterpret_cast<size_t *>(dest) + x) = *(reinterpret_cast<const size_t *>(src) + x);
    }

    if (left_over > 0)
    {
        for (size_t x = mem_to_cpy; x < total_elements; x++)
        {
            *(reinterpret_cast<uint8_t *>(dest) + x) = *(reinterpret_cast<const uint8_t *>(src) + x);
        }
    }
}