#include <arch/x86/io.hpp>
#include <arch/x86/x86_32/pic.hpp>
#include <types.hpp>

void PIC::sendeoi(uint8_t irq)
{
    if (irq >= 8)
    {
        out8(PIC2_COMMAND, PIC_EOI);
    }

    out8(PIC1_COMMAND, PIC_EOI);
}

void PIC::remap(uint32_t offset1, uint32_t offset2)
{
    uint8_t a1 = 0;
    uint8_t a2 = 0;

    a1 = in8(PIC1_DATA); // save masks
    a2 = in8(PIC2_DATA);

    // starts the initialization sequence (in cascade mode)
    out8(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    out8(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    // ICW2: Master PIC vector offset
    out8(PIC1_DATA, offset1);

    // ICW2: Slave PIC vector offset
    out8(PIC2_DATA, offset2);

    // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    out8(PIC1_DATA, 4);

    // ICW3: tell Slave PIC its cascade identity (0000 0010)
    out8(PIC2_DATA, 2);

    out8(PIC1_DATA, ICW4_8086);
    out8(PIC2_DATA, ICW4_8086);

    // restore saved masks.
    out8(PIC1_DATA, a1);
    out8(PIC2_DATA, a2);
}
