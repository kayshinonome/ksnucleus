#pragma once

#include <array.hpp>
#include <types.hpp>

template <typename ARRAY_TYPE, uint32_t WIDTH, uint32_t HEIGHT>
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
     * @return constexpr uint32_t
     */
    [[nodiscard]] constexpr static uint32_t width()
    {
        return WIDTH;
    }

    /**
     * @brief Get the height of the array, calculated at compile time
     *
     * @return constexpr uint32_t
     */
    [[nodiscard]] constexpr static uint32_t height()
    {
        return HEIGHT;
    }

    /**
     * @brief Get the size of the entire thing, as if you called as_flat_array().size()
     *
     * @return constexpr uint32_t
     */
    [[nodiscard]] constexpr static uint32_t size()
    {
        return WIDTH * HEIGHT;
    }
};
