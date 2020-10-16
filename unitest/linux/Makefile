########################################################################
# Get Linux Build Enviornment:
include ../../Platform.env

# Build options
INCLUDE += -I../../HAL/include
INCLUDE += -I../../HAL/
INCLUDE += -I../../SAL/include
INCLUDE += -I../../SAL/
LIBRARY += -L../../HAL/lib
LIBRARY += -L../../SAL/lib

######################################################################
# Target
$(warning $(SYSTEM) )
$(warning $(PLATFORM) )

CFLAGS	+= -Wall -g -c $(INCLUDE) -D$(SYSTEM) -D$(PLATFORM)
LIBS	+= $(LIBRARY)/lds_hal_interface.so

######################################################################
# Build
PHONY: all

SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)
BIN=$(OBJ:%.o=%)
 

all:$(BIN)
 
$(BIN):%:%.o
	 $(CC) $^ -o $@
$(OBJ):%.o:%.c
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@
 
clean:
	@rm -f $(OBJ) $(BIN)


