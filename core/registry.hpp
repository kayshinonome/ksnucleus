/**
 * @file registry.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief A data structure containing hints on what the key values are
 *
 */
#pragma once
#include <types.hpp>

/**
 * @brief Global registry with hints on system info
 *
 */
inline class
{
  public:
    uint16_t screen_width;
    uint16_t screen_height;
    uint16_t screen_depth;
} global_registry{};
