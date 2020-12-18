#ifndef _LDS_POWER_OPERATION_H
#define _LDS_POWER_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_POWER_ErrorNo{
	LDS_POWER_OPEN_ERROR,
	LDS_POWER_INIT_ERROR,
	LDS_POWER_START_ERROR,
}LDS_POWER_ErrorNo;

typedef enum tagCTRL_POWER
{
	LDS_CTRL_POWER_END,
	LDS_CTRL_POWER_SET_PARAM,
	LDS_CTRL_POWER_SET_OUTPUT,
	LDS_CTRL_POWER_MAX
}LDS_CTRL_POWER;

typedef struct _LDS_POWER_CTX{
	char dev_name[128];
	int  dev_fd;
	LDS_POWER_ErrorNo curr_err_state;
}LDS_POWER_CTX;

struct LDS_POWER_OPERATION
{
    struct  LDS_HAL_COMMON base;    
	const   char		  *name;

    int     (*ioctl)(LDS_POWER_CTX *ctx, LDS_CTRL_POWER type, ...);
};

extern struct LDS_POWER_OPERATION lds_hal_power;

#ifdef __cplusplus
}
#endif

#endif