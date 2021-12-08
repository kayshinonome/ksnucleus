#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <debug.hpp>
#include <types.hpp>

[[noreturn]] SUBSYSCALL ks_fission(const char *error_code)
{
    constinit static Atomic<uint16_t> fisson_level{};
    constinit static Atomic<bool> fission_called_before{};

    // Tell the debug console the worst has happened
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

    // Sit here and hang in case anything has gone wrong...
    while (true)
    {
    }
}
