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

volatile uint32_t passed_in_multiboot_magic;
volatile uint32_t passed_in_multiboot_info;

void ksinit::boot()
{
    if (passed_in_multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        ks_fission("Invalid multiboot magic");
    }

    // NOLINTNEXTLINE(performance-no-int-to-ptr)
    auto *info = reinterpret_cast<multiboot_info *>(passed_in_multiboot_info);
    global_registry.screen_width = info->framebuffer_width;
    global_registry.screen_height = info->framebuffer_height;
    global_registry.screen_depth = info->framebuffer_bpp;
}
