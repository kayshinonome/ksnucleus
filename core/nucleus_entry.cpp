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
        Array<uint8_t, 1024> *buffer = nullptr;

        ks_allocatememory(reinterpret_cast<void **>(&buffer), buffer->size());

        // Fill that framebuffer with random data
        ks_random(reinterpret_cast<void *>(buffer->raw()), buffer->size());

        // Shutdown the system
        ks_setsystemstate(SystemState::SHUTDOWN);
    }
}
