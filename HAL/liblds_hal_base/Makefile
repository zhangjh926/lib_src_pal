include ../../Platform.env

#SUBDIRS = `find ./* -type d`
ifeq ($(liblds_hal_gpio), y)
SUBDIRS := 	liblds_hal_gpio
endif
ifeq ($(liblds_hal_key), y)
SUBDIRS += 	liblds_hal_key
endif
ifeq ($(liblds_hal_led), y)
SUBDIRS += 	liblds_hal_led
endif
ifeq ($(liblds_hal_adc), y)
SUBDIRS += 	liblds_hal_adc
endif
ifeq ($(liblds_hal_i2c), y)
SUBDIRS += 	liblds_hal_i2c
endif
ifeq ($(liblds_hal_uart), y)
SUBDIRS += 	liblds_hal_uart
endif
ifeq ($(liblds_hal_rtc), y)
SUBDIRS += 	liblds_hal_rtc
endif
ifeq ($(liblds_hal_wdt), y)
SUBDIRS += 	liblds_hal_wdt
endif
ifeq ($(liblds_hal_gps), y)
SUBDIRS += 	liblds_hal_gps
endif
ifeq ($(liblds_hal_pwm), y)
SUBDIRS += 	liblds_hal_pwm
endif
ifeq ($(liblds_hal_pir), y)
SUBDIRS += 	liblds_hal_pir
endif
ifeq ($(liblds_hal_ptz), y)
SUBDIRS += 	liblds_hal_ptz
endif
ifeq ($(liblds_hal_spi), y)
SUBDIRS += 	liblds_hal_spi
endif
ifeq ($(liblds_hal_gyro), y)
SUBDIRS += 	liblds_hal_gyro
endif

all:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
