#include <arch/x86/x86_32/v86.hpp>
#include <core/quark.hpp>
#include <core/registry.hpp>
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
    // Since we don't have v86 working yet, we will see what the global registry has to say about the screen properties
    return global_registry.screen_width * global_registry.screen_height * global_registry.screen_depth;
}

Quark pc_vesa{.commitframebuffer = [](void *data) {
    if (bios_data_area->CURRENT_VIDEO_MODE != 0)
    {
        return false;
    }

    auto *vesa_video_memory = reinterpret_cast<volatile uint8_t *>(get_vesa_framebuffer_location());
    auto *framebuffer = reinterpret_cast<volatile uint8_t *>(data);
    auto length = get_vesa_framebuffer_size();
    copy_memory(framebuffer, vesa_video_memory, length);
    return true;
}};
