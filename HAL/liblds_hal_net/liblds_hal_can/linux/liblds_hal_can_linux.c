#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_can_base.h"

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/
static LDS_CAN_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_can_open(void *ctx_t, void *param)
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
static int lds_hal_can_close(void *ctx_t)
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
static int lds_hal_can_init(void *param)
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
static int lds_hal_can_deinit(void *ctx_t)
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
static int lds_hal_can_start(void *ctx_t)
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
static int lds_hal_can_stop(void *ctx_t)
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
static int  lds_hal_set_can_enable(LDS_CAN_CTX *ctx, int onoff)
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
static int  lds_hal_can_get_error(void *ctx_t)
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
static int  lds_hal_can_recv_data(LDS_CAN_CTX *ctx, char *recv_data)
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
static int  lds_hal_can_send_data(LDS_CAN_CTX *ctx, char *send_data)
{
    return 0;
}

struct LDS_CAN_OPERATION        lds_hal_can = {
    .name                       = "lds_hal_can",
    .base.lds_hal_open          = lds_hal_can_open,
    .base.lds_hal_close         = lds_hal_can_close,
    .base.lds_hal_start         = lds_hal_can_start,
    .base.lds_hal_stop          = lds_hal_can_stop,
    .base.lds_hal_get_error     = lds_hal_can_get_error,
    .lds_hal_set_can_enable     = lds_hal_set_can_enable,
    .lds_hal_can_recv_data      = lds_hal_can_recv_data,
    .lds_hal_can_send_data      = lds_hal_can_send_data,
};