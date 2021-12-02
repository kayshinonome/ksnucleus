.section .text
.global check_support
.type check_support, @function

.code32
check_support:
    // Save old stack base pointer
    push    %ebp
    // Set the new value
    mov     %esp, %ebp
    // Allocate space for stored EFLAGS
    sub $0x8, %esp
    // Store EFLAGS once
    pushfd
    // Store the EFLAGS again
    pushfd
    // Invert the ID bit in stored EFLAGS
    xorl    $0x00200000,(%esp)
    // Load stored EFLAGS (with ID bit inverted)
    popfd
    // Store EFLAGS again (ID bit may or may not be inverted)
    pushfd
    // %eax = modified EFLAGS (ID bit may or may not be inverted)
    pop     %eax
    // %eax = whichever bits were changed
    xor     (%esp), %eax
    // Get rid of the old EFLAGS
    popfd
    // %eax = zero if ID bit can't be changed, else non-zero
    and     $0x00200000, %eax
    // Branch if zero, indicating cpuid isn't supported
    jz      check_support_end
    // Write true because cpuid is supported
    mov     $0x1, %eax

check_support_end:
    // Deallocate the stack space used for EFLAGS
    mov     %ebp, %esp
    // Restore the old stack
    pop     %ebp
    ret
