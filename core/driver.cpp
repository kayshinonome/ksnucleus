#include <core/driver.hpp>

bool Driver_Collection::call_quark_service(Driver_Services driver_service, Array<void *, MAX_QUARK_ARG_COUNT> args)
{
    constexpr Array<uint16_t, 4> arg_array_count{1, 0, 0, 0};

    if (!is_arg_array_good(args, arg_array_count[static_cast<uint16_t>(driver_service)]))
    {
        return false;
    }

    for (uint32_t x = 0, len = size(); x < len; x++)
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