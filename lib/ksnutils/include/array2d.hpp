#pragma once

#include <array.hpp>
#include <types.hpp>

template <typename ARRAY_TYPE, size_t WIDTH, size_t HEIGHT>
class Array2D : public Array<Array<ARRAY_TYPE, HEIGHT>, WIDTH>
{
  public:
    /**
     * @brief Return this as a flat array
     *
     * @return Array<ARRAY_TYPE, WIDTH * HEIGHT>&
     */
    Array<ARRAY_TYPE, WIDTH * HEIGHT> &as_flat_array()
    {
        return reinterpret_cast<Array<ARRAY_TYPE, WIDTH * HEIGHT> &>(*this);
    }

    /**
     * @brief Return this as a flat const array
     *
     * @return const Array<ARRAY_TYPE, WIDTH * HEIGHT>&
     */
    const Array<ARRAY_TYPE, WIDTH * HEIGHT> &as_flat_array() const
    {
        return reinterpret_cast<const Array<ARRAY_TYPE, WIDTH * HEIGHT> &>(*this);
    }

    /**
     * @brief Get the width of the array, calculated at compile time
     *
     * @return constexpr int
     */
    [[nodiscard]] constexpr size_t width() const
    {
        return WIDTH;
    }

    /**
     * @brief Get the height of the array, calculated at compile time
     *
     * @return constexpr int
     */
    [[nodiscard]] constexpr size_t height() const
    {
        return HEIGHT;
    }
};
