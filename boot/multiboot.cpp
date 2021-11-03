#include <boot/multiboot.hpp>
#include <utils.hpp>

constexpr uint32_t magic = MULTIBOOT_HEADER_MAGIC;
constexpr uint32_t flags = 0;
constexpr uint32_t checksum = 0 - (magic + flags);

__attribute__((used)) __attribute__((used, section(".multiboot")))
const multiboot_header ksnucleus_multboot_multiboot_header{.magic = magic, .flags = flags, .checksum = checksum};