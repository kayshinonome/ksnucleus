#include <core/quark.hpp>

bool Quark_Collection::add_quark(Quark &quark)
{
    for (size_t x = 0, len = length(); x < len; x++)
    {
        if ((*this)[x] == nullptr)
        {
            (*this)[x] = &quark;
            return true;
        }
    }
    return false;
}

// Fixme: This is super super inefficient
bool Quark_Collection::call_quark_service(Quark_Services quark_service, Array<void *, MAX_QUARK_ARG_COUNT> args)
{
    const auto quark_arg_count_for_call = quark_arg_counts[static_cast<uint8_t>(quark_service)];

    // Ensure that the args isn't null in its spot where it shouldn't
    for (uint8_t x = 0; x < quark_arg_count_for_call; x++)
    {
        if (args[x] == nullptr)
        {
            ks_fission("Nullptr detected in quark call where actual data should have been");
        }
    }

    // Search for a viable quark and call it
    for (uint32_t x = 0, len = length(); x < len; x++)
    {
        auto *current_quark = (*this)[x];

        if (current_quark != nullptr)
        {
            // Call the quarks init
            if (!current_quark->has_been_initialized)
            {
                current_quark->init();
            }

            if (current_quark->is_viable(quark_service))
            {
                switch (quark_service)
                {
                    case Quark_Services::COMMIT_FRAMEBUFFER:
                    {

                        current_quark->commit_framebuffer(args[0]);
                        return true;
                    }
                    case Quark_Services::REBOOT:
                    {

                        current_quark->reboot();
                        return true;
                    }
                    case Quark_Services::SHUTDOWN:
                    {

                        current_quark->shutdown();
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
