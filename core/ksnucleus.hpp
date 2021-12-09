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

#include <core/runtime.hpp>
#include <string.hpp>
#include <types.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define SYSCALL extern "C" __attribute__((hot)) void

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define SUBSYSCALL extern "C" __attribute__((hot)) void

enum class KsSyscallID : uint8_t
{
    RANDOM = 0,
    GETTIME = 1,
    FISSION = 2,
    SETSYSTEMSTATE = 3,
    COMMITFRAMEBUFFER = 4,
    ALLOCATEMEMORY = 5
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
SYSCALL mk_syscall(KsSyscallID syscall_id, void **args);

/**
 * @brief Fill a buffer with random bytes
 *
 * @param buffer
 * @param length
 * @return void
 */
SUBSYSCALL ks_random(void *buffer, size_t length);

/**
 * @brief Get the current time in seconds
 *
 * @param time Pointer to a 64 bit unsigned integer to put the time
 * @return void
 */
SUBSYSCALL ks_gettime(uint64_t *time);

/**
 * @brief Prints a error message, and kills the system
 *
 * @param error_string The error string, 127 bytes, not including the null terminator
 * @return void
 */
[[noreturn]] SUBSYSCALL ks_fission(const char error_string[128]);
SUBSYSCALL ks_setsystemstate(SystemState system_state);
SUBSYSCALL ks_commitframebuffer(const void *buffer, uint16_t width, uint16_t height, uint8_t depth);
SUBSYSCALL ks_allocatememory(void **buffer, uint32_t size);
