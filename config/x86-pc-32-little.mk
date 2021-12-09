# Config for 32 bit x86 on IBM compatible PCs
CUSTOM_CONFIG_SET					:=  true
CC									:=	clang
CXX									:=	clang
LD									:=	clang
AS									:=  clang
AR									:=	llvm-ar
CPPFLAGS							:=
CXXFLAGS      						:=
CFLAGS        						:=
LDFLAGS       						:=
ASFLAGS       						:=
ARFLAGS       						:=
CONFIG_KSNUCLEUS_ARCH				:=	x86
CONFIG_KSNUCLEUS_PLATFORM			:=	pc
CONFIG_KSNUCLEUS_WORD_WIDTH			:=	32
CONFIG_KSNUCLEUS_ENDIAN				:=	little
CONFIG_KSNUCLEUS_DEBUG				:=	true

# PC options
CONFIG_KSNUCLEUS_8042_SUPPORT		:=	true
CONFIG_KSNUCLEUS_VESA_SUPPORT		:=	true
CONFIG_KSNUCLEUS_MULTIBOOT_SUPPORT	:=	true
