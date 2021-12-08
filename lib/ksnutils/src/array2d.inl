#pragma once
#include <array2d.hpp>
#include <types.hpp>

template <typename ARRAY_TYPE, uint32_t WIDTH, uint32_t HEIGHT>
Array<ARRAY_TYPE, WIDTH * HEIGHT> &Array2D<ARRAY_TYPE, WIDTH, HEIGHT>::as_flat_array()
{
    return reinterpret_cast<Array<ARRAY_TYPE, WIDTH * HEIGHT> &>(*this);
}

template <typename ARRAY_TYPE, uint32_t WIDTH, uint32_t HEIGHT>
const Array<ARRAY_TYPE, WIDTH * HEIGHT> &Array2D<ARRAY_TYPE, WIDTH, HEIGHT>::as_flat_array() const
{
    return reinterpret_cast<Array<ARRAY_TYPE, WIDTH * HEIGHT> &>(*this);
}

template <typename ARRAY_TYPE, uint32_t WIDTH, uint32_t HEIGHT>
[[nodiscard]] constexpr uint32_t Array2D<ARRAY_TYPE, WIDTH, HEIGHT>::width()
{
    return WIDTH;
}

template <typename ARRAY_TYPE, uint32_t WIDTH, uint32_t HEIGHT>
[[nodiscard]] constexpr uint32_t Array2D<ARRAY_TYPE, WIDTH, HEIGHT>::height()
{
    return HEIGHT;
}

template <typename ARRAY_TYPE, uint32_t WIDTH, uint32_t HEIGHT>
[[nodiscard]] constexpr uint32_t Array2D<ARRAY_TYPE, WIDTH, HEIGHT>::size()
{
    return WIDTH * HEIGHT;
}