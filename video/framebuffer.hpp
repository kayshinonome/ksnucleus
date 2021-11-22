#include <array2d.hpp>
#include <types.hpp>
#include <video/point.hpp>
#include <video/rect.hpp>

template <typename COLOR_TYPE, size_t WIDTH, size_t HEIGHT>
class Framebuffer : public Array2D<COLOR_TYPE, WIDTH, HEIGHT>
{
  public:
    void draw_rect(COLOR_TYPE color, const Rect &rect)
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

    void draw_character(COLOR_TYPE color, Array2D<uint8_t, 256, 8> &font, const Point &p, char c)
    {
        for (size_t x = p.x, lenx = font.width(); x < lenx; x++)
        {
            for (size_t y = p.y, leny = font.height(); y < leny; y++)
            {
                const auto character = font[c];
            }
        }
    }
};
