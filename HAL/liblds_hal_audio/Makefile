#SUBDIRS = `find ./* -type d`
SUBDIRS= liblds_hal_audio_mic liblds_hal_audio_speaker

all:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
