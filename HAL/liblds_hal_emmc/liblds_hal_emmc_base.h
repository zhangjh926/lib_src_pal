#ifndef _LDS_EMMC_OPERATION_H
#define _LDS_EMMC_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_EMMC_ErrorNo{
	LDS_EMMC_OPEN_ERROR,
	LDS_EMMC_INIT_ERROR,
	LDS_EMMC_START_ERROR,
}LDS_EMMC_ErrorNo;

typedef enum tagCTRL_EMMC
{
	LDS_CTRL_EMMC_END,
	LDS_CTRL_EMMC_SET_PARAM,
	LDS_CTRL_EMMC_SET_OUTPUT,
	LDS_CTRL_EMMC_MAX
}LDS_CTRL_EMMC;

typedef struct _LDS_EMMC_CTX{
	char dev_name[128];
	int  dev_fd;
    LDS_EMMC_ErrorNo curr_err_state;
}LDS_EMMC_CTX;

struct LDS_EMMC_OPERATION
{
    struct  LDS_HAL_COMMON base;
	const   char		  *name;

    int     (*ioctl)(LDS_EMMC_CTX *ctx, LDS_CTRL_EMMC type, ...);
};

extern struct LDS_EMMC_OPERATION lds_hal_emmc;


#ifdef __cplusplus
}
#endif

#endif