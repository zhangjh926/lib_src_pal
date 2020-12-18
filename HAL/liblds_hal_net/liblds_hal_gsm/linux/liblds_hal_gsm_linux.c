#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_gsm_base.h"

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/
static LDS_GSM_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_gsm_open(void *ctx_t, void *param)
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
static int lds_hal_gsm_close(void *ctx_t)
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
static int lds_hal_gsm_init(void *param)
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
static int lds_hal_gsm_deinit(void *ctx_t)
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
static int lds_hal_gsm_start(void *ctx_t)
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
static int lds_hal_gsm_stop(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

    return 0;
}

#if 0
/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_eth_ioctl(LDS_CTRL_ETH type, ...)
{
	switch(type)
	{
		default:
			break;
	}
	
	return 0;
}
#endif
/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int  lds_hal_set_gsm_enable(LDS_GSM_CTX *ctx, int onoff)
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
static int  lds_hal_set_gsm_mac_addr(LDS_GSM_CTX *ctx, char *set_mac_addr)
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
static int  lds_hal_get_gsm_mac_addr(LDS_GSM_CTX *ctx, char *get_mac_addr)
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
static GSMState lds_hal_get_gsm_state(void)
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
static int  lds_hal_get_gsm_ip(LDS_GSM_CTX *ctx, char *get_ip)
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
static int  lds_hal_get_gsm_gateway(LDS_GSM_CTX *ctx, char *get_gateway)
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
static int  lds_hal_gsm_get_error(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

    return ctx->curr_err_state;
}


struct LDS_GSM_OPERATION        lds_hal_gsm = {
    .name                       = "lds_hal_gsm",
    .base.lds_hal_open          = lds_hal_gsm_open,
    .base.lds_hal_close         = lds_hal_gsm_close,
    .base.lds_hal_start         = lds_hal_gsm_start,
    .base.lds_hal_stop          = lds_hal_gsm_stop,
    .base.lds_hal_get_error     = lds_hal_gsm_get_error,
    .lds_hal_set_gsm_enable     = lds_hal_set_gsm_enable,
    .lds_hal_get_gsm_mac_addr   = lds_hal_get_gsm_mac_addr,
    .lds_hal_set_gsm_mac_addr   = lds_hal_set_gsm_mac_addr,
    .lds_hal_get_gsm_state      = lds_hal_get_gsm_state,
    .lds_hal_get_gsm_ip         = lds_hal_get_gsm_ip,
    .lds_hal_get_gsm_gateway    = lds_hal_get_gsm_gateway,
};