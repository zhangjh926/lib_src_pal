#ifndef _LDS_USB_UVC_OPERATION_H
#define _LDS_USB_UVC_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_USB_UVC_ErrorNo{
	LDS_USB_UVC_OPEN_ERROR,
	LDS_USB_UVC_INIT_ERROR,
	LDS_USB_UVC_START_ERROR,
}LDS_USB_UVC_ErrorNo;

typedef enum tagCTRL_USB_UVC
{
	LDS_CTRL_USB_UVC_END,
	LDS_CTRL_USB_UVC_PARAM,
	LDS_CTRL_USB_UVC_SET_OUTPUT,
	LDS_CTRL_USB_UVC_MAX
}LDS_CTRL_USB_UVC;

typedef struct _LDS_USB_UVC_CTX{
	char dev_name[128];
	int  dev_fd;
    LDS_USB_UVC_ErrorNo curr_err_state;
}LDS_USB_UVC_CTX;


struct LDS_USB_UVC_OPERATION
{
    struct  LDS_HAL_COMMON base;
	const   char		  *name;

    int     (*ioctl)(LDS_USB_UVC_CTX *ctx, LDS_CTRL_USB_UVC, ...);
};

extern struct LDS_USB_UVC_OPERATION lds_hal_usb_uvc;

#ifdef __cplusplus
}
#endif

#endif