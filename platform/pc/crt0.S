#define ALIGNMENT 4096

// Reserve a stack for the initial thread.
.section .bss
.align ALIGNMENT
stack_bottom:
.skip 1024 * 1024  // Stack
stack_top:

// The kernel entry point.
.section .text
.align ALIGNMENT
.global _start
.type _start, @function
_start:

  // Disable interrupts
  cli

  // Move the multiboot magic to a place that our code can read it (defined in boot/multiboot.cpp)
  mov %eax, passed_in_multiboot_magic
  // Move the pointer to the the multiboot info to a place that the code can read it (defined in boot/multiboot.cpp)
  mov %ebx, passed_in_multiboot_info

  mov $stack_top, %esp

  // Reset EFLAGS
  pushl $0
  popf

  call _init
  call nucleus_init
  call nucleus_entry
  call _fini

  // Hang if nucleus_entry unexpectedly returns.
  cli

_stop:	
  hlt
  jmp _stop


.size _start, . - _start
