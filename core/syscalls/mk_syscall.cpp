#include <array.hpp>
#include <core/ksnucleus.hpp>
#include <types.hpp>

// trying to convert non-type safe to type safe here... watch out
SYSCALL mk_syscall(KsSyscallID syscall_id, void **args)
{
    /**
     * @brief Numbers of args in the syscall
     *
     */
    constexpr Array<uint8_t, 7> syscall_arg_count{2, 1, 1, 1, 4, 3, 1};

    /**
     * @brief If that requires a arg
     *
     */
    constexpr Array<bool, syscall_arg_count.size()> syscall_requires_admin{};

    /**
     * @brief A array to hold the intermediate of the syscalls
     *
     */
    Array<void *, syscall_arg_count.size()> arg_array{};

    /**
     * @brief Copy the args
     *
     */
    arg_array = args;

    // Ensure than the syscall id is within range
    if (static_cast<uint32_t>(syscall_id) > syscall_arg_count.size())
    {
        ks_fission("Invalid syscall called");
    }

    auto answer = arg_array.search([](auto search_term) { return search_term == nullptr; });

    if (answer.valid && answer.data < syscall_arg_count[static_cast<size_t>(syscall_id)])
    {
        ks_fission("Nullptr detected in syscall args where actual data should have been");
    }

    switch (syscall_id)
    {
        case KsSyscallID::RANDOM:
        {
            ks_random(arg_array[0], *reinterpret_cast<size_t *>(arg_array[1]));
            break;
        }

        case KsSyscallID::GETTIME:
        {
            ks_gettime(*reinterpret_cast<uint64_t **>(arg_array[0]));
            break;
        }

        case KsSyscallID::FISSION:
        {
            ks_fission(reinterpret_cast<char *>(arg_array[0]));
            break;
        }

        case KsSyscallID::SETSYSTEMSTATE:
        {
            ks_setsystemstate(*reinterpret_cast<SystemState *>(arg_array[0]));
            break;
        }

        case KsSyscallID::COMMITFRAMEBUFFER:
        {
            ks_commitframebuffer(arg_array[0], *reinterpret_cast<uint16_t *>(arg_array[1]),
                                 *reinterpret_cast<uint16_t *>(arg_array[2]),
                                 *reinterpret_cast<uint8_t *>(arg_array[3]));
            break;
        }

        case KsSyscallID::ALLOCATEMEMORY:
        {
            ks_allocatememory(reinterpret_cast<void **>(arg_array[0]), *reinterpret_cast<Permissions *>(arg_array[1]),
                              *reinterpret_cast<uint32_t *>(arg_array[2]));
            break;
        }

        case KsSyscallID::DEALLOCATEMEMORY:
        {
            ks_deallocatememory(reinterpret_cast<void **>(arg_array[0]));
            break;
        }
    }
}
