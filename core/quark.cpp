#include <core/quark.hpp>
#include <debug.hpp>

bool Quark_Collection::add_quark(Quark &quark)
{
    for (size_t x = 0, len = size(); x < len; x++)
    {
        if ((*this)[x] == nullptr)
        {
            (*this)[x] = &quark;
            return true;
        }
    }
    return false;
}

// FIXME: This is super super inefficient
// FIXME: This is too complicated to actually comphrehend all at once. Simplify it.
bool Quark_Collection::call_quark_service(Quark_Services quark_service, Array<void *, MAX_QUARK_ARG_COUNT> args)
{
    auto answer = args.search([](auto search_term) { return search_term == nullptr; });

    if (answer.valid && answer.data < quark_arg_counts[static_cast<size_t>(quark_service)])
    {
        ks_fission("Nullptr detected in quark args where actual data should have been");
    }

    // Search for a viable quark and call it
    for (uint32_t x = 0, len = size(); x < len; x++)
    {
        auto *current_quark = (*this)[x];

        if (current_quark != nullptr)
        {
            // Call the quarks init
            if ((!current_quark->has_been_initialized) && current_quark->init != nullptr)
            {
                current_quark->init();
            }

            switch (quark_service)
            {
                case Quark_Services::COMMITFRAMEBUFFER:
                {
                    if (current_quark->commitframebuffer != nullptr && current_quark->commitframebuffer(args[0]))
                    {
                        return true;
                    }
                    break;
                }
                case Quark_Services::REBOOT:
                {
                    if (current_quark->reboot != nullptr && current_quark->reboot())
                    {
                        return true;
                    }
                    break;
                }
                case Quark_Services::SHUTDOWN:
                {
                    if (current_quark->shutdown != nullptr && current_quark->shutdown())
                    {
                        return true;
                    }
                    break;
                }
                case Quark_Services::RANDSEED:
                {
                    if (current_quark->randseed != nullptr && current_quark->randseed())
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
