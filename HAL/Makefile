#SUBDIRS = `find ./* -type d`
SUBDIRS = liblds_hal_base liblds_hal_audio liblds_hal_video liblds_hal_cvbs liblds_hal_dsp liblds_hal_emmc liblds_hal_flash liblds_hal_fpga liblds_hal_gpu liblds_hal_hdmi liblds_hal_lvds liblds_hal_power liblds_hal_sdcard liblds_hal_lcd liblds_hal_net liblds_hal_usb

all:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
