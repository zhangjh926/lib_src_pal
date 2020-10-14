# Get Linux Build Enviornment:
include ../../Platform.env
ifndef BUILD_VERBOSE
	BUILD_VERBOSE = 0
	Q = @
endif

export BUILD_VERBOSE Q

########################################################
ifndef PROJ_HOME

PROJ_HOME	= `pwd`
TOP			= ../

CC		=	$(CROSS_TOOL)gcc
LD		=	$(CROSS_TOOL)ld
AR		=	$(CROSS_TOOL)ar cqs
STRIP		=	$(CROSS_TOOL)strip

CP		=	@cp -f
RM		=	@rm -f
LN		=	@ln -sf
ECHO	=	@echo
CTAG	=	@ctags -R


TARGET_DIR = $(TOP)/lib/

INCPATH   = -I./
INCPATH  += -I$(TOP)/include

endif
########################################################

########################################################
TARGET	=	liblds_sal_file.a

########################################################
#DEFINES += -DDEBUG

########################################################

CFLAGS  += -pipe -O2 $(INCPATH) $(DEFINES)
#CFLAGS  += -pipe -Wall $(INCPATH) $(DEFINES)
LFLAGS	+= $(LIBDIR) $(LIBS)

########################################################

$(warning $(SYSTEM) )
$(warning $(PLATFORM) )
##########    Files    ##########
ifeq ($(SYSTEM), LINUX)
OBJECTS =	linux/liblds_sal_file_linux.o 
else
OBJECTS =	rtos/liblds_sal_file_rtos.o
endif

HEADERS	=	liblds_sal_file_base.h		

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
	$(Q)$(AR)	$(LFLAGS) $(TARGET) $(OBJECTS)

install:	$(TARGET)
	$(CP)		$(TARGET) $(TARGET_DIR)
	$(CP)		$(HEADERS) $(TOP)/include
	@echo 		"Install.......	[OK]"

clean:
	$(RM)		$(OBJECTS) $(TARGET) *~ tags *.so *.a *.dpend
	$(ECHO)		"Cleaning......   [OK]"

