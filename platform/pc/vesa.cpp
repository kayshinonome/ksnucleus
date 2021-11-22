#include <arch/x86/x86_32/v86.hpp>
#include <core/quark.hpp>
#include <platform/pc/bios.hpp>
#include <utils.hpp>
#include <video/framebuffer.hpp>

void *get_vesa_framebuffer_location()
{
    // FIXME: Quick hack, should be read from bios instead
    return reinterpret_cast<void *>(0xa0000);
}

size_t get_vesa_framebuffer_size()
{
    // Another quick hack
    return 320 * 200 * 1;
}

Quark pc_vesa{.is_viable = []() { return bios_data_area->CURRENT_VIDEO_MODE == 0; },
              .init = []() {},
              .fini = []() {},
              .commit_framebuffer =
                  [](volatile void *data) {
                      auto *vesa_video_memory = reinterpret_cast<volatile uint8_t *>(get_vesa_framebuffer_location());
                      auto *framebuffer = reinterpret_cast<volatile uint8_t *>(data);
                      auto length = get_vesa_framebuffer_size();
                      copy_memory(framebuffer, vesa_video_memory, length);
                  }};