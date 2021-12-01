#pragma once
#include <types.hpp>

class PIC
{
  private:
    // IO base address for master PIC
    constexpr static auto PIC1 = 0x20;
    // IO base address for slave PIC
    constexpr static auto PIC2 = 0xA0;
    constexpr static auto PIC1_COMMAND = PIC1;
    constexpr static auto PIC1_DATA = (PIC1 + 1);
    constexpr static auto PIC2_COMMAND = PIC2;
    constexpr static auto PIC2_DATA = (PIC2 + 1);
    // End-of-interrupt command code
    constexpr static auto PIC_EOI = 0x20;

    // ICW4 (not) needed
    constexpr static auto ICW1_ICW4 = 0x01;
    // Single (cascade) mode
    constexpr static auto ICW1_SINGLE = 0x02;
    // Call address interval 4 (8)
    constexpr static auto ICW1_INTERVAL4 = 0x04;
    // Level triggered (edge) mode
    constexpr static auto ICW1_LEVEL = 0x08;
    // Initialization - required!
    constexpr static auto ICW1_INIT = 0x10;
    // 8086/88 (MCS-80/85) mode
    constexpr static auto ICW4_8086 = 0x1;
    // Auto (normal) EOI
    constexpr static auto ICW4_AUTO = 0x02;
    // Buffered mode/slave
    constexpr static auto ICW4_BUF_SLAVE = 0x08;
    // Buffered mode/master
    constexpr static auto ICW4_BUF_MASTER = 0x0C;
    // Special fully nested (not)
    constexpr static auto ICW4_SFNM = 0x10;

  public:
    static void sendeoi(uint8_t irq);

    static void remap(uint32_t offset1, uint32_t offset2);
};