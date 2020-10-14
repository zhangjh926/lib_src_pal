#ifndef _LDS_TOUCH_OPERATION_H
#define _LDS_TOUCH_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_TOUCH_ErrorNo{
	LDS_TOUCH_OPEN_ERROR,
	LDS_TOUCH_INIT_ERROR,
	LDS_TOUCH_START_ERROR,
}LDS_TOUCH_ErrorNo;

typedef enum tagCTRL_TOUCH
{
	LDS_CTRL_TOUCH_END,
	LDS_CTRL_TOUCH_SET_PARAM,
	LDS_CTRL_TOUCH_SET_OUTPUT,
	LDS_CTRL_TOUCH_MAX
}LDS_CTRL_TOUCH;

struct LDS_TOUCH_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    int     (*ioctl)(LDS_CTRL_TOUCH, ...);
};

extern struct LDS_TOUCH_OPERATION lds_hal_touch;

#ifdef __cplusplus
}
#endif

#endif