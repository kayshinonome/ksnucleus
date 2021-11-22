#include <boot/multiboot.hpp>
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
