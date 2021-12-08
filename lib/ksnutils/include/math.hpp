/**
 * @file math.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief Provides many basic math operations (crudely)
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <array.hpp>
#include <core/ksnucleus.hpp>
#include <types.hpp>

constexpr auto M_PI = 3.14159265358979323846;

template <typename T> T constexpr abs(T x)
{
    return (x < 0) ? (-x) : (x);
}

template <typename T> constexpr T sin(T x)
{
    constexpr auto B = 4 / M_PI;
    constexpr auto C = -4 / (M_PI * M_PI);
    constexpr auto P = 0.225;

    auto y = B * x + C * x * abs(x);

    y = P * (y * abs(y) - y) + y;

    return y;
}

template <typename T> constexpr T cos(T x)
{
    ks_fission("No generic implementation of cos");
    return 0;
}

template <typename T> constexpr T sqrt(T x)
{
    ks_fission("No generic implementation of sqrt");
    return 0;
}

template <typename T1, typename T2> constexpr auto max(T1 x, T2 y)
{
    return (x > y) ? x : y;
}

template <typename T1, typename T2> constexpr auto min(T1 x, T2 y)
{
    return (x < y) ? x : y;
}

template <typename T> constexpr uint32_t crc32(T obj)
{

    // Calculated at compile time (Most of the time, usually even g optimizations is enough to do this)
    constexpr auto crc32_table = ([]() {
        uint32_t rem = 0;
        uint8_t octet = 0;
        Array<uint32_t, 256> table{};

        // Calculate CRC table.
        for (auto i = 0; i < 256; i++)
        {
            // remainder from polynomial division
            rem = i;
            for (auto j = 0; j < 8; j++)
            {
                if ((rem & 1) == 1)
                {
                    rem >>= 1;
                    rem ^= 0xedb88320;
                }
                else
                {
                    rem >>= 1;
                }
            }
            table[i] = rem;
        }

        return table;
    })();

    uint32_t rem = 0;
    uint8_t octet = 0;
    const uint8_t *q = nullptr;
    constexpr auto total_length = sizeof(T);
    uint32_t crc = 0xffffffff;

    // Idk why I'm allowed to reinterpret_cast here, maybe rules are relaxed for templates? Or maybe this is a clang
    // glitch. Either way, I'm not complaining

    q = reinterpret_cast<const uint8_t *>(&obj) + total_length;
    for (const auto *p = reinterpret_cast<const uint8_t *>(&obj); p < q; p++)
    {
        // Cast to unsigned octet.
        octet = *p;
        crc = (crc >> 8) ^ crc32_table[(crc & 0xff) ^ octet];
    }
    return ~crc;
}
