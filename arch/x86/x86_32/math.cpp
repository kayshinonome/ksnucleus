#include <math.hpp>

// We can use hardware float for this here.
template <> double sin<double>(double x)
{
    double result = 0.0;
    asm("fsin" : "=t"(result) : "0"(x));
    return result;
}

template <> double cos<double>(double x)
{
    double result = 0.0;
    asm("fcos" : "=t"(result) : "0"(x));
    return result;
}

template <> double sqrt<double>(double x)
{
    double result = 0.0;
    asm("fsqrt" : "=t"(result) : "0"(x));
    return result;
}
