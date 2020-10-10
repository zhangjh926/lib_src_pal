#SUBDIRS = `find ./* -type d`
SUBDIRS= liblds_hal_wifi liblds_hal_eth 

all:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
