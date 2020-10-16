#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_hdmi_base.h"

/* Define  -------------------------------------------------------------------*/
struct LDS_HDMI_CTX{
    LDS_HDMI_ErrorNo curr_err_state;
};

/* Define variable  ----------------------------------------------------------*/
static struct LDS_HDMI_CTX ctx;
/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_hdmi_open(char *dev_name)
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
static int lds_hal_hdmi_close(int dev_fd)
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
static int lds_hal_hdmi_init(void *param)
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
static int lds_hal_hdmi_deinit(void)
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
static int lds_hal_hdmi_start(void)
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
static int lds_hal_hdmi_stop(void)
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
static int lds_hal_hdmi_get_error(void)
{
    return ctx.curr_err_state;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_hdmi_ioctl(LDS_CTRL_HDMI type, ...)
{
	switch(type)
	{
		default:
			break;
	}
	
	return 0;
}


struct LDS_HDMI_OPERATION lds_hal_hdmi = {
    .name                   = "lds_hal_hdmi",
    .comm.lds_hal_open      = lds_hal_hdmi_open,
    .comm.lds_hal_close     = lds_hal_hdmi_close,
    .comm.lds_hal_start     = lds_hal_hdmi_start,
    .comm.lds_hal_stop      = lds_hal_hdmi_stop,
    .comm.lds_hal_init      = lds_hal_hdmi_init,
    .comm.lds_hal_deinit    = lds_hal_hdmi_deinit,
    .comm.lds_hal_get_error = lds_hal_hdmi_get_error,
    .ioctl                  = lds_hal_hdmi_ioctl,
};