#include <array.hpp>
#include <core/ksnucleus.hpp>
#include <types.hpp>

// trying to convert non-type safe to type safe here... watch out
SYSCALL mk_syscall(KsSyscallID syscall_id, void **args)
{
    constexpr Array<uint8_t, 6> syscall_arg_count{2, 1, 1, 1, 4, 2};

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

    // Verify that the array contains no nullptrs where valid pointers should be
    for (uint8_t x = 0, len = syscall_arg_count[static_cast<size_t>(syscall_id)]; x < len; x++)
    {
        if (arg_array[x] == nullptr)
        {
            ks_fission("Nullptr detected in syscall where actual data should have been");
        }
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
            ks_allocatememory(reinterpret_cast<void **>(arg_array[0]), *reinterpret_cast<uint32_t *>(arg_array[1]));
            break;
        }
    }
}
