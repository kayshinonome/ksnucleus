#include <core/ksnucleus.hpp>
#include <math.hpp>
#include <table.hpp>
#include <types.hpp>
#include <video/fonts.hpp>
#include <video/framebuffer.hpp>

extern "C"
{
    void nucleus_entry()
    {
        // Create a framebuffer
        Array<uint8_t, 1024> buffer{};

        // Fill that framebuffer with random data
        // ks_random(reinterpret_cast<void *>(buffer.raw()), buffer.size());

        // Shutdown the system
        ks_setsystemstate(SystemState::SHUTDOWN);
    }
}
