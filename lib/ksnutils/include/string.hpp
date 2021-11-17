#include <array.hpp>
#include <types.hpp>

template <size_t STRING_SIZE> class String : public Array<char, STRING_SIZE>
{
};