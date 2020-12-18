#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_bluetooth_base.h"

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/
static LDS_BLUETOOTH_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_bluetooth_open(void *ctx_t, void *param)
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
static int lds_hal_bluetooth_close(void *ctx_t)
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
static int lds_hal_bluetooth_init(void *param)
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
static int lds_hal_bluetooth_deinit(void *ctx_t)
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
static int lds_hal_bluetooth_start(void *ctx_t)
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
static int lds_hal_bluetooth_stop(void *ctx_t)
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
static int lds_hal_bluetooth_ioctl(LDS_CTRL_BLUETOOTH type, ...)
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
static int  lds_hal_set_ble_uuid(LDS_BLUETOOTH_CTX *ctx, char *uuid)
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
static int  lds_hal_set_ble_model_name(LDS_BLUETOOTH_CTX *ctx, char *model_name)
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
static int  lds_hal_ble_bind(LDS_BLUETOOTH_CTX *ctx)
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
static int  lds_hal_ble_unbind(LDS_BLUETOOTH_CTX *ctx)
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
static int  lds_hal_ble_start_advertise(LDS_BLUETOOTH_CTX *ctx)
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
static int  lds_hal_ble_send_data(LDS_BLUETOOTH_CTX *ctx, char *send_data)
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
static int  lds_hal_ble_recv_data(LDS_BLUETOOTH_CTX *ctx, char* recv_data)
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
static int  lds_hal_ble_mesh_enable(LDS_BLUETOOTH_CTX *ctx, int onoff)
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
static int  lds_hal_bluetooth_get_error(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

    return ctx->curr_err_state;
}

struct LDS_BLUETOOTH_OPERATION lds_hal_bluetooth = {
    .name                       = "lds_hal_bluetooth",
    .base.lds_hal_open          = lds_hal_bluetooth_open,
    .base.lds_hal_close         = lds_hal_bluetooth_close,
    .base.lds_hal_start         = lds_hal_bluetooth_start,
    .base.lds_hal_stop          = lds_hal_bluetooth_stop,
    .base.lds_hal_get_error     = lds_hal_bluetooth_get_error,
    .lds_hal_set_ble_uuid       = lds_hal_set_ble_uuid,
    .lds_hal_set_ble_model_name = lds_hal_set_ble_model_name,
    .lds_hal_ble_bind           = lds_hal_ble_bind,
    .lds_hal_ble_unbind         = lds_hal_ble_unbind,
    .lds_hal_ble_start_advertise= lds_hal_ble_start_advertise,
    .lds_hal_ble_send_data      = lds_hal_ble_send_data,
    .lds_hal_ble_recv_data      = lds_hal_ble_recv_data,
    .lds_hal_ble_mesh_enable    = lds_hal_ble_mesh_enable,
};