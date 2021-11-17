/**
 * @file ksnucleus.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief File containing the syscalls
 * @version 0.1
 * @date 2021-10-28
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <types.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define SYSCALL extern "C" __attribute__((used, hot, noinline)) void

enum class KsSyscallID : uint8_t
{
    RANDOM = 0,
    GETTIME = 1,
    FISSION = 2
};

/**
 * @brief
 *
 * @param args Arguments for the function
 * The arguments are containing in a array of void pointers, each one pointing to the desired data
 * The nucleus will interpret these pointers as their correct data based upon the syscall you called
 * @param syscall_id
 * @return void
 */
SYSCALL mk_syscall(void **args, KsSyscallID syscall_id);

/**
 * @brief Fill a buffer with random bytes
 *
 * @param buffer
 * @param length
 * @return SYSCALL
 */
SYSCALL ks_random(void *buffer, size_t length);
SYSCALL ks_gettime(uint64_t *time);
SYSCALL ks_fission(void *, void *stack_position);