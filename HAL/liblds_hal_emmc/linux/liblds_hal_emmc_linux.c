#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_emmc_base.h"

/* Define  -------------------------------------------------------------------*/

/* Define variable  ----------------------------------------------------------*/
static LDS_EMMC_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_emmc_open(void *ctx_t, void *param)
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
static int lds_hal_emmc_close(void *ctx_t)
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
static int lds_hal_emmc_init(void *param)
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
static int lds_hal_emmc_deinit(void *ctx_t)
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
static int lds_hal_emmc_start(void *ctx_t)
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
static int lds_hal_emmc_stop(void *ctx_t)
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
static int lds_hal_emmc_get_error(void *ctx_t)
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
static int lds_hal_emmc_ioctl(LDS_EMMC_CTX *ctx_t, LDS_CTRL_EMMC type, ...)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

	switch(type){
		default:
			break;
	}
	
	return 0;
}


struct LDS_EMMC_OPERATION lds_hal_emmc = {
    .name                   = "lds_hal_emmc",
    .base.lds_hal_open      = lds_hal_emmc_open,
    .base.lds_hal_close     = lds_hal_emmc_close,
    .base.lds_hal_start     = lds_hal_emmc_start,
    .base.lds_hal_stop      = lds_hal_emmc_stop,
    .base.lds_hal_get_error = lds_hal_emmc_get_error,
    .ioctl                  = lds_hal_emmc_ioctl,
};

