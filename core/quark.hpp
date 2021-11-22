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

class Quark_Collection : public Array<Quark *, 0xff>
{
  public:
    bool add_quark(Quark &quark)
    {

        for (size_t x = 0, len = length(); x < len; x++)
        {
            if ((*this)[x] == nullptr)
            {
                (*this)[x] = &quark;
                return true;
            }
        }
        return false;
    }
};

inline Quark_Collection quark_collection{};