#include <arch/x86/io.hpp>
#include <arch/x86/x86_32/interrupts.hpp>
#include <arch/x86/x86_32/pic.hpp>

/**
 * @brief A pointer to the array of interrupt handlers.
 *
 */
class IDT_Register
{
  public:
    // IDT length + size of each gate minus 1
    const uint16_t limit = IDT::length() * IDT::sizeof_type() - 1;
    const IDT *base;

    explicit IDT_Register(const IDT &idt) : base(&idt)
    {
    }

} __attribute__((packed));

class IDT_Gate
{
  public:
    /**
     * @brief Lower 16 bits of handler function address
     *
     */
    uint16_t low_offset;

    /**
     * @brief Kernel segment selector
     *
     */
    uint16_t sel;

    /**
     * @brief Always zero
     *
     */
    uint8_t always0;

    /**
     * @brief The flags concerning the idt
     *
     */
    uint8_t flags;

    /**
     * @brief Higher 16 bits of handler function address
     *
     */
    uint16_t high_offset;

} __attribute__((packed));

extern "C"
{
    /**
     * @brief Handle all the interrupts
     * NOTE: This function **must** be marked as noinline, otherwise the compiler will inline it yet leave a copy of it
     * in the nucleus
     * @param data
     * @param id
     */
    __attribute__((no_caller_saved_registers, noinline)) void master_interrupt_handler(Interrupt_Data *data, size_t id)
    {
        // Check if irq
        if (id > 31)
        {
            // After every interrupt we need to send an EOI to the PICs
            // or they will not send another interrupt again

            if (id >= 40)
            {
                out8(0xA0, 0x20); // slave
            }
            out8(0x20, 0x20); // master
        }

        // Inform the event engine that a event occured
        x86_interrupt_event_engine.fire(id, *data);
    }

    __attribute__((interrupt)) void irq_handler(Interrupt_Data *data)
    {
        master_interrupt_handler(data, 0);
    }

    __attribute__((interrupt)) void isr_handler(Interrupt_Data *data, size_t id)
    {
        master_interrupt_handler(data, id);
    }

    void flush_idt(IDT_Register *idt_reg);
}

uint64_t IDT::get_descriptor(void *handler)
{

    static_assert(sizeof(IDT_Gate) == sizeof(uint64_t));

    constexpr uint16_t KERNEL_CS = 0x08;

    IDT_Gate descriptor{};
    auto handler_addr = reinterpret_cast<uint32_t>(handler);

    descriptor.low_offset = static_cast<uint16_t>(handler_addr & 0xffff);
    descriptor.sel = KERNEL_CS;
    descriptor.always0 = 0;
    descriptor.flags = 0x8e;
    descriptor.high_offset = static_cast<uint16_t>((handler_addr >> 16) & 0xffff);

    return *reinterpret_cast<uint64_t *>(&descriptor);
}

bool IDT::init()
{
    // Set all of the IDT table I care about at the moment
    __attribute__((aligned(0x10))) static IDT idt{};

    for (auto x = 0; x < 32; x++)
    {
        idt[x] = IDT::get_descriptor(reinterpret_cast<void *>(isr_handler));
    }

    for (auto x = 0; x < 16; x++)
    {
        idt[x + 32] = IDT::get_descriptor(reinterpret_cast<void *>(irq_handler));
    }

    // Produce the idt register
    IDT_Register idt_reg(idt);

    PIC::remap(0x20, 0x28);

    // Load the IDT
    flush_idt(&idt_reg);

    // Enable interrupts
    asm volatile("sti");

    // Hope nothing fissions
    return true;
}