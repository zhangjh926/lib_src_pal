#SUBDIRS = `find ./* -type d`
SUBDIRS = liblds_hal_gpio liblds_hal_key liblds_hal_led liblds_hal_adc liblds_hal_i2c liblds_hal_uart liblds_hal_rtc liblds_hal_wdt liblds_hal_gps liblds_hal_pwm liblds_hal_pir liblds_hal_ptz liblds_hal_spi liblds_hal_gyro

all:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
