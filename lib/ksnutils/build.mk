LIBS += $(BUILD_DIR)/libksnutils.a 
LDFLAGS	+= -lksnutils

include lib/ksnutils/src/build.mk

LIBKSNUTILS_OBJS	:= $(LIBKSNUTILS_SRCS:%=$(BUILD_DIR)/%.o)
OBJS 				+= $(LIBKSNUTILS_OBJS)

$(BUILD_DIR)/libksnutils.a: $(LIBKSNUTILS_OBJS)
>	mkdir -p $(dir $@)
>	$(AR) $(ARFLAGS) $@ $^
