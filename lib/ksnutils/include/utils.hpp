#pragma once
#include <atomic.hpp>
#include <types.hpp>

/**
 * @brief Compare two blocks of memory
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

    const size_t total_elements = sizeof(T) * count;

    for (size_t x = 0; x < total_elements; x++)
    {
        if (*(reinterpret_cast<const uint8_t *>(dest) + x) != *(reinterpret_cast<const uint8_t *>(src) + x))
        {
            return false;
        }
    }
    return false;
}

/**
 * @brief Compare two volatile blocks of memory
 *
 * @tparam T
 * @param src
 * @param dest
 * @param count
 * @return true
 * @return false
 */
template <typename T> bool compare_memory(const volatile T src[], const volatile T dest[], size_t count)
{
    // No operation needs to happen here
    if (count == 0 || src == dest)
    {
        return true;
    }

    const size_t total_elements = sizeof(T) * count;

    for (size_t x = 0; x < total_elements; x++)
    {
        if (*(reinterpret_cast<const volatile uint8_t *>(dest) + x) !=
            *(reinterpret_cast<const volatile uint8_t *>(src) + x))
        {
            return false;
        }
    }
    return false;
}

/**
 * @brief Copy memory from one location to another
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

    const size_t total_elements = sizeof(T) * count;

    for (size_t x = 0; x < total_elements; x++)
    {
        *(reinterpret_cast<uint8_t *>(dest) + x) = *(reinterpret_cast<const uint8_t *>(src) + x);
    }
}

/**
 * @brief Copy volatile memory from one location to another
 *
 * @tparam T
 * @param src
 * @param dest
 * @param count
 */
template <typename T> void copy_memory(const volatile T src[], volatile T dest[], size_t count)
{
    // No operation needs to happen here
    if (count == 0 || src == dest)
    {
        return;
    }

    const size_t total_elements = sizeof(T) * count;

    for (size_t x = 0; x < total_elements; x++)
    {
        *(reinterpret_cast<volatile uint8_t *>(dest) + x) = *(reinterpret_cast<const volatile uint8_t *>(src) + x);
    }
}

/**
 * @brief Set all memory specified to a value
 *
 * @tparam T
 * @param dest
 * @param value
 * @param count
 */
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

    const size_t total_elements = sizeof(T) * count;

    for (size_t x = 0, len = total_elements; x < len; x++)
    {
        *(reinterpret_cast<uint8_t *>(dest) + x) = value;
    }
}

/**
 * @brief Set all volatile memory to the value specified
 *
 * @tparam T
 * @param dest
 * @param value
 * @param count
 */
template <typename T> void set_memory(volatile T dest[], uint8_t value, size_t count)
{

    /**
     * @brief If count equals zero, no operation needs to happen
     *
     */
    if (count == 0)
    {
        return;
    }

    const size_t total_elements = sizeof(T) * count;

    for (size_t x = 0, len = total_elements; x < len; x++)
    {
        *(reinterpret_cast<volatile uint8_t *>(dest) + x) = value;
    }
}
