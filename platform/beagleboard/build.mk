ifneq ($(CONFIG_KSNUCLEUS_ARCH), arm)
	$(error "Non arm archs are not supported")
endif


ifneq ($(CONFIG_KSNUCLEUS_WORD_WIDTH), 64)
	$(error "Beagleboard has a 64 bit processor and ksnucleus will only run native executables")
endif

CPPFLAGS 	+= 	\
-D__CONFIG_KSNUCLEUS_PLATFORM_BEAGLEBOARD__

CPPFLAGS        +=      \
-march=armv8-a
