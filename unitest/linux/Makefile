########################################################################
# Get Linux Build Enviornment:
include ../../Platform.env

# Build options
INCLUDE += -I../../output/HAL/include
INCLUDE += -I../../HAL/
INCLUDE += -I../../output/SAL/include
INCLUDE += -I../../SAL/
INCLUDE += -I../../../../../../middleware/include/common
LIBRARY += -L../../output/HAL/lib
LIBRARY += -L../../output/SAL/lib

######################################################################
# Target
$(warning $(SYSTEM) )
$(warning $(PLATFORM) )

ifeq ($(PLATFORM), AMBA)
LIBRARY += -Wl,-rpath-link=../../$(SYSTEM_LIB_PATH)/ -L../../vendor/amba/linux/platform/lib/ -L../../$(SYSTEM_LIB_PATH)
LIBRARY += -L../../$(SYSTEM_LIB_PATH)/ -lfreetype
LIBRARY += -L../../$(SYSTEM_LIB_PATH)/ -lamp
LIBRARY += ../../$(SYSTEM_LIB_PATH)/libamdev.so
LIBRARY +=  -limg_aaa_flow_v5 -limg_algo_v5_dyn -llua -limg_dsp_v5_dyn 
else ifeq ($(PLATFORM), REALTEK)
LIBRARY += -L../../vendor/realtek/linux/platform/lib/
else ifeq ($(PLATFORM), SIGMASTAR)
LIBRARY += -L../../vendor/sigmastar/linux/platform/lib/
endif

CFLAGS	+= -Wall -O1 -Werror $(INCLUDE) -D$(SYSTEM) -D$(PLATFORM)
LIBS	+= $(LIBRARY) -llds_hal_video_encode -llds_hal_adc -llds_hal_gpio -lpthread

$(warning $(shell pwd))
######################################################################
# Build
PHONY: all

SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)
BIN=$(OBJ:%.o=%)
 

all:$(BIN)
 
$(BIN):%:%.o
	 $(CC) $(CFLAGS) $(LIBS) $^ -o $@
# $(OBJ):%.o:%.c
# 	$(CC) $(CFLAGS) $(LIBS) $^ -o $@
 
clean:
	@rm -f $(OBJ) $(BIN)


