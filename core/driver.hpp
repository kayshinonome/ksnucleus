#pragma once

#include <quark.hpp>

class Driver : public GenericQuark
{
  public:
    /**
     * @brief These are the quark services
     * Every service returns false if it wasn't able to complete its job and another has to be found
     */
    bool (*commitframebuffer)(void *data) = nullptr;
    bool (*reboot)() = nullptr;
    bool (*shutdown)() = nullptr;
    bool (*randseed)() = nullptr;
    bool (*getmemorymap)() = nullptr;
};

enum class Driver_Services : uint8_t
{
    COMMITFRAMEBUFFER,
    REBOOT,
    SHUTDOWN
};

class Driver_Collection : public Quark_Collection<Driver, Driver_Services, 0x10>
{
  public:
    bool call_quark_service(Driver_Services driver_service, Array<void *, MAX_QUARK_ARG_COUNT> args) override;
};

constinit inline Driver_Collection driver_collection{};