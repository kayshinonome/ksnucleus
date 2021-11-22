/**
 * @file gdt.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief Header representing the GDT
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <array.hpp>
#include <types.hpp>

constexpr auto GDT_LENGTH = 5;

class GDT : public Array<uint64_t, GDT_LENGTH>
{
  private:
    /**
     * @brief Descriptor type (0 for system, 1 for code/data)
     *
     */
    constexpr static uint16_t SEG_TYPE(uint16_t x)
    {
        return ((x) << 0x04);
    }

    /**
     * @brief Present
     *
     */
    constexpr static uint16_t SEG_PRES(uint16_t x)
    {
        return ((x) << 0x07);
    }

    /**
     * @brief Available for system use
     *
     */
    constexpr static uint16_t SEG_SAVL(uint16_t x)
    {
        return ((x) << 0x0c);
    }

    /**
     * @brief Long mode
     *
     */
    constexpr static uint16_t SEG_LONG(uint16_t x)
    {
        return ((x) << 0x0d);
    }

    /**
     * @brief Size (0 for 16-bit, 1 for 32)
     *
     */
    constexpr static uint16_t SEG_SIZE(uint16_t x)
    {
        return ((x) << 0x0e);
    }

    /**
     * @brief Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
     *
     */
    constexpr static uint16_t SEG_GRAN(uint16_t x)
    {
        return ((x) << 0x0f);
    }

    /**
     * @brief Set privilege level (0 - 3)
     *
     */
    constexpr static uint16_t SEG_PRIV(uint16_t x)
    {
        return (((x)&0x03) << 0x05);
    }

    constexpr static uint8_t SEG_DATA_RD = 0x00;
    constexpr static uint8_t SEG_DATA_RDA = 0x01;       // Read-Only, accessed
    constexpr static uint8_t SEG_DATA_RDWR = 0x02;      // Read/Write
    constexpr static uint8_t SEG_DATA_RDWRA = 0x03;     // Read/Write, accessed
    constexpr static uint8_t SEG_DATA_RDEXPD = 0x04;    // Read-Only, expand-down
    constexpr static uint8_t SEG_DATA_RDEXPDA = 0x05;   // Read-Only, expand-down, accessed
    constexpr static uint8_t SEG_DATA_RDWREXPD = 0x06;  // Read/Write, expand-down
    constexpr static uint8_t SEG_DATA_RDWREXPDA = 0x07; // Read/Write, expand-down, accessed
    constexpr static uint8_t SEG_CODE_EX = 0x08;        // Execute-Only
    constexpr static uint8_t SEG_CODE_EXA = 0x09;       // Execute-Only, accessed
    constexpr static uint8_t SEG_CODE_EXRD = 0x0a;      // Execute/Read
    constexpr static uint8_t SEG_CODE_EXRDA = 0x0b;     // Execute/Read, accessed
    constexpr static uint8_t SEG_CODE_EXC = 0x0c;       // Execute-Only, conforming
    constexpr static uint8_t SEG_CODE_EXCA = 0x0d;      // Execute-Only, conforming, accessed
    constexpr static uint8_t SEG_CODE_EXRDC = 0x0e;     // Execute/Read, conforming
    constexpr static uint8_t SEG_CODE_EXRDCA = 0x0f;    // Execute/Read, conforming, accessed

    constexpr static uint64_t get_descriptor(uint64_t base, uint64_t limit, uint16_t flags)
    {
        uint64_t descriptor = 0;

        // Create the high 32 bit segment

        // base direct map
        descriptor = base & 0xff000000;

        // base 23-16 : 7-0
        descriptor |= (base >> 16) & 0x000000ff;

        // flags 16-11 : 24-19 7-0 : 15-8
        descriptor |= (flags << 8) & 0x00f0ff00;

        // limit direct map
        descriptor |= limit & 0x000f0000;

        // Shift by 32 to move to the lower half of the section
        descriptor <<= 32;

        // Create the low 32 bit segment
        // base 15-0 : 31-16
        descriptor |= (base << 16) & 0xffff0000;

        // limit direct map
        descriptor |= limit & 0x0000ffff;

        return descriptor;
    }

  public:
    static void init();
};
