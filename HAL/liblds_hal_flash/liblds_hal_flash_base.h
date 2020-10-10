#ifndef _LDS_FLASH_OPERATION_H
#define _LDS_FLASH_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef enum tagCTRL_FLASH
{
	LDS_CTRL_FLASH_END,
	LDS_CTRL_FLASH_SET_PARAM,
	LDS_CTRL_FLASH_SET_OUTPUT,
	LDS_CTRL_FLASH_MAX
}LDS_CTRL_FLASH;

struct LDS_FLASH_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    int     (*ioctl)(LDS_CTRL_FLASH, ...);
};

extern struct LDS_FLASH_OPERATION lds_hal_flash;


#ifdef __cplusplus
}
#endif

#endif