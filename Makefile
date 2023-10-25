.PHONY: rtems_noel_spike

export R:=$(shell pwd)

all: rtems_noel_spike

rtems_noel_spike:
	@make -f $R/platform/rtems_noel_spike/Makefile

clean:
	@make -f $R/platform/rtems_noel_spike/Makefile clean

dist-clean:
	@make -f $R/platform/rtems_noel_spike/Makefile dist-clean
	@rm -rf $R/lib
