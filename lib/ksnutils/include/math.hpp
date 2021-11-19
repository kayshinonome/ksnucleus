/**
 * @file math.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief Provides many basic math operations (crudely)
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <types.hpp>

constexpr auto M_PI = 3.14159265358979323846;

/**
 * @brief Get the absolute value of a value
 *
 * @tparam T
 * @param x
 * @return T
 */
template <typename T> T constexpr abs(T x)
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
template <typename T> constexpr T sin(T x)
{
    constexpr auto B = 4 / M_PI;
    constexpr auto C = -4 / (M_PI * M_PI);
    constexpr auto P = 0.225;

    auto y = B * x + C * x * abs(x);

    y = P * (y * abs(y) - y) + y;

    return y;
}

/**
 * @brief Return the max value
 *
 * @tparam T
 * @param x
 * @param y
 * @return constexpr T
 */
template <typename T> constexpr T max(T x, T y)
{
    return (x > y) ? x : y;
}

/**
 * @brief Return the min value
 *
 * @tparam T
 * @param x
 * @param y
 * @return constexpr T
 */
template <typename T> constexpr T min(T x, T y)
{
    return (x < y) ? x : y;
}

/**
 * @brief A hideous way to calculate pow, but its constexpr so that is useful
 *
 * @tparam T
 * @param x
 * @param y
 * @return constexpr T
 */
template <typename T> constexpr T pow(T x, T y)
{
    for (auto a = 0U; a < y; a++)
    {
        x *= x;
    }
    return x;
}
