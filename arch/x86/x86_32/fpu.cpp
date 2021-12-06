#include <arch/x86/x86_32/fpu.hpp>

void FPU::load_control_word(uint16_t control)
{
    asm volatile("fldcw %0" ::"m"(control));
}

bool FPU::init()
{
    return true;
}
