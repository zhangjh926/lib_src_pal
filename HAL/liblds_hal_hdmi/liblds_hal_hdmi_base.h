#ifndef _LDS_HDMI_OPERATION_H
#define _LDS_HDMI_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_HDMI_ErrorNo{
	LDS_HDMI_OPEN_ERROR,
	LDS_HDMI_INIT_ERROR,
	LDS_HDMI_START_ERROR,
}LDS_HDMI_ErrorNo;

typedef enum tagCTRL_HDMI
{
	LDS_CTRL_HDMI_END,
	LDS_CTRL_HDMI_SET_PARAM,
	LDS_CTRL_HDMI_SET_OUTPUT,
	LDS_CTRL_HDMI_MAX
}LDS_CTRL_HDMI;

typedef struct _LDS_HDMI_CTX{
	char dev_name[128];
	int  dev_fd;
    LDS_HDMI_ErrorNo curr_err_state;
}LDS_HDMI_CTX;


struct LDS_HDMI_OPERATION
{
    struct  LDS_HAL_COMMON base;    
	const   char		  *name;

    int     (*ioctl)(LDS_HDMI_CTX *ctx, LDS_CTRL_HDMI type, ...);
};

extern struct LDS_HDMI_OPERATION lds_hal_hdmi;


#ifdef __cplusplus
}
#endif

#endif