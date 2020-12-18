########################################################################
# Get Linux Build Enviornment:
include ../../../Platform.env

TOPDIR   	:= $(OUTPUT_HAL_BASE_PREFIX)

Q = @
export Q

LIBSDIR	 	:= $(TOPDIR)/
LIB_INSTALL	:= $(LIBSDIR)/HAL/lib
INC_INSTALL	:= $(LIBSDIR)/HAL/include
OBJ_INSTALL	:= $(LIBSDIR)/HAL/obj

# Build options
INCLUDE += -I./ -I../../ -I$(INC_INSTALL)

INCLUDE += -I../../../../../../../middleware/include/common

LIBRARY += -L$(LIB_INSTALL)

VIDEO_LIBRARY :=

PLATFORM_PATH := 

#####################################################################
# Is it a general module,#TRUE or FALSE
COMMON_MODULE := FALSE

######################################################################
# Target
$(warning $(SYSTEM) )
$(warning $(PLATFORM) )
##########    Files    ##########
ifeq ($(SYSTEM), LINUX)
	ifeq ($(COMMON_MODULE), FALSE)
		ifeq ($(PLATFORM), AMBA)
		COBJS  	+= $(TOPDIR)/../vendor/amba/linux/video/encode/liblds_hal_video_encode_amba.o
		INCLUDE += -I$(TOPDIR)/../vendor/amba/linux/platform/include/
		VIDEO_LIBRARY +=  $(TOPDIR)/../vendor/amba/linux/platform/lib/liblds_video_encode.a
		PLATFORM_PATH += $(TOPDIR)/../vendor/amba/linux/platform/
		else ifeq ($(PLATFORM), REALTEK)
		COBJS  	+= $(TOPDIR)/../vendor/realtek/linux/video/encode/liblds_hal_video_encode_realtek.o
		INCLUDE += -I$(TOPDIR)/../vendor/realtek/linux/platform/include/
		VIDEO_LIBRARY += $(TOPDIR)/../vendor/realtek/linux/platform/lib/liblds_video_encode.a
		PLATFORM_PATH += $(TOPDIR)/../vendor/realtek/linux/platform/
		else ifeq ($(PLATFORM), SIGMASTAR)
		COBJS  	+= $(TOPDIR)/../vendor/sigmastar/linux/video/encode/liblds_hal_video_encode_sigmastar.o
		INCLUDE += -I$(TOPDIR)/../vendor/sigmastar/linux/platform/include/
		VIDEO_LIBRARY += $(TOPDIR)/../vendor/sigmastar/linux/platform/lib/liblds_video_encode.a
		PLATFORM_PATH += $(TOPDIR)/../vendor/sigmastar/linux/platform/
		endif
	else
		COBJS  	+= linux/liblds_hal_video_encode_linux.o
	endif
else
COBJS  	+= linux/liblds_hal_video_encode_rtos.o
endif

$(warning $(INCLUDE))
$(warning $(LIBRARY))
$(warning $(COBJS))
CFLAGS	+= -g -O2 -fPIC $(INCLUDE) -D$(SYSTEM) -D$(PLATFORM)

TARGET	:= liblds_hal_video_encode
INC_FILE := liblds_hal_video_encode_base

######################################################################
# Build
OBJS	:= $(COBJS) $(CPPOBJS)

all: $(TARGET)

$(TARGET): depend $(OBJS)
	$(Q)$(AR) $(ARFLAGS) $(TARGET).a $(OBJS)
	$(Q)$(AR) -x $(VIDEO_LIBRARY)
	$(CC) $(LDFLAGS) -shared $(CFLAGS) $(LIBRARY) $(OBJS) *.o -o $@.so 
	install -m 755 -d $(LIB_INSTALL)
	#install -m 644 $(TARGET).a $(LIB_INSTALL)
	install -m 644 $(TARGET).so $(LIB_INSTALL)
	#install -m 644 $(PLATFORM_PATH)/lib/liblds_video_encode.so $(LIB_INSTALL)
	install -m 644 $(INC_FILE).h $(INC_INSTALL)
	install -m 644 $(COBJS) $(CPPOBJS) $(OBJ_INSTALL)

clean:
	rm -f linux/*.o rtos/*.o *.so *.a *.bak .depend *.o

distclean: clean
	rm -f $(LIB_INSTALL)/$(TARGET).a
	rm -f $(INC_INSTALL)/$(INC_FILE).h

#########################################################################
# Dependency
ifeq (.depend,$(wildcard .depend))
include .depend
endif

SRCS := $(COBJS:.o=.c) $(CPPOBJS:.o=.cpp) $(APPOBJS:.o=.c)
INCS := $(INCLUDE)
depend dep:
	$(CC)  -M  $(CFLAGS) $(INCS) $(SRCS) > .depend

