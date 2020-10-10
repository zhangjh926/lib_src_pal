#ifndef _LDS_FPGA_OPERATION_H
#define _LDS_FPGA_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef enum tagCTRL_FPGA
{
	LDS_CTRL_FPGA_END,
	LDS_CTRL_FPGA_SET_PARAM,
	LDS_CTRL_FPGA_SET_OUTPUT,
	LDS_CTRL_FPGA_MAX
}LDS_CTRL_FPGA;

struct LDS_FPGA_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    int     (*ioctl)(LDS_CTRL_FPGA, ...);
};

extern struct LDS_FPGA_OPERATION lds_hal_fpga;


#ifdef __cplusplus
}
#endif

#endif