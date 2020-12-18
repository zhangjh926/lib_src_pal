#SUBDIRS = `find ./* -type d`
#SUBDIRS= liblds_hal_wifi liblds_hal_eth  liblds_hal_bluetooth liblds_hal_can liblds_hal_nfc liblds_hal_gsm
include ../../Platform.env

ifeq ($(liblds_hal_wifi), y)
SUBDIRS = liblds_hal_wifi
endif

ifeq ($(liblds_hal_eth), y)
SUBDIRS += liblds_hal_eth
endif

ifeq ($(liblds_hal_bluetooth), y)
SUBDIRS += liblds_hal_bluetooth
endif

ifeq ($(liblds_hal_can), y)
SUBDIRS += liblds_hal_can
endif

ifeq ($(liblds_hal_nfc), y)
SUBDIRS += liblds_hal_nfc
endif

ifeq ($(liblds_hal_gsm), y)
SUBDIRS += liblds_hal_gsm
endif

all:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
