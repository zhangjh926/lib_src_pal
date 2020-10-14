#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_usb_uvc_base.h"

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/

/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_usb_uvc_open(char *dev_name)
{
    return 0;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_usb_uvc_close(int dev_fd)
{
    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_usb_uvc_init(void *param)
{
    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_usb_uvc_deinit(void)
{
    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_usb_uvc_start(void)
{
    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_usb_uvc_stop(void)
{
    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_usb_uvc_ioctl(LDS_CTRL_USB_UVC type, ...)
{
	switch(type)
	{
		default:
			break;
	}
	
	return 0;
}


struct LDS_USB_UVC_OPERATION lds_hal_usb_uvc = {
    .name               = "lds_hal_usb_uvc",
    .comm.lds_hal_open  = lds_hal_usb_uvc_open,
    .comm.lds_hal_close = lds_hal_usb_uvc_close,
    .comm.lds_hal_start = lds_hal_usb_uvc_start,
    .comm.lds_hal_stop  = lds_hal_usb_uvc_stop,
    .comm.lds_hal_init  = lds_hal_usb_uvc_init,
    .comm.lds_hal_deinit= lds_hal_usb_uvc_deinit,
    .ioctl              = lds_hal_usb_uvc_ioctl,
};