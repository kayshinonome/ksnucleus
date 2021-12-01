#include <arch/x86/cpuid.hpp>
#include <arch/x86/gdt.hpp>
#include <arch/x86/x86_32/fpu.hpp>
#include <arch/x86/x86_32/interrupts.hpp>
#include <core/init.hpp>
#include <core/ksnucleus.hpp>
#include <string.hpp>

bool ksinit::arch()
{
    if (!cpuid_check_support())
    {
        ks_fission("CPUID support is not available");
    }

    if (cpuid_get_vendor() != CPU_Vendor::INTEL)
    {
        ks_fission("Only INTEL CPUs are supported for now");
    }

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

    static auto handler = [](uint16_t id, Interrupt_Data data) {
        static Array<String, 32> error_messages = {"Division By Zero",
                                                   "Debug",
                                                   "Non Maskable Interrupt",
                                                   "Breakpoint",
                                                   "Into Detected Overflow",
                                                   "Out of Bounds",
                                                   "Invalid Opcode",
                                                   "No Coprocessor",
                                                   "Double Fault",
                                                   "Coprocessor Segment Overrun",
                                                   "Bad TSS",
                                                   "Segment Not Present",
                                                   "Stack Fault",
                                                   "General Protection Fault",
                                                   "Page Fault",
                                                   "Unknown Interrupt",
                                                   "Coprocessor Fault",
                                                   "Alignment Check",
                                                   "Machine Check",
                                                   "SIMD Floating-Point Exception",
                                                   "Virtualization Exception",
                                                   "Reserved",
                                                   "Reserved",
                                                   "Reserved",
                                                   "Reserved",
                                                   "Reserved",
                                                   "Reserved",
                                                   "Reserved",
                                                   "Reserved",
                                                   "Reserved",
                                                   "Security Exception",
                                                   "Reserved"};

        ks_fission(error_messages[id].raw());
    };

    for (auto x = 0; x < 32; x++)
    {
        x86_interrupt_event_engine.add_event_handler(x, handler);
    }

    return true;
}
