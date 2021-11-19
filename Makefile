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
.PHONY: clean run inspect debug all docs distclean
.DEFAULT_GOAL := all

CUSTOM_CONFIG_SET := false

-include config.mk

ifeq ($(CUSTOM_CONFIG_SET),false)
    include config/x86-pc-32-little.mk
endif

BUILD_DIR     		= 								\
build/$(CONFIG_KSNUCLEUS_ARCH)-$(CONFIG_KSNUCLEUS_PLATFORM)-$(CONFIG_KSNUCLEUS_WORD_WIDTH)-$(CONFIG_KSNUCLEUS_ENDIAN)

INCLUDE_DIRS  		+=								\
$(PWD)												\
$(PWD)/lib/ksnutils/include							\

INCLUDE_FLAGS 		+=								\
$(addprefix -I,$(INCLUDE_DIRS))

CPPFLAGS      		+=								\
-MMD                    							\
-MP                     							\
-Wall	                							\
-Wextra	                							\
-Wpedantic											\
-Wabi												\
-Werror												\
-Wno-unused-parameter				                \
-Wno-write-strings					                \
-Wno-unused-variable				                \
-Wno-unused-function				                \
-Wno-c++20-designator								\
-Wno-nested-anon-types								\
-Wno-gnu-anonymous-struct							\
-Wno-gnu-array-member-paren-init					\
-fstack-protector-strong				            \
-fno-common											\
-fno-builtin										\
-ffunction-sections									\
-fdata-sections

CXXFLAGS      		+=								\
-std=c++20											\
-fno-exceptions						               	\
-fno-rtti											\
-fno-unwind-tables					                \
-fno-non-call-exceptions							\
-Wno-unused-private-field			              	\
-Wno-deprecated-copy								\
-nostdinc

LDFLAGS      		+=								\
-L$(BUILD_DIR)          							\
-ffreestanding						                \
-nodefaultlibs						                \
-static                 							\
-nostartfiles										\
-fuse-ld=lld

ASFLAGS       		+=
ARFLAGS       		+=								\
-crs

QEMUFLAGS			+=								\
-d int,in_asm										\
-no-reboot 											\
-no-shutdown 

ifeq ($(CONFIG_KSNUCLEUS_DEBUG),true)

CPPFLAGS		  	+=								\
-DDEBUG												\
-Og													\
-g
else

CPPFLAGS		  	+=								\
-DNDEBUG											\
-O2													\
-flto
endif

include 											\
arch/build.mk										\
boot/build.mk										\
core/build.mk										\
lib/build.mk										\
platform/build.mk									\
video/build.mk

NUCLEUS_OBJS		= $(NUCLEUS_SRCS:%=$(BUILD_DIR)/%.o)
OBJS 				+= $(NUCLEUS_OBJS)

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
>

run: $(BUILD_DIR)/nucleus
>	$(QEMU) $(QEMUFLAGS) -kernel $^
>

clean:
>	rm -rfv build docs compile_commands.json

distclean: clean
>	rm -rfv .cache config.mk

docs:
>	doxygen

DEPS = $(OBJS:.o=.d)
-include $(DEPS)