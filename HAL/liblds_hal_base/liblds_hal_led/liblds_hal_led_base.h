#ifndef __IO_LDS_LED_H__
#define __IO_LDS_LED_H__

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Header file include --------------------------------------------------*/
typedef enum   _LDS_LED_ErrorNo{
	LDS_LED_OPEN_ERROR,
	LDS_LED_INIT_ERROR,
	LDS_LED_START_ERROR,
}LDS_LED_ErrorNo;

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

typedef struct _LDS_LED_CTX
{
	int				blink_time;
	LDS_CTRL_LED	curr_err_state;
}LDS_LED_CTX;


struct LDS_LED_OPERATION
{
    struct LDS_HAL_COMMON base;
	const char		*name;

	/* common function */
	int				(*ioctl)			(LDS_LED_CTX *ctx, LDS_CTRL_LED type, ...);
};

extern struct LDS_LED_OPERATION lds_hal_led;

#ifdef __cplusplus
}
#endif

#endif 

