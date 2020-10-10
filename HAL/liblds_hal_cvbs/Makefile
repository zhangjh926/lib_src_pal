########################################################################
# Get Linux Build Enviornment:
include ../../Platform.env

TOPDIR   	:= ../../../

Q = @
export Q

LIBSDIR	 	:= $(TOPDIR)/
LIB_INSTALL	:= $(LIBSDIR)/lib
INC_INSTALL	:= $(LIBSDIR)/include

# Build options
INCLUDE += -I./ -I../../include
INCLUDE += -I../
INCLUDE += -I../../

LIBRARY += -L../../../lib

######################################################################
# Target
$(warning $(SYSTEM) )
$(warning $(PLATFORM) )
##########    Files    ##########
ifeq ($(SYSTEM), LINUX)
COBJS  	:= 
COBJS  	+= linux/liblds_hal_cvbs_linux.o
CPPOBJS	:=  
else
COBJS  	:= 
COBJS  	+= linux/liblds_hal_cvbs_rtos.o
CPPOBJS	:=
endif

CFLAGS	+= -g -O2 -fpic $(INCLUDE) -D$(SYSTEM) -D$(PLATFORM)

TARGET	:= liblds_hal_cvbs
INC_FILE := liblds_hal_cvbs_base

######################################################################
# Build
OBJS	:= $(COBJS) $(CPPOBJS)

all: $(TARGET)

$(TARGET): depend $(OBJS)
	$(Q)$(AR) $(ARFLAGS) $(TARGET).a $(OBJS)
	$(Q)$(CC) -shared -o $(TARGET).so $(OBJS)
	install -m 755 -d $(LIB_INSTALL)
	install -m 644 $(TARGET).a $(LIB_INSTALL)
	install -m 644 $(TARGET).so $(LIB_INSTALL)
	install -m 644 $(INC_FILE).h $(INC_INSTALL)

clean:
	rm -f *.o *.so *.a *.bak .depend

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
	$(Q)$(CC)  -M  $(CFLAGS)   $(INCS) $(SRCS) > .depend

