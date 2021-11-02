#include <arch/x86/gdt.hpp>
#include <utils.hpp>

extern "C"
{
    void flush_gdt(GDT_Ptr *gdt_ptr);
}

void GDT::Entry::set_gate(uint64_t base, uint64_t limit, uint16_t flags)
{
    uint64_t descriptor = 0;

    // Create the high 32 bit segment

    // base direct map
    descriptor = base & 0xff000000;

    // base 23-16 : 7-0
    descriptor |= (base >> 16) & 0x000000ff;

    // flags 16-11 : 24-19 7-0 : 15-8
    descriptor |= (flags << 8) & 0x00f0ff00;

    // limit direct map
    descriptor |= limit & 0x000f0000;

    // Shift by 32 to move to the lower half of the section
    descriptor <<= 32;

    // Create the low 32 bit segment
    // base 15-0 : 31-16
    descriptor |= (base << 16) & 0xffff0000;

    // limit direct map
    descriptor |= limit & 0x0000ffff;

    // Copy the descriptor value into our GDT entries array
    copy_memory(&descriptor, reinterpret_cast<uint64_t *>(this), 1);
}

/**
 * @brief Init and load the gdt
 *
 */
void GDT::init()
{

    constexpr uint16_t GDT_CODE_PL0 = Entry::SEG_TYPE(1) | Entry::SEG_PRES(1) | Entry::SEG_SAVL(0) |
                                      Entry::SEG_LONG(0) | Entry::SEG_SIZE(1) | Entry::SEG_GRAN(1) |
                                      Entry::SEG_PRIV(0) | Entry::SEG_CODE_EXRD;

    constexpr uint16_t GDT_DATA_PL0 = Entry::SEG_TYPE(1) | Entry::SEG_PRES(1) | Entry::SEG_SAVL(0) |
                                      Entry::SEG_LONG(0) | Entry::SEG_SIZE(1) | Entry::SEG_GRAN(1) |
                                      Entry::SEG_PRIV(0) | Entry::SEG_DATA_RDWR;

    constexpr uint16_t GDT_CODE_PL3 = Entry::SEG_TYPE(1) | Entry::SEG_PRES(1) | Entry::SEG_SAVL(0) |
                                      Entry::SEG_LONG(0) | Entry::SEG_SIZE(1) | Entry::SEG_GRAN(1) |
                                      Entry::SEG_PRIV(3) | Entry::SEG_CODE_EXRD;

    constexpr uint16_t GDT_DATA_PL3 = Entry::SEG_TYPE(1) | Entry::SEG_PRES(1) | Entry::SEG_SAVL(0) |
                                      Entry::SEG_LONG(0) | Entry::SEG_SIZE(1) | Entry::SEG_GRAN(1) |
                                      Entry::SEG_PRIV(3) | Entry::SEG_DATA_RDWR;

    GDT gdt{};
    GDT_Ptr gdt_ptr(&gdt);

    /**
     * @brief Generated GDT is
     *  [0] 0x0000000000000000
     *  [1] 0x00CF9A000000FFFF
     *  [2] 0x00CF92000000FFFF
     *  [3] 0x00CFFA000000FFFF
     *  [4] 0x00CFF2000000FFFF
     *
     * In order to read the GDT in GDB, run
     * p/x (uint64_t[5])gdt
     *
     */

    // Null segment
    gdt.entries[0].set_gate(0, 0, 0);

    // Code segment
    gdt.entries[1].set_gate(0, 0x000fffff, GDT_CODE_PL0);

    // Data segment
    gdt.entries[2].set_gate(0, 0x000fffff, GDT_DATA_PL0);

    // User mode code segment
    gdt.entries[3].set_gate(0, 0x000fffff, GDT_CODE_PL3);

    // User mode data segment
    gdt.entries[4].set_gate(0, 0x000fffff, GDT_DATA_PL3);

    flush_gdt(&gdt_ptr);
}