ifneq  ($(CONFIG_KSNUCLEUS_ARCH),x86)
	$(error "Non x86 archs not supported")
endif

LDFLAGS 	+= 								\
-Tplatform/pc/link.ld

NUCLEUS_SRCS += 							\
platform/pc/crt0.S							\
platform/pc/init_platform.cpp				\
platform/pc/vesa.cpp

CPPFLAGS	+=								\
-D__CONFIG_KSNUCLEUS_PLATFORM_PC__

inspect: $(BUILD_DIR)/nucleus
> 	if ! grub-file --is-x86-multiboot $^; then
>		echo "Nucleus failed Multiboot test"
>		exit 1
>	fi
