#include <core/init.hpp>

extern "C"
{
    void nucleus_init()
    {
        ksinit::arch();
        ksinit::boot();
        ksinit::platform();
    }
}