CPPFLAGS 		+=							\
-target i486-unknown-unknown-elf			\
-march=i486									\
-mfpmath=387

NUCLEUS_SRCS 	+= 							\
arch/x86/x86_32/flush_gdt.S					\
arch/x86/x86_32/flush_idt.S					\
arch/x86/x86_32/flush_tss.S					\
arch/x86/x86_32/enter_v86.S					\
arch/x86/x86_32/cpuid_check_support.S		\
arch/x86/x86_32/fpu.cpp						\
arch/x86/x86_32/isr.cpp				\
arch/x86/x86_32/init_arch.cpp

QEMU			:=							\
qemu-system-i386

QEMUFLAGS 		+=							\
-cpu 486-v1
