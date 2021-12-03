#include <arch/x86/io.hpp>
#include <core/quark.hpp>

Quark pc_8042{.is_viable = [](Quark_Services quark_service) { return quark_service == Quark_Services::REBOOT; },
              .reboot =
                  []() {
                      uint8_t good = 0x02;
                      while ((good & 0x02) != 0)
                      {
                          good = in8(0x64);
                      }
                      out8(0x64, 0xFE);
                  }};