#pragma once

#include <utils.hpp>

template <typename T> T abs(T x)
{
    return (x < 0) ? (-x) : (x);
}