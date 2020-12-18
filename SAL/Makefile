#SUBDIRS = `find ./* -type d`
SUBDIRS = liblds_sal_file 

all:
	@mkdir -p ../output/SAL/obj
	@mkdir -p ../output/SAL/lib
	@mkdir -p ../output/SAL/include
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
	@rm -fr ../output/
