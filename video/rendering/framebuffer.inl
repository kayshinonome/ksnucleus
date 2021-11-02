#pragma once

#include <utils.hpp>
#include <video/rendering.hpp>

template <typename COLOR_TYPE, size_t WIDTH, size_t HEIGHT>
void Framebuffer<COLOR_TYPE, WIDTH, HEIGHT>::draw_rect(COLOR_TYPE color, const Rect &rect)
{
    /**
     * @brief Most inefficient way to draw a rectangle, check.
     *
     */
    for (auto x = rect.start.x; x < rect.end.x; x++)
    {
        for (auto y = rect.start.y; y < rect.end.y; y++)
        {
            (*this)[x][y] = color;
        }
    }
}

template <typename COLOR_TYPE, size_t WIDTH, size_t HEIGHT>
void Framebuffer<COLOR_TYPE, WIDTH, HEIGHT>::draw_character(COLOR_TYPE color, Array2D<uint8_t, 256, 8> &font,
                                                            const Point &p, char c)

{
    for (size_t x = p.x, lenx = font.width(); x < lenx; x++)
    {
        for (size_t y = p.y, leny = font.height(); y < leny; y++)
        {
        }
    }
}
