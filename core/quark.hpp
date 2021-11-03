#include <utils.hpp>

class Quark
{
  public:
    bool (*is_viable)() = nullptr;
    void (*init)() = nullptr;
    void (*fini)() = nullptr;
    void (*commit_framebuffer)(void *data) = nullptr;
};