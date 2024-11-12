.PHONY: rtems5_noel_spike rtems5_leon3_tsim clean dist-clean

export R:=$(shell pwd)

all: rtems5_noel_spike rtems5_leon3_tsim

rtems5_noel_spike:
	@make -f $R/platform/rtems5_noel_spike/Makefile

rtems5_leon3_tsim:
	@make -f $R/platform/rtems5_leon3_tsim/Makefile

clean:
	@make -f $R/platform/rtems5_noel_spike/Makefile clean
	@make -f $R/platform/rtems5_leon3_tsim/Makefile clean

dist-clean:
	@make -f $R/platform/rtems5_noel_spike/Makefile dist-clean
	@make -f $R/platform/rtems5_leon3_tsim/Makefile dist-clean
	@rm -rf $R/lib
