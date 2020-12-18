#ifndef _LDS_GPU_OPERATION_H
#define _LDS_GPU_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_GPU_ErrorNo{
	LDS_GPU_OPEN_ERROR,
	LDS_GPU_INIT_ERROR,
	LDS_GPU_START_ERROR,
}LDS_GPU_ErrorNo;

typedef enum tagCTRL_GPU
{
	LDS_CTRL_GPU_END,
	LDS_CTRL_GPU_SET_PARAM,
	LDS_CTRL_GPU_SET_OUTPUT,
	LDS_CTRL_GPU_MAX
}LDS_CTRL_GPU;

typedef struct _LDS_GPU_CTX{
	char dev_name[128];
	int  dev_fd;
    LDS_GPU_ErrorNo curr_err_state;
}LDS_GPU_CTX;

struct LDS_GPU_OPERATION
{
    struct  LDS_HAL_COMMON base;    
	const   char		  *name;

    int     (*ioctl)(LDS_GPU_CTX *ctx, LDS_CTRL_GPU type, ...);
};

extern struct LDS_GPU_OPERATION lds_hal_gpu;


#ifdef __cplusplus
}
#endif

#endif