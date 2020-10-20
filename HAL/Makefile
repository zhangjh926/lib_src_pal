include ../Platform.env

#SUBDIRS = `find ./* -type d`
ifeq ($(liblds_hal_base), y)
SUBDIRS = 	liblds_hal_base
endif
ifeq ($(liblds_hal_audio), y)
SUBDIRS +=	liblds_hal_audio
endif
ifeq ($(liblds_hal_video), y)
SUBDIRS +=	liblds_hal_video
endif
ifeq ($(liblds_hal_cvbs), y) 
SUBDIRS +=	liblds_hal_cvbs
endif
ifeq ($(liblds_hal_dsp), y)
SUBDIRS +=	liblds_hal_dsp
endif
ifeq ($(liblds_hal_emmc), y)
SUBDIRS +=	liblds_hal_emmc
endif
ifeq ($(liblds_hal_flash), y)
SUBDIRS +=	liblds_hal_flash
endif 
ifeq ($(liblds_hal_fpga), y)
SUBDIRS +=	liblds_hal_fpga
endif
ifeq ($(liblds_hal_gpu), y)
SUBDIRS +=	liblds_hal_gpu
endif
ifeq ($(liblds_hal_hdmi), y)
SUBDIRS +=	liblds_hal_hdmi
endif
ifeq ($(liblds_hal_lvds), y)
SUBDIRS +=	liblds_hal_lvds
endif
ifeq ($(liblds_hal_power), y)
SUBDIRS +=	liblds_hal_power
endif
ifeq ($(liblds_hal_sdcard), y) 
SUBDIRS +=	liblds_hal_sdcard
endif
ifeq ($(liblds_hal_lcd), y)
SUBDIRS +=	liblds_hal_lcd
endif
ifeq ($(liblds_hal_net), y)
SUBDIRS +=	liblds_hal_net
endif
ifeq ($(liblds_hal_usb), y)
SUBDIRS +=	liblds_hal_usb
endif
ifeq ($(liblds_hal_pcie), y)
SUBDIRS +=	liblds_hal_pcie
endif

OBJS	:= obj/*.o

TARGET	:= lds_hal_interface

all:
	@mkdir -p obj
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done
	$(CC) -shared -o lib/$(TARGET).so $(OBJS)
	$(STRIP) lib/$(TARGET).so
	@rm -fr obj

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
	@rm -fr obj; rm -fr lib/* ; rm -fr include/*
