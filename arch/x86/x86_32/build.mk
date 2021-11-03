CPPFLAGS 		+=					\
-m32								\
-target i686-unknown-unknown-elf	\
-march=i686

NUCLEUS_SRCS 	+= 					\
arch/x86/x86_32/flush_gdt.S			\
arch/x86/x86_32/flush_idt.S			\
arch/x86/x86_32/flush_tss.S			\
arch/x86/x86_32/enter_v86.S			\
arch/x86/x86_32/init_arch.cpp

QEMU			:=					\
qemu-system-i386

QEMUFLAGS 		+=					\
-cpu pentium