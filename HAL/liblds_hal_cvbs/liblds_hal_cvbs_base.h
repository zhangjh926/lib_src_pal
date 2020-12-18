#ifndef _LDS_CVBS_OPERATION_H
#define _LDS_CVBS_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_CVBS_ErrorNo{
	LDS_CVBS_OPEN_ERROR,
	LDS_CVBS_INIT_ERROR,
	LDS_CVBS_START_ERROR,
}LDS_CVBS_ErrorNo;

typedef enum tagCTRL_CVBS
{
	LDS_CTRL_CVBS_END,
	LDS_CTRL_CVBS_SET_PARAM,
	LDS_CTRL_CVBS_SET_OUTPUT,
	LDS_CTRL_CVBS_MAX
}LDS_CTRL_CVBS;


typedef struct _LDS_CVBS_CTX{
	char dev_name[128];
	int  dev_fd;
    LDS_CVBS_ErrorNo curr_err_state;
}LDS_CVBS_CTX;

struct LDS_CVBS_OPERATION
{
    struct  LDS_HAL_COMMON base;    
	const   char		  *name;

    int     (*ioctl)(LDS_CVBS_CTX *ctx, LDS_CTRL_CVBS type, ...);
};

extern struct LDS_CVBS_OPERATION lds_hal_cvbs;


#ifdef __cplusplus
}
#endif

#endif

