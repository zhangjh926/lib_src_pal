#ifndef _LDS_EMMC_OPERATION_H
#define _LDS_EMMC_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef enum tagCTRL_EMMC
{
	LDS_CTRL_EMMC_END,
	LDS_CTRL_EMMC_SET_PARAM,
	LDS_CTRL_EMMC_SET_OUTPUT,
	LDS_CTRL_EMMC_MAX
}LDS_CTRL_EMMC;

struct LDS_EMMC_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    int     (*ioctl)(LDS_CTRL_EMMC, ...);
};

extern struct LDS_EMMC_OPERATION lds_hal_emmc;


#ifdef __cplusplus
}
#endif

#endif