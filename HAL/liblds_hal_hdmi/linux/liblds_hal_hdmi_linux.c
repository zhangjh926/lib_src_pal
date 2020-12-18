#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_hdmi_base.h"

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/
static LDS_HDMI_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_hdmi_open(void *ctx_t, void *param)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

    return 0;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_hdmi_close(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

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
static int lds_hal_hdmi_deinit(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_hdmi_start(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_hdmi_stop(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_hdmi_get_error(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;
    
    return ctx->curr_err_state;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_hdmi_ioctl(LDS_HDMI_CTX *ctx, LDS_CTRL_HDMI type, ...)
{
    if( NULL == ctx) return -1;

	switch(type){
		default:
			break;
	}
	
	return 0;
}


struct LDS_HDMI_OPERATION lds_hal_hdmi = {
    .name                   = "lds_hal_hdmi",
    .base.lds_hal_open      = lds_hal_hdmi_open,
    .base.lds_hal_close     = lds_hal_hdmi_close,
    .base.lds_hal_start     = lds_hal_hdmi_start,
    .base.lds_hal_stop      = lds_hal_hdmi_stop,
    .base.lds_hal_get_error = lds_hal_hdmi_get_error,
    .ioctl                  = lds_hal_hdmi_ioctl,
};