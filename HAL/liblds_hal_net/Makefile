#SUBDIRS = `find ./* -type d`
SUBDIRS= liblds_hal_wifi liblds_hal_eth  liblds_hal_bluetooth liblds_hal_can liblds_hal_nfc liblds_hal_gsm

all:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
