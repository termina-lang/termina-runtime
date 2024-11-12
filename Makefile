.PHONY: rtems5_noel_spike clean dist-clean

export R:=$(shell pwd)

all: rtems5_noel_spike

rtems5_noel_spike:
	@make -f $R/platform/rtems5_noel_spike/Makefile

clean:
	@make -f $R/platform/rtems5_noel_spike/Makefile clean

dist-clean:
	@make -f $R/platform/rtems5_noel_spike/Makefile dist-clean
	@rm -rf $R/lib
