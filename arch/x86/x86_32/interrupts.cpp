#include <arch/x86/io.hpp>
#include <arch/x86/x86_32/interrupts.hpp>
#include <core/ksnucleus.hpp>

extern "C"
{
    void irq_handler(Interrupt_Data data)
    {
        if (data.int_no > 0xff)
        {
            ks_fission("IRQ called was higher than possible");
        }

        // After every interrupt we need to send an EOI to the PICs
        // or they will not send another interrupt again

        if (data.int_no >= 40)
        {
            out8(0xA0, 0x20); // slave
        }
        out8(0x20, 0x20); // master

        // Inform the isr event engine that a event occured
        irq_event_engine.fire(data.int_no, data);
    }

    void isr_handler(Interrupt_Data data)
    {
        if (data.int_no > 31)
        {
            ks_fission("ISR called was higher than possible");
        }
        isr_event_engine.fire(data.int_no, data);
    }
}