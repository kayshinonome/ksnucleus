#include <arch/x86/io.hpp>
#include <core/driver.hpp>

Driver pc_8042{.reboot = []() {
    uint8_t good = 0x02;
    while ((good & 0x02) != 0)
    {
        good = in8(0x64);
    }
    out8(0x64, 0xFE);
    return true;
}};
