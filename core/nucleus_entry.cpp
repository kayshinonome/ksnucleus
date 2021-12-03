#include <core/ksnucleus.hpp>
#include <math.hpp>
#include <types.hpp>
#include <video/fonts.hpp>
#include <video/framebuffer.hpp>

extern "C"
{
    __attribute__((used)) void nucleus_entry()
    {
        // Create a framebuffer
        Framebuffer<uint8_t, 320, 200> vga_framebuffer;

        // Fill that framebuffer with random data
        ks_random(&vga_framebuffer.as_flat_array(), vga_framebuffer.as_flat_array().length());

        // Commit that framebuffer
        ks_commitframebuffer(&vga_framebuffer, vga_framebuffer.width(), vga_framebuffer.height(), 8);

        // Shutdown the system
        ks_setsystemstate(SystemState::SHUTDOWN);
    }
}
