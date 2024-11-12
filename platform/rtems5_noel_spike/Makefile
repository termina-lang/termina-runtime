

CROSS:=/opt/rtems-noel-1.0.4/bin/riscv-rtems5-

CC:=$(CROSS)gcc --pipe
AR:=$(CROSS)ar

MKDIR:=mkdir

TARGET_FOLDER_NAME:=rtems5_noel_spike

INCLUDE_DIRS+=$R/api
INCLUDE_DIRS+=$R/os/rtems5/include
INCLUDE_DIRS+=$R/platform/rtems5_noel_spike/include

CPPFLAGS:=-O0 -g3 -Wall --pipe -march=rv32im -mabi=ilp32 -B/opt/rtems-noel-1.0.4/kernel/riscv-rtems5/spike32im/lib/ -specs bsp_specs -qrtems -c
CPPFLAGS+=-I/opt/rtems-noel-1.0.4/kernel/riscv-rtems5/spike32im/lib/include 
CPPFLAGS+=$(patsubst %,-I %,$(INCLUDE_DIRS))

SRCS:=$(wildcard $R/common/*.c)
SRCS+=$(wildcard $R/os/rtems5/src/*.c)

OBJS:=$(patsubst %.c, %.o, $(patsubst $R/%, $R/lib/$(TARGET_FOLDER_NAME)/%, $(SRCS)))

# compilation targets
TARGET:=$R/lib/$(TARGET_FOLDER_NAME)/libtermina_rtems5_noel_spike.a

# dependency files
DEPS:=$(patsubst %.o,%.d,$(OBJS))

$R/lib/$(TARGET_FOLDER_NAME)/%.o: $R/%.c
	@echo " CC  $<"
	@$(MKDIR) -p $(@D)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c -o $@ $<

rtems5_noel_spike: $(TARGET)

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

