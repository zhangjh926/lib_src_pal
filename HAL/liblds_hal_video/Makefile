#SUBDIRS = `find ./* -type d`
SUBDIRS= liblds_hal_video_encode liblds_hal_video_decode

all:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
