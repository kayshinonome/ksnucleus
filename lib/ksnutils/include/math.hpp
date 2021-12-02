/**
 * @file math.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief Provides many basic math operations (crudely)
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <core/ksnucleus.hpp>
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

template <typename T> constexpr T cos(T x)
{
	ks_fission("No implementation of cos");
	return 0;
}

template <typename T> constexpr T sqrt(T x)
{
	ks_fission("No implementation of sqrt");
	return 0;
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
