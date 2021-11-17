#include <arch/x86/x86_32/v86.hpp>
#include <core/quark.hpp>
#include <platform/pc/bios.hpp>
#include <utils.hpp>
#include <video/framebuffer.hpp>

volatile void *get_vesa_framebuffer_location()
{
    return nullptr;
}

size_t get_vesa_framebuffer_size()
{
    return 0;
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