#ifndef __IO_LDS_LED_H__
#define __IO_LDS_LED_H__

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Header file include --------------------------------------------------*/

/* Define  --------------------------------------------------------------*/
typedef enum tagLED_CTRL
{
	LDS_CTRL_LED_END,
	LDS_CTRL_LED_ACTIVELOW_SET,
	LDS_CTRL_LED_ON,
	LDS_CTRL_LED_OFF,
	LDS_CTRL_LED_SET_BLINK_TIME,
	LDS_CTRL_LED_BLINK,
	LDS_CTRL_LED_MAX
}LDS_CTRL_LED;

struct LDS_LED_OPERATION
{
    struct LDS_HAL_COMMON comm;
	const char		*name;
	int				ctxsize;
	int				maxctrl;

	/* common function */
	int				(*ioctl)			(LDS_CTRL_LED type, ...);
};

extern struct LDS_LED_OPERATION lds_hal_led;

#ifdef __cplusplus
}
#endif

#endif 

