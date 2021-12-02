/*  multiboot.h - Multiboot header file.  */
/*  Copyright (C) 1999,2003,2007,2008,2009,2010  Free Software Foundation, Inc.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 *  deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL ANY
 *  DEVELOPER OR DISTRIBUTOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 *  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <types.hpp>

/**
 * @brief How many bytes from the start of the file we search for the header.
 *
 */
constexpr auto MULTIBOOT_SEARCH = 8192;
constexpr auto MULTIBOOT_HEADER_ALIGN = 4;

/**
 * @brief The magic field should contain this.
 *
 */
constexpr auto MULTIBOOT_HEADER_MAGIC = 0x1BADB002;

/**
 * @brief This should be in %eax.
 *
 */
constexpr auto MULTIBOOT_BOOTLOADER_MAGIC = 0x2BADB002;

/**
 * @brief  Alignment of multiboot modules.
 *
 */
constexpr auto MULTIBOOT_MOD_ALIGN = 0x00001000;

/**
 * @brief Alignment of the multiboot info structure.
 *
 */
constexpr auto MULTIBOOT_INFO_ALIGN = 0x00000004;

// Flags set in the 'flags' member of the multiboot header.

/**
 * @brief Align all boot modules on i386 page (4KB) boundaries.
 *
 */
constexpr auto MULTIBOOT_PAGE_ALIGN = 0x00000001;

/**
 * @brief Must pass memory information to OS.
 *
 */
constexpr auto MULTIBOOT_MEMORY_INFO = 0x00000002;

/**
 * @brief Must pass video information to OS.
 *
 */
constexpr auto MULTIBOOT_VIDEO_MODE = 0x00000004;

/**
 * @brief This flag indicates the use of the address fields in the header.
 *
 */
constexpr auto MULTIBOOT_AOUT_KLUDGE = 0x00010000;

// Flags to be set in the 'flags' member of the multiboot info structure.

/**
 * @brief is there basic lower/upper memory information?
 *
 */
constexpr auto MULTIBOOT_INFO_MEMORY = 0x00000001;

/**
 * @brief is there a boot device set?
 *
 */
constexpr auto MULTIBOOT_INFO_BOOTDEV = 0x00000002;

/**
 * @brief is the command-line defined?
 *
 */
constexpr auto MULTIBOOT_INFO_CMDLINE = 0x00000004;

/**
 * @brief are there modules to do something with?
 *
 */
constexpr auto MULTIBOOT_INFO_MODS = 0x00000008;

// These next two are mutually exclusive

/**
 * @brief is there a symbol table loaded?
 *
 */
constexpr auto MULTIBOOT_INFO_AOUT_SYMS = 0x00000010;

/**
 * @brief is there an ELF section header table?
 *
 */
constexpr auto MULTIBOOT_INFO_ELF_SHDR = 0X00000020;

/**
 * @brief is there a full memory map?
 *
 */
constexpr auto MULTIBOOT_INFO_MEM_MAP = 0x00000040;

/**
 * @brief Is there drive info?
 *
 */
constexpr auto MULTIBOOT_INFO_DRIVE_INFO = 0x00000080;

/**
 * @brief Is there a config table?
 *
 */
constexpr auto MULTIBOOT_INFO_CONFIG_TABLE = 0x00000100;

/**
 * @brief Is there a boot loader name?
 *
 */
constexpr auto MULTIBOOT_INFO_BOOT_LOADER_NAME = 0x00000200;

/**
 * @brief Is there a APM table?
 *
 */
constexpr auto MULTIBOOT_INFO_APM_TABLE = 0x00000400;

/**
 * @brief Is there video information?
 *
 */
constexpr auto MULTIBOOT_INFO_VBE_INFO = 0x00000800;
constexpr auto MULTIBOOT_INFO_FRAMEBUFFER_INFO = 0x00001000;

struct multiboot_header
{
    /**
     * @brief Must be MULTIBOOT_MAGIC - see above.
     *
     */
    uint32_t magic;

    /**
     * @brief Feature flags.
     *
     */
    uint32_t flags;

    /**
     * @brief The above fields plus this one must equal 0 mod 2^32.
     *
     */
    uint32_t checksum;

    /**
     * @brief These are only valid if MULTIBOOT_AOUT_KLUDGE is set.
     *
     */
    uint32_t header_addr;
    uint32_t load_addr;
    uint32_t load_end_addr;
    uint32_t bss_end_addr;
    uint32_t entry_addr;

