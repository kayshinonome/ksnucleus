#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <core/quark.hpp>
#include <types.hpp>

SUBSYSCALL ks_setsystemstate(SystemState system_state)
{
    switch (system_state)
    {
        case SystemState::REBOOT:
        {
            quark_collection.call_quark_service(Quark_Services::REBOOT, {});
            break;
        }

        case SystemState::SHUTDOWN:
        {
            quark_collection.call_quark_service(Quark_Services::SHUTDOWN, {});
            break;
        }
    }
}