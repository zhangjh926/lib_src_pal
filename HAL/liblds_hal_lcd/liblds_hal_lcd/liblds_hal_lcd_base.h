#ifndef _LDS_LCD_OPERATION_H
#define _LDS_LCD_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_LCD_ErrorNo{
	LDS_LCD_OPEN_ERROR,
	LDS_LCD_INIT_ERROR,
	LDS_LCD_START_ERROR,
}LDS_LCD_ErrorNo;

typedef enum tagCTRL_LCD
{
	LDS_CTRL_LCD_END,
	LDS_CTRL_LCD_SET_PARAM,
	LDS_CTRL_LCD_SET_OUTPUT,
	LDS_CTRL_LCD_MAX
}LDS_CTRL_LCD;

typedef struct _LDS_LCD_CTX{
	char dev_name[128];
	int  dev_fd;
    LDS_LCD_ErrorNo curr_err_state;
}LDS_LCD_CTX;

struct LDS_LCD_OPERATION
{
    struct  LDS_HAL_COMMON base;    
	const   char		  *name;

    int     (*ioctl)(LDS_LCD_CTX *ctx, LDS_CTRL_LCD type, ...);
};

extern struct LDS_LCD_OPERATION lds_hal_lcd;

#ifdef __cplusplus
}
#endif

#endif