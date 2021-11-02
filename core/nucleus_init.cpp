#include <core/init.hpp>

__attribute__((used, constructor)) void nucleus_init()
{
    if (!ksinit::arch())
    {
    }

    if (!ksinit::platform())
    {
    }
}