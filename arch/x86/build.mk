ifneq ($(CONFIG_KSNUCLEUS_ENDIAN),little)
	$(error "Unsupported endianness on x86, only little is possible")
endif

ifeq ($(CONFIG_KSNUCLEUS_WORD_WIDTH),16)
    $(error "ksnucleus does not support 16 bit mode")
else ifeq ($(CONFIG_KSNUCLEUS_WORD_WIDTH),32)
	include arch/x86/x86_16/build.mk
	include arch/x86/x86_32/build.mk
else ifeq ($(CONFIG_KSNUCLEUS_WORD_WIDTH),64)
	include arch/x86/x86_64/build.mk
else
	$(error "Unsupported word width")
endif

CPPFLAGS	+=							\
-DCONFIG_KSNUCLEUS_ARCH_X86

QEMUFLAGS	+=							\
-M smm=off

NUCLEUS_SRCS	+=						\
arch/x86/gdt.cpp						\
arch/x86/cpuid.cpp