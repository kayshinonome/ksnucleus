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
  private:
    uint8_t unused : 2;

  public:
    uint8_t system_read : 1;
    uint8_t system_write : 1;
    uint8_t system_execute : 1;
    uint8_t user_read : 1;
    uint8_t user_write : 1;
    uint8_t user_execute : 1;
};