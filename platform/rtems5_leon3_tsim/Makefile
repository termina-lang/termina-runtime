

CROSS:=/opt/rcc-1.3.2-gcc/bin/sparc-gaisler-rtems5-

CC:=$(CROSS)gcc --pipe
AR:=$(CROSS)ar

MKDIR:=mkdir

TARGET_FOLDER_NAME:=rtems5_leon3_tsim

INCLUDE_DIRS+=$R/api
INCLUDE_DIRS+=$R/os/rtems5/include
INCLUDE_DIRS+=$R/platform/rtems5_leon3_tsim/include

CPPFLAGS:=-O0 -g3 -Wall -c -fmessage-length=0 -mcpu=leon3 -qbsp=leon3
CPPFLAGS+=-I/opt/rcc-1.3.2-gcc/sparc-gaisler-rtems5/leon3/lib/include
CPPFLAGS+=$(patsubst %,-I %,$(INCLUDE_DIRS))

SRCS:=$(wildcard $R/common/*.c)
SRCS+=$(wildcard $R/os/rtems5/src/*.c)
SRCS+=$(wildcard $R/platform/rtems5_leon3_tsim/src/*.c)

OBJS:=$(patsubst %.c, %.o, $(patsubst $R/%, $R/lib/$(TARGET_FOLDER_NAME)/%, $(SRCS)))

# compilation targets
TARGET:=$R/lib/$(TARGET_FOLDER_NAME)/libtermina_rtems5_leon3_tsim.a

# dependency files
DEPS:=$(patsubst %.o,%.d,$(OBJS))

$R/lib/$(TARGET_FOLDER_NAME)/%.o: $R/%.c
	@echo " CC  $<"
	@$(MKDIR) -p $(@D)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c -o $@ $<

rtems5_leon3_tsim: $(TARGET)

$(TARGET): $(OBJS)
	@echo " AR $@"
	@$(AR) r $@ $(OBJS) 

clean:
	@rm -rf $(OBJS)
	@rm -rf $(DEPS)

dist-clean: clean
	@rm -rf $R/lib/$(TARGET_FOLDER_NAME)

# include existing dependency files
-include $(DEPS)

