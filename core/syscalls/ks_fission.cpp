#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <types.hpp>
#include <debug.hpp>

[[noreturn]] SUBSYSCALL ks_fission(const char* error_code)
{

    static Atomic<uint16_t> fisson_level;
    static Atomic<bool> fission_called_before;

    debug("Nucleus has undergone fission! ", error_code);

    // If no fissions happened before, init everything
    if (!fission_called_before)
    {
        fisson_level = 0;
        fission_called_before = true;
    }

    // Tracking how many fissions have happened since call
    fisson_level++;

    // Only the first fission may kill the system
    if (fisson_level == 1)
    {
        ks_setsystemstate(SystemState::REBOOT);
    }

    while (true)
    {
    }
}
