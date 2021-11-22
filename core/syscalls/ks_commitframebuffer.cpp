#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <core/quark.hpp>
#include <types.hpp>

SUBSYSCALL ks_commitframebuffer(void *buffer, size_t width, size_t height, uint8_t depth)
{
    // FIXME: This is a testing hack since a full quark framework isnt in place
    extern Quark pc_vesa;
    pc_vesa.commit_framebuffer(buffer);
}