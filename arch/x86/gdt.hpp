/**
 * @file gdt.hpp
 * @author Kay Shinonome (kayshinonome@protonmail.com)
 * @brief Header representing the GDT
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <utils.hpp>

class GDT
{
  private:
    /**
     * @brief Entry in the GDT
     *
     */
    class Entry
    {
      private:
        uint16_t limit_low;
        uint16_t base_low;
        uint8_t base_middle;
        uint8_t access;
        uint8_t granularity;
        uint8_t base_high;

      public:
        /**
         * @brief Descriptor type (0 for system, 1 for code/data)
         *
         */
        static constexpr uint16_t SEG_TYPE(uint16_t x)
        {
            return ((x) << 0x04);
        }

        /**
         * @brief Present
         *
         */
        static constexpr uint16_t SEG_PRES(uint16_t x)
        {
            return ((x) << 0x07);
        }

        /**
         * @brief Available for system use
         *
         */
        static constexpr uint16_t SEG_SAVL(uint16_t x)
        {
            return ((x) << 0x0c);
        }

        /**
         * @brief Long mode
         *
         */
        static constexpr uint16_t SEG_LONG(uint16_t x)
        {
            return ((x) << 0x0d);
        }

        /**
         * @brief Size (0 for 16-bit, 1 for 32)
         *
         */
        static constexpr uint16_t SEG_SIZE(uint16_t x)
        {
            return ((x) << 0x0e);
        }

        /**
         * @brief Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
         *
         */
        static constexpr uint16_t SEG_GRAN(uint16_t x)
        {
            return ((x) << 0x0f);
        }

        /**
         * @brief Set privilege level (0 - 3)
         *
         */
        static constexpr uint16_t SEG_PRIV(uint16_t x)
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

        /**
         * @brief Set GDT gate
         *
         * @param base
         * @param limit
         * @param flags
         */
        void set_gate(uint64_t base, uint64_t limit, uint16_t flags);

    } __attribute__((packed));

    /**
     * @brief The actual data for the GDT
     *
     */
    Array<Entry, 5> entries;

  public:
    /**
     * @brief Init the GDT and load it
     *
     */
    static void init();
};

/**
 * @brief Pointer to the GDT
 *
 */
class GDT_Ptr
{
  private:
    const uint16_t limit = sizeof(GDT) - 1;
    GDT *base;

  public:
    explicit GDT_Ptr(GDT *gdt)
    {
        base = gdt;
    }

} __attribute__((packed));