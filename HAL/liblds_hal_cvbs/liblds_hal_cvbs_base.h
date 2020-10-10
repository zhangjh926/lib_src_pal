#ifndef _LDS_CVBS_OPERATION_H
#define _LDS_CVBS_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef enum tagCTRL_CVBS
{
	LDS_CTRL_CVBS_END,
	LDS_CTRL_CVBS_SET_PARAM,
	LDS_CTRL_CVBS_SET_OUTPUT,
	LDS_CTRL_CVBS_MAX
}LDS_CTRL_CVBS;

struct LDS_CVBS_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    int     (*ioctl)(LDS_CTRL_CVBS, ...);
};

extern struct LDS_CVBS_OPERATION lds_hal_cvbs;


#ifdef __cplusplus
}
#endif

#endif

