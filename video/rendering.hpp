#pragma once

#include <utils.hpp>

/**
 * @brief Representing a point
 *
 */
class Point
{
  public:
    /**
     * @brief X position
     *
     */
    uint16_t x;

    /**
     * @brief Y position
     *
     */
    uint16_t y;
};

/**
 * @brief Representing a rectangle
 *
 */
class Rect
{
  public:
    /**
     * @brief Start point
     *
     */
    Point start;

    /**
     * @brief End point
     *
     */
    Point end;
};

/**
 * @brief Template representing the video buffer
 *
 * @tparam WIDTH
 * @tparam HEIGHT
 * @tparam COLOR_TYPE
 */
template <typename COLOR_TYPE, size_t WIDTH, size_t HEIGHT>
class Framebuffer : public Array2D<COLOR_TYPE, WIDTH, HEIGHT>
{
  public:
    void draw_rect(COLOR_TYPE color, const Rect &rect);

    void draw_character(COLOR_TYPE color, Array2D<uint8_t, 256, 8> &font, const Point &p, char c);
};
