#include <core/quark.hpp>
#include <future.hpp>
#include <platform/pc/bios.hpp>
#include <types.hpp>

Quark pc_at_keyboard{.is_viable = [](Quark_Services quark_services) { return false; },
                     .getkeycode =
                         [](Future<uint16_t> &data) {
                             data.callback = []() {
                                 uint16_t a = 0;
                                 return a;
                             };
                         }};

