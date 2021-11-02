.section .text
.global flush_gdt

.type flush_gdt, @function
    // void flush_gdt(GDT::GDT_Ptr * gdt_ptr)
flush_gdt:
    movl    4(%esp), %eax
    lgdt	(%eax)
    ljmp    $0x08, $.long_jump_gdt  // Long jump to our new code segment
.long_jump_gdt:

    // 0x10 is the offset in the GDT to our data segment
    mov	$0x10, %ax
    mov	%ax, %ds
    mov	%ax, %es
    mov	%ax, %fs
    mov	%ax, %gs
    mov	%ax, %ss

    ret
