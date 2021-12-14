/**
 * @file registry.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief A data structure containing hints on what the key values are
 *
 */
#pragma once
#include <memory/memory_table.hpp>
#include <types.hpp>

/**
 * @brief Global registry with hints on system info
 * When a piece of the os gleans any system information, it is stored here in case something has to guess something
 * about the computer.
 *
 * It's intended for things such as the bootloader to feed us these things
 *
 */
constinit inline class
{
  public:
    uint16_t screen_width;
    uint16_t screen_height;
    uint16_t screen_depth;
    Memory_Table<0xff> memory_table;
} global_registry{};
