#ifndef _LDS_LVDS_OPERATION_H
#define _LDS_LVDS_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_LVDS_ErrorNo{
	LDS_LVDS_OPEN_ERROR,
	LDS_LVDS_INIT_ERROR,
	LDS_LVDS_START_ERROR,
}LDS_LVDS_ErrorNo;

typedef enum tagCTRL_LVDS
{
	LDS_CTRL_LVDS_END,
	LDS_CTRL_LVDS_SET_PARAM,
	LDS_CTRL_LVDS_SET_OUTPUT,
	LDS_CTRL_LVDS_MAX
}LDS_CTRL_LVDS;

typedef struct _LDS_LVDS_CTX{
	char dev_name[128];
	int  dev_fd;
    LDS_LVDS_ErrorNo curr_err_state;
}LDS_LVDS_CTX;


struct LDS_LVDS_OPERATION
{
    struct  LDS_HAL_COMMON base;    
	const   char		  *name;

    int     (*ioctl)(LDS_LVDS_CTX *ctx, LDS_CTRL_LVDS type, ...);
};

extern struct LDS_LVDS_OPERATION lds_hal_lvds;

#ifdef __cplusplus
}
#endif

#endif