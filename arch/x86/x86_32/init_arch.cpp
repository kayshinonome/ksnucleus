#include <arch/x86/gdt.hpp>
#include <core/init.hpp>

bool ksinit::arch()
{
    GDT::init();
    return true;
}
