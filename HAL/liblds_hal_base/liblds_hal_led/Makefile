# Get Linux Build Enviornment:
include ../../../Platform.env

ifndef BUILD_VERBOSE
	BUILD_VERBOSE = 0
	Q = @
endif

export BUILD_VERBOSE Q

########################################################
ifndef PROJ_HOME

PROJ_HOME	= `pwd`
TOP		= 	$(OUTPUT_HAL_BASE_PREFIX)

CC		=	$(CROSS_TOOL)gcc
LD		=	$(CROSS_TOOL)ld
AR		=	$(CROSS_TOOL)ar cqs
STRIP	=	$(CROSS_TOOL)strip

CP		=	@cp -f
RM		=	@rm -f
LN		=	@ln -sf
ECHO	=	@echo
CTAG	=	@ctags -R


TARGET_DIR = $(TOP)/HAL/lib/

INCPATH   = -I./
INCPATH  += -I$(TOP)/HAL/include
INCPATH  += -I../../

endif
########################################################
########################################################
TARGET	=	liblds_hal_led

########################################################
#DEFINES += -DDEBUG

#####################################################################
# Is it a general module  #TRUE or FALSE
COMMON_MODULE := FALSE

########################################################

CFLAGS  += -pipe -O2 -fPIC $(INCPATH) $(DEFINES) -D$(SYSTEM) -D$(PLATFORM)
#CFLAGS  += -pipe -Wall $(INCPATH) $(DEFINES)
LFLAGS	+= $(LIBDIR) $(LIBS)

########################################################

$(warning $(SYSTEM) )
$(warning $(PLATFORM) )
##########    Files    ##########
ifeq ($(SYSTEM), LINUX)
		ifeq ($(PLATFORM)_$(COMMON_MODULE), AMBA_FALSE)
		OBJECTS +=	$(TOP)/../vendor/amba/linux/base/led/liblds_hal_led_amba.o
		else ifeq ($(PLATFORM)_$(COMMON_MODULE), REALTEK_FALSE)
		OBJECTS +=	$(TOP)/../vendor/realtek/linux/base/led/liblds_hal_led_amba.o
		else ifeq ($(PLATFORM)_$(COMMON_MODULE), SIGMASTAR_FALSE)
		OBJECTS +=	$(TOP)/../vendor/sigmastar/linux/base/led/liblds_hal_led_amba.o
		else
		OBJECTS +=	linux/liblds_hal_led_linux.o
		endif
else
OBJECTS +=	rtos/liblds_hal_led_rtos.o
endif
$(warning $(PLATFORM)_$(COMMON_MODULE))
$(warning $(OBJECTS) )
HEADERS	=	liblds_hal_led_base.h \
			

######### Implicit rules #########
.SUFFIXES: .cpp .cxx .cc .C .c

.c.o:
ifeq ($(BUILD_VERBOSE),0)
	$(ECHO)		"Compiling.....   [$<]"
endif
	$(Q)$(CC)	-c $(CFLAGS) -o $@ $<

########## Build rules ##########
all:    $(TARGET) install

$(TARGET) : $(OBJECTS)
ifeq ($(BUILD_VERBOSE),0)
	$(ECHO)		"Making........   [$@]"
endif
	$(Q)$(AR)	$(LFLAGS) $(TARGET).a $(OBJECTS)
	$(Q)$(CC) 	-shared -o $(TARGET).so $(OBJECTS)

install:	$(TARGET)
	#$(CP)		$(TARGET).a $(TARGET_DIR)
	$(STRIP)	$(TARGET).so
	$(CP)		$(TARGET).so $(TARGET_DIR)
	$(CP)		$(HEADERS) $(TOP)/HAL/include
	$(CP)		$(OBJECTS) $(TOP)/HAL/obj
	@echo 		"Install.......	[OK]"

clean:
	$(RM)		$(OBJECTS) $(TARGET) *~ tags *.so *.a *.dpend
	$(ECHO)		"Cleaning......   [OK]"

