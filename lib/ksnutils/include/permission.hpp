/**
 * @file permission.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief
 *
 * KSNucleus permissions work in this manner
 *
 * System | User
 *    rwx | rwx
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include <types.hpp>

class Permissions
{
  public:
    bool unused : 2;
    bool system_read : 1;
    bool system_write : 1;
    bool system_execute : 1;
    bool user_read : 1;
    bool user_write : 1;
    bool user_execute : 1;
};

static_assert(sizeof(Permissions) == sizeof(uint8_t));