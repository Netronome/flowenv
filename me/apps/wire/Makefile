SDKHOME ?= /opt/netronome

NFCC=$(SDKHOME)/bin/nfcc
NFLD=$(SDKHOME)/bin/nfld
STDLIB=$(SDKHOME)/components/standardlibrary
PICO_CODE=$(STDLIB)/picocode/nfp6000/null/null.npfw
MEBASE=../..


CFLAGS=				\
	-W3			\
	-Gx6000			\
	-Qspill=7		\
	-Qnctx_mode=8		\
	-single_dram_signal

LDFLAGS=			\
	-rtsyms			\
	-mip


INC=					\
	-I	.			\
	-I$(STDLIB)/microc/include	\
	-I$(MEBASE)/include		\
	-I$(MEBASE)/lib

DEFS=-DPKT_NBI_OFFSET=64


STDSRC=					\
	$(MEBASE)/lib/nfp/libnfp.c	\
	$(MEBASE)/lib/pkt/libpkt.c	\
	$(STDLIB)/microc/src/rtl.c


all: wire.nffw

wire0.list: wire.c
	$(NFCC) -Fewire0 $(CFLAGS) $(INC) $(DEFS) -DMY_NBI=0 wire.c $(STDSRC)

wire7.list: wire.c
	$(NFCC) -Fewire7 $(CFLAGS) $(INC) $(DEFS) -DMY_NBI=1 wire.c $(STDSRC)

wire.nffw: wire0.list wire7.list $(PICO_CODE)
	$(NFLD) -elf wire.nffw $(LDFLAGS)	\
		-u i32.me0 -l wire0.list	\
		-u i38.me0 -l wire7.list	\
		-i i8 -e $(PICO_CODE)		\
		-i i9 -e $(PICO_CODE)

clean:
	rm -f *.obj *.list *.nffw
