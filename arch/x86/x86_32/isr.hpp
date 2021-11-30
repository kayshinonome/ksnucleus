#pragma once
#include <event.hpp>
#include <types.hpp>

constexpr auto INTERRUPT_COUNT = 256;

class ISR_Data
{
  public:
    // Data segment selector
    uint32_t ds;

    // Pushed by pusha.
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t useless;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;

    // Interrupt number and error code (if applicable)
    uint32_t int_no;
    uint32_t err_code;

    // Pushed by the processor automatically
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
} __attribute__((packed));

inline Event_Engine<ISR_Data, INTERRUPT_COUNT> isr_event_engine;

constexpr auto a = sizeof(isr_event_engine);