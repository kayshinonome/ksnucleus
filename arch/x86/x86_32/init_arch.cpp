#include <arch/x86/cpuid.hpp>
#include <arch/x86/gdt.hpp>
#include <array.hpp>
#include <core/init.hpp>
#include <types.hpp>

bool ksinit::arch()
{
    GDT::init();
    return true;
}
