#include <boot/multiboot.hpp>
#define ALIGNMENT 4096

.section .multiboot
.align 4
.long MULTIBOOT_HEADER_MAGIC
.long 0
.long -(MULTIBOOT_HEADER_MAGIC)

// Reserve a stack for the initial thread.
.section .bss
.align ALIGNMENT
stack_bottom:
.skip 500 * 1024  // Stack
stack_top:

// The kernel entry point.
.section .text
.align ALIGNMENT
.global _start
.type _start, @function
_start:

  // Disable interrupts
  cli

  mov $stack_top, %esp

  // Reset EFLAGS
  pushl $0
  popf

  call _init
  call nucleus_entry
  call _fini

  // Hang if nucleus_entry unexpectedly returns.
  cli

_stop:	
  hlt
  jmp _stop


.size _start, . - _start
