#pragma once

#include <types.hpp>

class FPU
{
  private:
    static void load_control_word(uint16_t control);

  public:
    static bool init();
};