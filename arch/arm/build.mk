ifeq ($(CONFIG_KSNUCLEUS_WORD_WIDTH),16)
    $(error "ksnucleus does not support 16 bit mode")
else ifeq ($(CONFIG_KSNUCLEUS_WORD_WIDTH),32)
	include arch/arm/aarch32/build.mk
else ifeq ($(CONFIG_KSNUCLEUS_WORD_WIDTH),64)
	include arch/arm/aarch64/build.mk
else
	$(error "Unsupported word width")
endif

ifeq ($(CONFIG_KSNUCLEUS_ENDIAN), little)
	CPPFLAGS += \
	-mlittle-endian
else ifeq ($(CONFIG_KSNUCLEUS_ENDIAN), big)
	CPPFLAGS += \
	-mbig-endian
endif

CPPFLAGS	+=							\
-D__CONFIG_KSNUCLEUS_ARCH_ARM__
