#pragma once
#include <utils.hpp>

extern "C"
{
    void enter_v86(uint32_t ss, uint32_t esp, uint32_t cs, uint32_t eip);
}