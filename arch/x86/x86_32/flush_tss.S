.section .text

// Allows our code to call tss_flush().
.global flush_tss
.type flush_tss, @function
flush_tss:
    mov $0x2B, %ax  // Load the index of our TSS structure - The index is
                    // 0x28, as it is the 5th selector and each is 8 bytes
                    // long, but we set the bottom two bits (making 0x2B)
                    // so that it has an RPL of 3, not zero.
    ltr %ax         // Load 0x2B into the task state register.
    ret
