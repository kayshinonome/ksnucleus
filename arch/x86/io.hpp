/**
 * @file io.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief Functions to interact with the IO ports
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <utils.hpp>

/**
 * @brief Get a uint8_t from the io ports
 *
 * @param port
 * @return uint8_t
 */
uint8_t inline in8(uint16_t port)
{
    uint8_t ret = 0;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/**
 * @brief Send a uint8_t through the io ports
 *
 * @param port
 * @param value
 */
void inline out8(uint16_t port, uint8_t value)
{
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

/**
 * @brief Get a uint16_t from the io ports
 *
 * @param port
 * @return uint16_t
 */
uint16_t inline in16(uint16_t port)
{
    uint16_t ret = 0;
    asm volatile("inw %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

/**
 * @brief Send a uint16_t through the io ports
 *
 * @param port
 * @param value
 */
void inline out16(uint16_t port, uint16_t value)
{
    asm volatile("outw %1, %0" : : "dN"(port), "a"(value));
}

/**
 * @brief Get a uint32_t from the io ports
 *
 * @param port
 * @return uint32_t
 */
uint32_t inline in32(uint16_t port)
{
    uint32_t ret = 0;
    asm volatile("inl %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

/**
 * @brief Send a uint32_t through the io ports
 *
 * @param port
 * @param value
 */
void inline out32(uint16_t port, uint32_t value)
{
    asm volatile("outl %1, %0" : : "dN"(port), "a"(value));
}
