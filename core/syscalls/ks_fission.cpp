#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <types.hpp>

[[noreturn]] SUBSYSCALL ks_fission(const char error_code[128])
{
    ks_setsystemstate(SystemState::REBOOT);
    while (true)
    {
    }
}