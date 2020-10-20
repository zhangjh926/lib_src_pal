#ifndef _LDS_DSP_OPERATION_H
#define _LDS_DSP_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_DSP_ErrorNo{
	LDS_DSP_OPEN_ERROR,
	LDS_DSP_INIT_ERROR,
	LDS_DSP_START_ERROR,
}LDS_DSP_ErrorNo;

typedef enum tagCTRL_DSP
{
	LDS_CTRL_DSP_END,
	LDS_CTRL_DSP_SET_PARAM,
	LDS_CTRL_DSP_SET_OUTPUT,
	LDS_CTRL_DSP_MAX
}LDS_CTRL_DSP;

struct LDS_DSP_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    int     (*ioctl)(LDS_CTRL_DSP, ...);
};

extern struct LDS_DSP_OPERATION lds_hal_dsp;


#ifdef __cplusplus
}
#endif

#endif