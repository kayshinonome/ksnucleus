#pragma once
#include <utils.hpp>

// FIXME: Make a better version of this function

template <typename T> void set_memory(T dest[], uint8_t value, size_t count)
{

    /**
     * @brief If count equals zero, no operation needs to happen
     *
     */
    if (count == 0)
    {
        return;
    }

    size_t expanded_value = 0;
    const size_t total_elements = sizeof(T) * count;
    const size_t left_over = total_elements % sizeof(size_t);
    const size_t mem_to_cpy = total_elements - left_over;

    /**
     * @brief Using this function to zero out data is common, so we will directly assign expanded_value and skip the
     * loop
     *
     */
    if (value != 0)
    {
        expanded_value = value;

        // Make a size_t filled with here the value
        for (size_t x = 0, len = sizeof(size_t); x < len; x++)
        {
            expanded_value <<= sizeof(value) * 8;
            expanded_value |= value;
        }
    }

    for (size_t x = 0, len = mem_to_cpy / sizeof(size_t); x < len; x++)
    {
        *(reinterpret_cast<size_t *>(dest) + x) = expanded_value;
    }

    if (left_over > 0)
    {
        for (size_t x = mem_to_cpy; x < total_elements; x++)
        {
            *(reinterpret_cast<uint8_t *>(dest) + x) = value;
        }
    }
}
