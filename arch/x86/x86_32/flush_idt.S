.section .text
.global flush_idt
.type flush_idt, @function

.code32
flush_idt:
    movl	4(%esp),%eax
    lidt	(%eax)
    ret
