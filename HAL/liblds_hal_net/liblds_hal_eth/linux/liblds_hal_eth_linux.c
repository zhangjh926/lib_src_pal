#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_eth_base.h"

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/
static LDS_ETH_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_eth_open(void *ctx_t, void *param)
{
    if(NULL == ctx_t ) return -1;
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
static int lds_hal_eth_close(void *ctx_t)
{
    if(NULL == ctx_t ) return -1;
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
static int lds_hal_eth_init(void *param)
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
static int lds_hal_eth_deinit(void *ctx_t)
{
    if(NULL == ctx_t ) return -1;
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
static int lds_hal_eth_start(void *ctx_t)
{
    if(NULL == ctx_t ) return -1;
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
static int lds_hal_eth_stop(void *ctx_t)
{
    if(NULL == ctx_t ) return -1;
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
static int  lds_hal_set_eth_enable(LDS_ETH_CTX *ctx, int onoff)
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
static int  lds_hal_set_eth_mac_addr(LDS_ETH_CTX *ctx, char *set_mac_addr)
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
static int  lds_hal_get_eth_mac_addr(LDS_ETH_CTX *ctx, char *get_mac_addr)
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
static EthState lds_hal_get_eth_state(void)
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
static int  lds_hal_get_eth_ip(LDS_ETH_CTX *ctx, char *get_ip)
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
static int  lds_hal_get_eth_gateway(LDS_ETH_CTX *ctx, char *get_gateway)
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
static int  lds_hal_eth_get_error(void *ctx_t)
{
    if(NULL == ctx_t ) return -1;
    else ctx = ctx_t;

    return ctx->curr_err_state;
}


struct LDS_ETH_OPERATION lds_hal_eth = {
    .name                       = "lds_hal_eth",
    .base.lds_hal_open          = lds_hal_eth_open,
    .base.lds_hal_close         = lds_hal_eth_close,
    .base.lds_hal_start         = lds_hal_eth_start,
    .base.lds_hal_stop          = lds_hal_eth_stop,
    .base.lds_hal_get_error     = lds_hal_eth_get_error,
    .lds_hal_set_eth_enable     = lds_hal_set_eth_enable,
    .lds_hal_get_eth_mac_addr   = lds_hal_get_eth_mac_addr,
    .lds_hal_set_eth_mac_addr   = lds_hal_set_eth_mac_addr,
    .lds_hal_get_eth_state      = lds_hal_get_eth_state,
    .lds_hal_get_eth_ip         = lds_hal_get_eth_ip,
    .lds_hal_get_eth_gateway    = lds_hal_get_eth_gateway,
};