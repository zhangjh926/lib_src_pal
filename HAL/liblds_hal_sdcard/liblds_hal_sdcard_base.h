#ifndef _LDS_SDCARD_OPERATION_H
#define _LDS_SDCARD_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef enum tagCTRL_SDCARD
{
	LDS_CTRL_SDCARD_END,
	LDS_CTRL_SDCARD_SET_PARAM,
	LDS_CTRL_SDCARD_SET_OUTPUT,
	LDS_CTRL_SDCARD_MAX
}LDS_CTRL_SDCARD;

struct LDS_SDCARD_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    int     (*ioctl)(LDS_CTRL_SDCARD, ...);
};

extern struct LDS_SDCARD_OPERATION lds_hal_sdcard;


#ifdef __cplusplus
}
#endif

#endif

