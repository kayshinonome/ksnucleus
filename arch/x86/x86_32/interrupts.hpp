#pragma once

#include <array.hpp>
#include <event.hpp>
#include <types.hpp>

constexpr auto IDT_SIZE = 256;

class Interrupt_Data
{
  public:
    // Pushed by the processor automatically
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
} __attribute__((packed));

class IDT : public Array<uint64_t, IDT_SIZE>
{
  private:
    static uint64_t get_descriptor(void *handler);

  public:
    static bool init();
} __attribute__((packed));

inline Event_Engine<Interrupt_Data, IDT_SIZE> x86_interrupt_event_engine{};
