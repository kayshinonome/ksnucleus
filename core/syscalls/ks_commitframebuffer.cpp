#include <array.hpp>
#include <atomic.hpp>
#include <core/ksnucleus.hpp>
#include <core/quark.hpp>
#include <types.hpp>

SUBSYSCALL ks_commitframebuffer(const void *buffer, uint16_t width, uint16_t height, uint8_t depth)
{
    quark_collection.call_quark_service(Quark_Services::COMMITFRAMEBUFFER, {&buffer});
}