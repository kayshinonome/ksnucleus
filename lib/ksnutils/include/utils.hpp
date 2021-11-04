#pragma once
#include <atomic.hpp>
#include <types.hpp>

constexpr auto M_PI = 3.14159265358979311600;

/**
 * @brief Get the absolute value of a function
 *
 * @tparam T
 * @param x
 * @return T
 */
template <typename T> T abs(T x)
{
    return (x < 0) ? (-x) : (x);
}

/**
 * @brief Get a approximate for sin
 *
 * @tparam T
 * @param x
 * @return T
 */
template <typename T> T sin(T x)
{
    constexpr auto B = 4 / M_PI;
    constexpr auto C = -4 / (M_PI * M_PI);
    constexpr auto P = 0.225;

    auto y = B * x + C * x * abs(x);

    y = P * (y * abs(y) - y) + y;

    return y;
}

template <typename T> bool compare_memory(const T src[], const T dest[], size_t count)
{
    // No operation needs to happen here
    if (count == 0 || src == dest)
    {
        return true;
    }

    const size_t total_elements = sizeof(T) * count;
    const size_t left_over = total_elements % sizeof(size_t);
    const size_t mem_to_cpy = total_elements - left_over;

    for (size_t x = 0, len = mem_to_cpy / sizeof(size_t); x < len; x++)
    {
        if (*(reinterpret_cast<const size_t *>(dest) + x) != *(reinterpret_cast<const size_t *>(src) + x))
        {
            return false;
        }
    }

    if (left_over > 0)
    {
        for (size_t x = mem_to_cpy; x < total_elements; x++)
        {
            if (*(reinterpret_cast<const uint8_t *>(dest) + x) != *(reinterpret_cast<const uint8_t *>(src) + x))
            {
                return false;
            }
        }
    }

    return true;
}

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
