#ifndef __IO_LDS_GPIO_H__
#define __IO_LDS_GPIO_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif

enum LDS_GPIO {
	GPIO_ERROR = -1,

	// GPIOA0 - GPIOA31 ( 0 - 31 )
	GPIO0,	GPIO1,  GPIO2,  GPIO3,  GPIO4,  GPIO5,  GPIO6,  GPIO7,
	GPIO8,  GPIO9,  GPIO10, GPIO11, GPIO12, GPIO13, GPIO14, GPIO15,
	GPIO16, GPIO17, GPIO18, GPIO19, GPIO20, GPIO21, GPIO22, GPIO23,
	GPIO24, GPIO25, GPIO26, GPIO27, GPIO28, GPIO29, GPIO30, GPIO31,

	// GPIOB0 - GPIOB31 ( 32 - 63 )
	GPIO32,	 GPIO33,  GPIO34,  GPIO35,  GPIO36,  GPIO37,  GPIO38,  GPIO39,
	GPIO40,  GPIO41,  GPIO42,  GPIO43,  GPIO44,  GPIO45,  GPIO46,  GPIO47,
	GPIO48,  GPIO49,  GPIO50,  GPIO51,  GPIO52,  GPIO53,  GPIO54,  GPIO55,
	GPIO56,  GPIO57,  GPIO58,  GPIO59,  GPIO60,  GPIO61,  GPIO62,  GPIO63,

	// GPIOC0 - GPIOC31 ( 64 - 95 )
	GPIO64,	 GPIO65,  GPIO66,  GPIO67,  GPIO68,  GPIO69,  GPIO70,  GPIO71,
	GPIO72,  GPIO73,  GPIO74,  GPIO75,  GPIO76,  GPIO77,  GPIO78,  GPIO79,
	GPIO80,  GPIO81,  GPIO82,  GPIO83,  GPIO84,  GPIO85,  GPIO86,  GPIO87,
	GPIO88,  GPIO89,  GPIO90,  GPIO91,  GPIO92,  GPIO93,  GPIO94,  GPIO95,

	// GPIOD0 - GPIOD31 ( 96 - 127 )
	GPIO96,	 GPIO97,  GPIO98,  GPIO99,  GPIO100, GPIO101, GPIO102, GPIO103,
	GPIO104, GPIO105, GPIO106, GPIO107, GPIO108, GPIO109, GPIO110, GPIO111,
	GPIO112, GPIO113, GPIO114, GPIO115, GPIO116, GPIO117, GPIO118, GPIO119,
	GPIO120, GPIO121, GPIO122, GPIO123, GPIO124, GPIO125, GPIO126, GPIO127,

	// GPIOE0 - GPIOE31 ( 128 - 159 )
	GPIO128, GPIO129, GPIO130, GPIO131, GPIO132, GPIO133, GPIO134, GPIO135,
	GPIO136, GPIO137, GPIO138, GPIO139, GPIO140, GPIO141, GPIO142, GPIO143,
	GPIO144, GPIO145, GPIO146, GPIO147, GPIO148, GPIO149, GPIO150, GPIO151,
	GPIO152, GPIO153, GPIO154, GPIO155, GPIO156, GPIO157, GPIO158, GPIO159,

	GPIO_MAX,
};

typedef enum   _LDS_GPIO_ErrorNo{
	LDS_GPIO_OPEN_ERROR,
	LDS_GPIO_INIT_ERROR,
	LDS_GPIO_START_ERROR,
}LDS_GPIO_ErrorNo;

typedef enum tagGPIO_DIRECTION
{
	LDS_GPIO_DIRECTION_IN = 0,
	LDS_GPIO_DIRECTION_OUT,
}LDS_GPIO_DIRECTION;

typedef enum tagGPIO_STATUS
{
	LDS_GPIO_STATUS_LOW = 0,
	LDS_GPIO_STATUS_HIGH,
}LDS_GPIO_STATUS;

typedef enum tagCTRL_GPIO
{
	LDS_CTRL_GPIO_END,
	LDS_CTRL_GPIO_SET_PIN,
	LDS_CTRL_GPIO_DIRECTION,
	LDS_CTRL_GPIO_GET_VALUE,
	LDS_CTRL_GPIO_SET_VALUE,
	LDS_CTRL_GPIO_TOGLE,
	LDS_CTRL_GPIO_MAX
}LDS_CTRL_GPIO;

struct LDS_GPIO_OPERATION
{
    struct 			LDS_HAL_COMMON 	comm;
	const 			char			*name;
	int				ctxsize;
	int				maxctrl;

	int				(*ioctl)    (LDS_CTRL_GPIO type, ...);
};

extern struct LDS_GPIO_OPERATION lds_hal_gpio;

#ifdef __cplusplus
}
#endif

#endif
