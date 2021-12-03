/**
 * @file registry.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief A data structure containing hints on what the key values are
 *
 */
#pragma once
#include <types.hpp>

class Registry
{
  public:
    uint16_t screen_width;
    uint16_t screen_height;
    uint16_t screen_depth;
};

inline Registry global_registry{};
