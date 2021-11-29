#include <arch/x86/cpuid.hpp>
#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <math.hpp>
#include <types.hpp>
#include <video/framebuffer.hpp>

extern "C"
{
    __attribute__((used)) void nucleus_entry()
    {
        // Get the cpuid vendor (2 equals intel)
        auto cpuid_vendor = static_cast<uint8_t>(cpuid_get_vendor());

        // Create a framebuffer
        Framebuffer<uint8_t, 320, 200> vga_framebuffer{};

        // Draw a square
        vga_framebuffer.draw_rect(cpuid_vendor * 10, {{0, 0}, {100, 100}});

        // Get the framebuffer width
        size_t width = vga_framebuffer.width();

        // Get the framebuffer height
        size_t height = vga_framebuffer.height();

        // Get the depth (crude way doing so shown here)
        size_t depth = 8;

        // Load a arg list
        Array<void *, 4> arg_list_commitframebuffer = {&vga_framebuffer, &width, &height, &depth};

        // Make the syscall
        mk_syscall(reinterpret_cast<void **>(&arg_list_commitframebuffer), KsSyscallID::COMMITFRAMEBUFFER);
    }
}