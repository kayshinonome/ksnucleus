ifneq  ($(CONFIG_KSNUCLEUS_ARCH),x86)
	$(error "Non x86 archs not supported")
endif

include \
platform/pc/multiboot/build.mk

LDFLAGS 	+= 								\
-Tplatform/pc/link.ld

NUCLEUS_SRCS += 								\
platform/pc/crt0.S								\
platform/pc/init_platform.cpp					\

CPPFLAGS	+=								\
-DCONFIG_KSNUCLEUS_PLATFORM_PC

QEMUFLAGS	+=								\
-vga cirrus

inspect: $(BUILD_DIR)/nucleus
> 	if ! grub-file --is-x86-multiboot $^; then
>		echo "Nucleus failed Multiboot test"
>		exit 1
>	fi

$(BUILD_DIR)/ksnucleus.iso: inspect $(BUILD_DIR)/nucleus
>	mkdir -pv $(BUILD_DIR)/_tmp/root/boot/grub
> 	cp -v $(BUILD_DIR)/nucleus $(BUILD_DIR)/_tmp/root
>	if ! grub-script-check $(PWD)/platform/pc/grub.cfg; then
>		exit 1
> 	fi
> 	cp -v $(PWD)/platform/pc/grub.cfg $(BUILD_DIR)/_tmp/root/boot/grub
> 	grub-mkrescue -o $@ $(BUILD_DIR)/_tmp/root
> 	rm -rfv $(BUILD_DIR)/_tmp/root/

package: $(BUILD_DIR)/ksnucleus.iso

package_run: package
>	$(QEMU) $(QEMUFLAGS) $(BUILD_DIR)/ksnucleus.iso

package_debug: package	
>	$(QEMU) $(QEMUFLAGS) -s -S $(BUILD_DIR)/ksnucleus.iso

ifeq ($(CONFIG_KSNUCLEUS_8042_SUPPORT), true)
	NUCLEUS_SRCS +=  \
	platform/pc/8042.cpp
	CPPFLAGS	 +=  \
	-DCONFIG_KSNUCLEUS_8042_SUPPORT
endif

ifeq ($(CONFIG_KSNUCLEUS_VESA_SUPPORT), true)
	NUCLEUS_SRCS +=  \
	platform/pc/vesa.cpp
	CPPFLAGS	 +=  \
	-DCONFIG_KSNUCLEUS_VESA_SUPPORT
endif