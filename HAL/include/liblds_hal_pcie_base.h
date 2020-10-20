#ifndef _LDS_PCIE_OPERATION_H
#define _LDS_PCIE_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_PCIE_ErrorNo{
	LDS_PCIE_OPEN_ERROR,
	LDS_PCIE_INIT_ERROR,
	LDS_PCIE_START_ERROR,
}LDS_PCIE_ErrorNo;

typedef enum tagCTRL_PCIE
{
	LDS_CTRL_PCIE_END,
	LDS_CTRL_PCIE_SET_PARAM,
	LDS_CTRL_PCIE_SET_OUTPUT,
	LDS_CTRL_PCIE_MAX
}LDS_CTRL_PCIE;

struct LDS_PCIE_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    int     (*ioctl)(LDS_CTRL_PCIE, ...);
};

extern struct LDS_PCIE_OPERATION lds_hal_pcie;


#ifdef __cplusplus
}
#endif

#endif
