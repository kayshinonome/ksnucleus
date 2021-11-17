#include <array.hpp>
#include <core/ksnucleus.hpp>
#include <types.hpp>

// trying to convert non-type safe to type safe here... watch out
SYSCALL mk_syscall(void **args, KsSyscallID syscall_id)
{
    /**
     * @brief Contains the number of args each syscall has
     *
     */
    Array<size_t, 3> syscall_arg_count = {2u, 1u, 2u};

    /**
     * @brief A array to hold the intermediate of the syscalls
     *
     */
    Array<void *, 3> arg_array = {};

    // Ensure than the syscall id is within range
    if (static_cast<size_t>(syscall_id) > syscall_arg_count.length())
    {
        // A error occurs here
    }

    // Copy the args over
    arg_array = args;

    // Verify that the array contains no nullptrs where valid pointers should be
    for (uint8_t x = 0, len = syscall_arg_count[static_cast<size_t>(syscall_id)]; x < len; x++)
    {
        if (arg_array[x] == nullptr)
        {
            // handler error of sorts
        }
    }

    switch (syscall_id)
    {
        case KsSyscallID::RANDOM:
        {
            ks_random(arg_array[0], *reinterpret_cast<size_t *>(arg_array[1]));
        }

        case KsSyscallID::GETTIME:
        {
            // ks_gettime(*reinterpret_cast<uint64_t **>(arg_array[0]));
        }

        case KsSyscallID::FISSION:
        {
        }
    }
}