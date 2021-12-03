CPPFLAGS 		+=								\
-target i386-unknown-unknown-elf				\
-march=i386										\
-m32											\
-mno-sse

NUCLEUS_SRCS 	+= 								\
arch/x86/x86_32/flush_gdt.S						\
arch/x86/x86_32/flush_idt.S						\
arch/x86/x86_32/flush_tss.S						\
arch/x86/x86_32/enter_v86.S						\
arch/x86/x86_32/cpuid_check_support.S			\
arch/x86/x86_32/fpu.cpp							\
arch/x86/x86_32/init_arch.cpp					\
arch/x86/x86_32/interrupts.cpp					\
arch/x86/x86_32/pic.cpp 						\
arch/x86/x86_32/math.cpp                                        

QEMU			:=								\
qemu-system-i386

QEMUFLAGS 		+=								\
-cpu 486-v1
