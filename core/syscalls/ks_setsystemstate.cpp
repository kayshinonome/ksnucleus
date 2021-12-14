#include <array.hpp>
#include <atomic.hpp>
#include <core/driver.hpp>
#include <core/ksnucleus.hpp>
#include <types.hpp>

SUBSYSCALL ks_setsystemstate(SystemState system_state)
{
    switch (system_state)
    {
        case SystemState::REBOOT:
        {
            driver_collection.call_quark_service(Driver_Services::REBOOT, {});
            break;
        }

        case SystemState::SHUTDOWN:
        {
            driver_collection.call_quark_service(Driver_Services::SHUTDOWN, {});
            break;
        }
    }

    while (true)
    {
    }
}