#ifndef _LDS_ETH_OPERATION_H
#define _LDS_ETH_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef enum tagCTRL_ETH
{
	LDS_CTRL_ETH_END,
	LDS_CTRL_ETH_SET_PARAM,
	LDS_CTRL_ETH_SET_OUTPUT,
	LDS_CTRL_ETH_MAX
}LDS_CTRL_ETH;

struct LDS_ETH_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    int     (*ioctl)(LDS_CTRL_ETH, ...);
};

extern struct LDS_ETH_OPERATION lds_hal_eth;

#ifdef __cplusplus
}
#endif

#endif