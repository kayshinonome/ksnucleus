#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <types.hpp>

SUBSYSCALL ks_setsystemstate(SystemState system_state)
{
    switch (system_state)
    {
        case SystemState::REBOOT:
        {
        }

        case SystemState::SHUTDOWN:
        {
        }
    }
}