# Please note that even in aarch64 we cannot specify the cpu because there are armv8 processors with crc support

CPPFLAGS += 				\
--target=aarch64-elf 			\
-m64 

