#pragma once
#include <atomic.hpp>
#include <types.hpp>

/**
 * @brief Compare two blocks of memory (CANNOT BE OPTIMIZED AWAY)
 *
 * @tparam T
 * @param src
 * @param dest
 * @param count
 * @return true
 * @return false
 */
template <typename T> bool compare_memory(const T src[], const T dest[], size_t count)
{
    // No operation needs to happen here
    if (count == 0 || src == dest)
    {
        return true;
    }

    for (size_t x = 0; x < count; x++)
    {
        if (*(reinterpret_cast<const T *>(dest) + x) != *(reinterpret_cast<const T *>(src) + x))
        {
            return false;
        }
    }
    return false;
}

/**
 * @brief Copy memory from one location to another (CANNOT BE OPTIMIZED AWAY)
 *
 * @tparam T
 * @param src
 * @param dest
 * @param count
 */
template <typename T> void copy_memory(const T src[], T dest[], size_t count)
{
    // No operation needs to happen here
    if (count == 0 || src == dest)
    {
        return;
    }

    for (size_t x = 0; x < count; x++)
    {
        *(reinterpret_cast<T *>(dest) + x) = *(reinterpret_cast<const T *>(src) + x);
    }
}

/**
 * @brief Set all memory specified to a value (CANNOT BE OPTIMIZED AWAY)
 *
 * @tparam T
 * @param dest
 * @param value
 * @param count
 */
template <typename T> void set_memory(T dest[], T value, size_t count)
{

    /**
     * @brief If count equals zero, no operation needs to happen
     *
     */
    if (count == 0)
    {
        return;
    }

    for (size_t x = 0, len = count; x < len; x++)
    {
        *(reinterpret_cast<T *>(dest) + x) = value;
    }
}
