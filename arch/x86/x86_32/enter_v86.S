.section .text
.global flush_gdt
.type flush_gdt, @function

#define VM_FLAGS $0x20000

// you should declare this function as :
// extern void enter_v86(uint32_t ss, uint32_t esp, uint32_t cs, uint32_t eip);
enter_v86:
    mov    %ebp,%esp
    push   0x4(%ebp)
    push   0x8(%ebp)
    pushf  
    orl    VM_FLAGS,(%esp)
    push   0xc(%ebp)
    push   0x10(%ebp)
    iret
