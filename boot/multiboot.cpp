#include <boot/multiboot.hpp>
#include <core/init.hpp>
#include <core/ksnucleus.hpp>
#include <core/registry.hpp>
#include <types.hpp>

constexpr uint32_t magic = MULTIBOOT_HEADER_MAGIC;
constexpr uint32_t flags = MULTIBOOT_VIDEO_MODE | MULTIBOOT_MEMORY_INFO;
constexpr uint32_t checksum = 0 - (magic + flags);

__attribute__((used, section(".multiboot"))) const multiboot_header ksnucleus_multiboot_header{.magic = magic,
                                                                                               .flags = flags,
                                                                                               .checksum = checksum,
                                                                                               .header_addr = 0,
                                                                                               .load_addr = 0,
                                                                                               .load_end_addr = 0,
                                                                                               .bss_end_addr = 0,
                                                                                               .entry_addr = 0,
                                                                                               .mode_type = 0,
                                                                                               .width = 320,
                                                                                               .height = 200,
                                                                                               .depth = 8};

uint32_t passed_in_multiboot_magic;
uint32_t passed_in_multiboot_info;

bool ksinit::boot()
{
    if (passed_in_multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        ks_fission("Invalid multiboot magic");
    }

    auto *info = reinterpret_cast<multiboot_info *>(passed_in_multiboot_info);
    global_registry.set(Registry_Keys::SCREEN_WIDTH, info->framebuffer_width);
    global_registry.set(Registry_Keys::SCREEN_HEIGHT, info->framebuffer_height);
    global_registry.set(Registry_Keys::SCREEN_DEPTH, info->framebuffer_bpp);
    return true;
}
