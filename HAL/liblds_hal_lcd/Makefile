#SUBDIRS = `find ./* -type d`
SUBDIRS= liblds_hal_lcd liblds_hal_touch

all:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
