C=gcc
CC=g++

NETRONOME_INST_DIR?=/opt/netronome
BSP_RELEASE_INCLUDE?=$(NETRONOME_INST_DIR)/include
BSP_RELEASE_LIB?=$(NETRONOME_INST_DIR)/lib

CFLAGS=-c -Wall -Werror -lstring

FLOWENV_LIBS=../libs/flowenv

INC=-I$(FLOWENV_LIBS) \
	-I$(BSP_RELEASE_INCLUDE)

LIB=-L/usr/local/lib \
    -L/usr/lib/x86_64-linux-gnu/ \
    -L/lib/x86_64-linux-gnu/ \
    -L$(FLOWENV_LIBS) \
	-L$(BSP_RELEASE_LIB)

SRC= $(FLOWENV_LIBS)/nfp_cntrs.c \
	nfp_cntrs.c

OBJ=$(SRC:.c=.o)

all: clean nfp_cntrs

nfp_cntrs: $(OBJ)
	$(C) $(OBJ) $(LIB) -lnfp -lnfp_nffw -o $@

%.o: %.c
	$(C) $(CFLAGS) $(INC) $(LIB) $< -o $@

clean:
	rm -rf *.o nfp_cntrs $(FLOWENV_LIBS)/*.o
