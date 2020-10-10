#ifndef _LDS_WIFI_OPERATION_H
#define _LDS_WIFI_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef enum tagCTRL_WIFI
{
	LDS_CTRL_WIFI_END,
	LDS_CTRL_WIFI_SET_PARAM,
	LDS_CTRL_WIFI_SET_OUTPUT,
	LDS_CTRL_WIFI_MAX
}LDS_CTRL_WIFI;

struct LDS_WIFI_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    int     (*ioctl)(LDS_CTRL_WIFI, ...);
};

extern struct LDS_WIFI_OPERATION lds_hal_wifi;

#ifdef __cplusplus
}
#endif

#endif