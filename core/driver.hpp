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
    bool call_quark_service(Driver_Services driver_service, Array<void *, MAX_QUARK_ARG_COUNT> args) override
    {
        constexpr Array<uint16_t, 4> arg_array_count{1, 0, 0, 0};

        if (!is_arg_array_good(args, arg_array_count[static_cast<uint16_t>(driver_service)]))
        {
            return false;
        }

        for (uint32_t x = 0; x < size(); x++)
        {
            auto *driver = (*this)[x];
            if (driver != nullptr)
            {

                init_quark_if_needed(driver);

                switch (driver_service)
                {
                    case Driver_Services::COMMITFRAMEBUFFER:
                    {
                        if (driver->commitframebuffer != nullptr && driver->commitframebuffer(args[0]))
                        {
                            return true;
                        }
                        break;
                    }

                    case Driver_Services::REBOOT:
                    {
                        if (driver->reboot != nullptr && driver->reboot())
                        {
                            return true;
                        }
                        break;
                    }

                    case Driver_Services::SHUTDOWN:
                    {
                        if (driver->shutdown != nullptr && driver->shutdown())
                        {
                            return true;
                        }
                        break;
                    }
                }
            }
        }
        return false;
    }
};

constinit inline Driver_Collection driver_collection{};