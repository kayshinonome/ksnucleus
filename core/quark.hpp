#pragma once

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