    /**
     * @brief These are only valid if MULTIBOOT_VIDEO_MODE is set.
     *
     */
    uint32_t mode_type;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
};

/**
 * @brief The symbol table for a.out.
 *
 */
struct multiboot_aout_symbol_table
{
    uint32_t tabsize;
    uint32_t strsize;
    uint32_t addr;
    uint32_t reserved;
};

using multiboot_aout_symbol_table_t = struct multiboot_aout_symbol_table;

/**
 * @brief The section header table for ELF.
 *
 */
struct multiboot_elf_section_header_table
{
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;
};
using multiboot_elf_section_header_table_t = struct multiboot_elf_section_header_table;

struct multiboot_info
{
    /**
     * @brief Multiboot info version number
     *
     */
    uint32_t flags;

    /**
     * @brief Available memory from BIOS
     *
     */
    uint32_t mem_lower;
    uint32_t mem_upper;

    /**
     * @brief "root" partition
     *
     */
    uint32_t boot_device;

    /**
     * @brief Kernel command line
     *
     */
    uint32_t cmdline;

    /**
     * @brief Boot-Module list
     *
     */
    uint32_t mods_count;
    uint32_t mods_addr;

    union {
        multiboot_aout_symbol_table_t aout_sym;
        multiboot_elf_section_header_table_t elf_sec;
    } u;

    /**
     * @brief Memory Mapping buffer
     *
     */
    uint32_t mmap_length;
    uint32_t mmap_addr;

    /**
     * @brief Drive Info buffer
     *
     */
    uint32_t drives_length;
    uint32_t drives_addr;

    /**
     * @brief ROM configuration table
     *
     */
    uint32_t config_table;

    /**
     * @brief Boot Loader Name
     *
     */
    uint32_t boot_loader_name;

    /**
     * @brief APM table
     *
     */
    uint32_t apm_table;

    /**
     * @brief Video
     *
     */
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;

    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;

    enum struct multiboot_framebuffer_type : uint8_t
    {
        MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED = 0,
        MULTIBOOT_FRAMEBUFFER_TYPE_RGB = 1,
        MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT = 2
    };

    multiboot_framebuffer_type framebuffer_type;
    union {
        struct
        {
            uint32_t framebuffer_palette_addr;
            uint16_t framebuffer_palette_num_colors;
        };
        struct
        {
            uint8_t framebuffer_red_field_position;
            uint8_t framebuffer_red_mask_size;
            uint8_t framebuffer_green_field_position;
            uint8_t framebuffer_green_mask_size;
            uint8_t framebuffer_blue_field_position;
            uint8_t framebuffer_blue_mask_size;
        };
    };
};
using multiboot_info_t = multiboot_info;

struct multiboot_color
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct multiboot_mmap_entry
{
    uint32_t size;
    uint64_t addr;
    uint64_t len;

    enum struct multiboot_mmap_entry_type
    {
        MULTIBOOT_MEMORY_AVAILABLE = 1,
        MULTIBOOT_MEMORY_RESERVED = 2,
        MULTIBOOT_MEMORY_ACPI_RECLAIMABLE = 3,
        MULTIBOOT_MEMORY_NVS = 4,
        MULTIBOOT_MEMORY_BADRAM = 5
    };

    multiboot_mmap_entry_type type;
} __attribute__((packed));

using multiboot_memory_map_t = struct multiboot_mmap_entry;

struct multiboot_mod_list
{
    /**
     * @brief the memory used goes from bytes 'mod_start' to 'mod_end-1' inclusive
     *
     */
    uint32_t mod_start;
    uint32_t mod_end;

    /**
     * @brief Module command line
     *
     */
    uint32_t cmdline;

    /**
     * @brief padding to take it to 16 bytes (must be zero)
     *
     */
    uint32_t pad;
};

using multiboot_module_t = struct multiboot_mod_list;

/**
 * @brief APM BIOS info.
 *
 */
struct multiboot_apm_info
{
    uint16_t version;
    uint16_t cseg;
    uint32_t offset;
    uint16_t cseg_16;
    uint16_t dseg;
    uint16_t flags;
    uint16_t cseg_len;
    uint16_t cseg_16_len;
    uint16_t dseg_len;
};
