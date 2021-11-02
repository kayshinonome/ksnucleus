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

#include <utils.hpp>

#define SYSCALL extern "C" __attribute__((used, hot, noinline)) void

enum class KsSyscallID : uint8_t
{
    RANDOM = 0,
    GETTIME = 1,
    WRITE = 2
};

/**
 * @brief
 *
 * @param args Arguments for the function
 * The arguments are containing in a array of void pointers, each one pointing to the desired data
 * @param syscall_id
 * @return void
 */
SYSCALL mk_syscall(void **args, KsSyscallID syscall_id);

// Subsyscalls
SYSCALL ks_random(void *buffer, size_t length);
SYSCALL ks_gettime(uint64_t *time);
SYSCALL ks_write(void *buffer, size_t length, uint8_t fileid);