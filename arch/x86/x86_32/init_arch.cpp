#include <arch/x86/cpuid.hpp>
#include <arch/x86/gdt.hpp>
#include <arch/x86/x86_32/fpu.hpp>
#include <arch/x86/x86_32/interrupts.hpp>
#include <core/init.hpp>
#include <core/ksnucleus.hpp>
#include <string.hpp>

void ksinit::arch()
{
    if (!GDT::init())
    {
        ks_fission("GDT init failed");
    }

    if (!IDT::init())
    {
        ks_fission("IDT init failed");
    }

    if (!FPU::init())
    {
        ks_fission("FPU init failed");
    }

    if (!cpuid::check_support())
    {
        ks_fission("CPUID support is not available, which is a requirement");
    }

    if (cpuid::get_vendor() != cpuid::CPU_Vendor::INTEL)
    {
        ks_fission("Only INTEL CPUs are supported for now");
    }
}
