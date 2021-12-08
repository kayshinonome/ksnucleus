SHELL := bash
.ONESHELL:
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules

ifeq ($(origin .RECIPEPREFIX), undefined)
  $(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
endif
.RECIPEPREFIX = >
.PHONY: clean 											\
		run										\
		inspect										\
		debug										\
		all										\
		docs										\
		distclean									\
		package										\
		package_run									\
		package_debug									\
		help

.DEFAULT_GOAL := all

CUSTOM_CONFIG_SET := false

-include config.mk

ifeq ($(CUSTOM_CONFIG_SET),false)
    include config/x86-pc-32-little.mk
endif

BUILD_DIR     		= 									\
build/$(CONFIG_KSNUCLEUS_ARCH)-$(CONFIG_KSNUCLEUS_PLATFORM)-$(CONFIG_KSNUCLEUS_WORD_WIDTH)-$(CONFIG_KSNUCLEUS_ENDIAN)

INCLUDE_DIRS  		+=									\
$(PWD)												\
$(PWD)/lib/ksnutils/include									\

INCLUDE_FLAGS 		+=									\
$(addprefix -I,$(INCLUDE_DIRS))

CPPFLAGS      		+=									\
-MMD                    									\
-MP                     									\
-Wall	                									\
-Wextra	                									\
-Wpedantic											\
-Wabi												\
-Werror												\
-Wno-unused-parameter				                				\
-Wno-unused-variable				                				\
-Wno-unused-function				                				\
-Wno-nested-anon-types										\
-Wno-gnu-anonymous-struct									\
-Wno-writable-strings										\
-fstack-protector-strong				            				\
-fno-builtin											\
-fno-delete-null-pointer-checks                                                                 \
-integrated-as

# The previous check is needed because clang is being annoying

CXXFLAGS      		+=									\
-std=c++20											\
-fno-exceptions						               				\
-fno-rtti											\
-fno-unwind-tables					                			\
-fno-non-call-exceptions									\
-Wno-unused-private-field			              					\
-nostdinc

LDFLAGS      		+=									\
-L$(BUILD_DIR)          									\
-ffreestanding						                			\
-nodefaultlibs						                			\
-static                 									\
-nostartfiles											\
-fuse-ld=lld 											\
-v 	
	
ASFLAGS       		+=
ARFLAGS       		+=									\
-crs

QEMUFLAGS			+=								\
-d int,in_asm											\
-no-reboot 											\
-no-shutdown 

ifeq ($(CONFIG_KSNUCLEUS_DEBUG),true)

CPPFLAGS		  	+=								\
-D__CONFIG_KSNUCLEUS_DEBUG__									\
-Og												\
-g
else

CPPFLAGS		  	+=								\
-O2												\
-flto
endif

include 											\
arch/build.mk											\
boot/build.mk											\
core/build.mk											\
filesystem/build.mk										\
lib/build.mk											\
platform/build.mk										\
video/build.mk

NUCLEUS_OBJS			=  $(NUCLEUS_SRCS:%=$(BUILD_DIR)/%.o)
OBJS 				+= $(NUCLEUS_OBJS)

help:
> @printf "Ksnucleus build system\n"
> @printf "Options\n"
> @printf "\t clean \t\t - Clean the tree of all binaries\n"
> @printf "\t distclean \t - Prepare the source tree for distribution\n"
> @printf "\t run \t\t - Run the kernel in a emulator (target defined)\n"
> @printf "\t debug \t\t - Debug the kernel in a emulator (target defined)\n"
> @printf "\t inspect \t - Ensure the kernel is valid (target defined)\n"
> @printf "\t docs \t\t - Generate doxygen documentation at /docs\n"
> @printf "\t package \t - Generate the package required for normal runtime on the target system (target defined)\n"
> @printf "\t package_run \t - Generate the package and run it in the emulator (target defined)\n"
> @printf "\t package_debug \t - Generate the package and debug it in the emulator (target defined)\n"
> @printf "\t help \t\t - Print this help message\n"

$(BUILD_DIR)/nucleus: $(NUCLEUS_OBJS) $(LIBS)
>	mkdir -pv $(dir $@)
>	$(LD) -o $@ $(NUCLEUS_OBJS) $(LDFLAGS) $(CPPFLAGS) 

all: $(BUILD_DIR)/nucleus inspect
> @echo "Compiling complete"

$(BUILD_DIR)/%.cpp.o: %.cpp
>	mkdir -pv $(dir $@)
>	$(CXX) -c $< -o $@ $(INCLUDE_FLAGS) $(CPPFLAGS) $(CXXFLAGS) 

$(BUILD_DIR)/%.S.o: %.S
>	mkdir -pv $(dir $@)
>	$(AS) -c $< -o $@ $(INCLUDE_FLAGS) $(CPPFLAGS) $(ASFLAGS)

debug: $(BUILD_DIR)/nucleus
>	$(QEMU) $(QEMUFLAGS) -s -S -kernel $^

run: $(BUILD_DIR)/nucleus
>	$(QEMU) $(QEMUFLAGS) -kernel $^

clean:
>	rm -rfv build docs compile_commands.json

distclean: clean
>	rm -rfv .cache config.mk

docs:
>	doxygen

DEPS = $(OBJS:.o=.d)
-include $(DEPS)
