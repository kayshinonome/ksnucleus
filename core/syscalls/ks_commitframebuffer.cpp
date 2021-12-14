#include <array.hpp>
#include <atomic.hpp>
#include <core/driver.hpp>
#include <core/ksnucleus.hpp>
#include <types.hpp>

SUBSYSCALL ks_commitframebuffer(const void *buffer, uint16_t width, uint16_t height, uint8_t depth)
{
    driver_collection.call_quark_service(Driver_Services::COMMITFRAMEBUFFER, {&buffer});
}