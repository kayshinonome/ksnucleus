#pragma once

#include <arch/x86/cpuid.hpp>
#include <types.hpp>

class FPU
{
  private:
    static void fpu_load_control_word(uint16_t control);

  public:
    static bool init();
};