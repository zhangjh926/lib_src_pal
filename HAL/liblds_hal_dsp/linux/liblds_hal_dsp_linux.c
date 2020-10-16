#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_dsp_base.h"

/* Define  -------------------------------------------------------------------*/
struct LDS_DSP_CTX{
    LDS_DSP_ErrorNo curr_err_state;
};

/* Define variable  ----------------------------------------------------------*/
static struct LDS_DSP_CTX ctx;
/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_dsp_open(char *dev_name)
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
static int lds_hal_dsp_close(int dev_fd)
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
static int lds_hal_dsp_init(void *param)
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
static int lds_hal_dsp_deinit(void)
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
static int lds_hal_dsp_start(void)
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
static int lds_hal_dsp_stop(void)
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
static int lds_hal_dsp_get_error(void)
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
static int lds_hal_dsp_ioctl(LDS_CTRL_DSP type, ...)
{
	switch(type)
	{
		default:
			break;
	}
	
	return 0;
}


struct LDS_DSP_OPERATION lds_hal_dsp = {
    .name                   = "lds_hal_dsp",
    .comm.lds_hal_open      = lds_hal_dsp_open,
    .comm.lds_hal_close     = lds_hal_dsp_close,
    .comm.lds_hal_start     = lds_hal_dsp_start,
    .comm.lds_hal_stop      = lds_hal_dsp_stop,
    .comm.lds_hal_init      = lds_hal_dsp_init,
    .comm.lds_hal_deinit    = lds_hal_dsp_deinit,
    .comm.lds_hal_get_error = lds_hal_dsp_get_error,
    .ioctl                  = lds_hal_dsp_ioctl,
};

