#ifndef _LDS_HDMI_OPERATION_H
#define _LDS_HDMI_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef enum tagCTRL_HDMI
{
	LDS_CTRL_HDMI_END,
	LDS_CTRL_HDMI_SET_PARAM,
	LDS_CTRL_HDMI_SET_OUTPUT,
	LDS_CTRL_HDMI_MAX
}LDS_CTRL_HDMI;

struct LDS_HDMI_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    int     (*ioctl)(LDS_CTRL_HDMI, ...);
};

extern struct LDS_HDMI_OPERATION lds_hal_hdmi;


#ifdef __cplusplus
}
#endif

#endif