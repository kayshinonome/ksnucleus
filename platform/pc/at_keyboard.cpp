#include <core/quark.hpp>
#include <future.hpp>
#include <platform/pc/bios.hpp>
#include <types.hpp>

Quark pc_at_keyboard{.getkeycode = [](Future<uint16_t> &data) {
    data.callback = []() {
        uint16_t a = 0;
        return a;
    };
    return false;
}};

