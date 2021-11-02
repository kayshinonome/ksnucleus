#pragma once

#include <utils.hpp>

template <typename ARRAY_TYPE, size_t WIDTH, size_t HEIGHT>
Array<ARRAY_TYPE, WIDTH * HEIGHT> &Array2D<ARRAY_TYPE, WIDTH, HEIGHT>::as_flat_array()
{
    return reinterpret_cast<Array<ARRAY_TYPE, WIDTH * HEIGHT> &>(*this);
}

template <typename ARRAY_TYPE, size_t WIDTH, size_t HEIGHT>
const Array<ARRAY_TYPE, WIDTH * HEIGHT> &Array2D<ARRAY_TYPE, WIDTH, HEIGHT>::as_flat_array() const
{
    return reinterpret_cast<const Array<ARRAY_TYPE, WIDTH * HEIGHT> &>(*this);
}

template <typename ARRAY_TYPE, size_t WIDTH, size_t HEIGHT>
[[nodiscard]] constexpr size_t Array2D<ARRAY_TYPE, WIDTH, HEIGHT>::width() const
{
    return WIDTH;
}

template <typename ARRAY_TYPE, size_t WIDTH, size_t HEIGHT>
[[nodiscard]] constexpr size_t Array2D<ARRAY_TYPE, WIDTH, HEIGHT>::height() const
{
    return HEIGHT;
}