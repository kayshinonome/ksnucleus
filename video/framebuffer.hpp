#include <array2d.hpp>
#include <types.hpp>
#include <video/point.hpp>
#include <video/rect.hpp>

// FIXME: Framebuffers sizes are calculated at runtime!  Templates are calculated at compile time!

/**
 * @brief Framebuffer type to be used internally
 *
 * @tparam COLOR_TYPE
 * @tparam WIDTH
 * @tparam HEIGHT
 */
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

    // FIXME: Actually implement this, and then specialize it to optimized functions
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
