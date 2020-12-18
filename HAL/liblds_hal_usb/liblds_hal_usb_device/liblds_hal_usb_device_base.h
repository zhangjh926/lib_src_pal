#ifndef _LDS_USB_DEVICE_OPERATION_H
#define _LDS_USB_DEVICE_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_USB_DEVICE_ErrorNo{
	LDS_USB_DEVICE_OPEN_ERROR,
	LDS_USB_DEVICE_INIT_ERROR,
	LDS_USB_DEVICE_START_ERROR,
}LDS_USB_DEVICE_ErrorNo;

typedef enum tagCTRL_USB_DEVICE
{
	LDS_CTRL_USB_DEVICE_END,
	LDS_CTRL_USB_DEVICE_PARAM,
	LDS_CTRL_USB_DEVICE_SET_OUTPUT,
	LDS_CTRL_USB_DEVICE_MAX
}LDS_CTRL_USB_DEVICE;

typedef struct _LDS_USB_DEVICE_CTX{
	char dev_name[128];
	int  dev_fd;
    LDS_USB_DEVICE_ErrorNo curr_err_state;
}LDS_USB_DEVICE_CTX;

struct LDS_USB_DEVICE_OPERATION
{
    struct  LDS_HAL_COMMON base;
	const   char		   *name;

    int     (*ioctl)(LDS_USB_DEVICE_CTX *ctx, LDS_CTRL_USB_DEVICE, ...);
};

extern struct LDS_USB_DEVICE_OPERATION lds_hal_usb_device;

#ifdef __cplusplus
}
#endif

#endif