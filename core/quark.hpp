#pragma once
#include <array.hpp>

class Quark
{
  public:
    bool (*is_viable)() = nullptr;
    void (*init)() = nullptr;
    void (*fini)() = nullptr;
    void (*commit_framebuffer)(volatile void *data) = nullptr;
    void (*reboot)() = nullptr;
    void (*shutdown)() = nullptr;
};

template <size_t SIZE> class Quark_Collection : public Array<Quark, SIZE>
{
};
