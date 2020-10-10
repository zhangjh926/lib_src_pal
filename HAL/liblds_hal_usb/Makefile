#SUBDIRS = `find ./* -type d`
SUBDIRS= liblds_hal_usb_device liblds_hal_usb_uvc

all:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
