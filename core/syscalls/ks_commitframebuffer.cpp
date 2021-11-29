#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <core/quark.hpp>
#include <types.hpp>

SUBSYSCALL ks_commitframebuffer(void *buffer, size_t width, size_t height, uint8_t depth)
{
    quark_collection.call_quark_service(Quark_Services::COMMIT_FRAMEBUFFER, {&buffer});
}