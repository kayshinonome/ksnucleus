CPPFLAGS 		+=							\
-target i486-unknown-unknown-elf			\
-march=i486									\
-mfpmath=387

NUCLEUS_SRCS 	+= 							\
arch/x86/x86_16/detect_v86.S