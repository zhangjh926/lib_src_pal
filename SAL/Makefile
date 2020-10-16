#SUBDIRS = `find ./* -type d`
SUBDIRS = liblds_sal_file 

all:
	@mkdir -p obj
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done
	@rm -fr obj

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
	@rm -fr obj; rm -fr lib/* ; rm -fr include/*
