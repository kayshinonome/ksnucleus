#include <arch/x86/cpuid.hpp>
#include <arch/x86/gdt.hpp>
#include <arch/x86/x86_32/fpu.hpp>
#include <core/init.hpp>
#include <core/ksnucleus.hpp>
#include <string.hpp>

bool ksinit::arch()
{

    if (!cpuid_check_support())
    {
        ks_fission("CPUID support is not available");
    }

    if (!GDT::init())
    {
        ks_fission("GDT init failed");
    }

    if (!FPU::init())
    {
        ks_fission("FPU init failed");
    }

    return true;
}
