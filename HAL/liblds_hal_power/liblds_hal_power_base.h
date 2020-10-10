#ifndef _LDS_POWER_OPERATION_H
#define _LDS_POWER_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef enum tagCTRL_POWER
{
	LDS_CTRL_POWER_END,
	LDS_CTRL_POWER_SET_PARAM,
	LDS_CTRL_POWER_SET_OUTPUT,
	LDS_CTRL_POWER_MAX
}LDS_CTRL_POWER;

struct LDS_POWER_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    int     (*ioctl)(LDS_CTRL_POWER, ...);
};

extern struct LDS_POWER_OPERATION lds_hal_power;

#ifdef __cplusplus
}
#endif

#endif