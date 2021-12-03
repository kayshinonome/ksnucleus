#include <core/init.hpp>

__attribute__((used, constructor)) void nucleus_init()
{
    ksinit::arch();
    ksinit::boot();
    ksinit::boot();
}
