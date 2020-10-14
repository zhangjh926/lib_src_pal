#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_bluetooth_base.h"

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
static int lds_hal_bluetooth_open(char *dev_name)
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
static int lds_hal_bluetooth_close(int dev_fd)
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
static int lds_hal_bluetooth_deinit(void)
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
static int lds_hal_bluetooth_start(void)
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
static int lds_hal_bluetooth_stop(void)
{
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
static int  lds_hal_set_ble_uuid(char *uuid)
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
static int  lds_hal_set_ble_model_name(char *model_name)
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
static int  lds_hal_ble_bind(void)
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
static int  lds_hal_ble_unbind(void)
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
static int  lds_hal_ble_start_advertise(void)
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
static int  lds_hal_ble_send_data(char *send_data)
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
static int  lds_hal_ble_recv_data(char* recv_data)
{
    return 0;
}

struct LDS_BLUETOOTH_OPERATION lds_hal_bluetooth = {
    .name                       = "lds_hal_bluetooth",
    .comm.lds_hal_open          = lds_hal_bluetooth_open,
    .comm.lds_hal_close         = lds_hal_bluetooth_close,
    .comm.lds_hal_start         = lds_hal_bluetooth_start,
    .comm.lds_hal_stop          = lds_hal_bluetooth_stop,
    .comm.lds_hal_init          = lds_hal_bluetooth_init,
    .comm.lds_hal_deinit        = lds_hal_bluetooth_deinit,
    .lds_hal_set_ble_uuid       = lds_hal_set_ble_uuid,
    .lds_hal_set_ble_model_name = lds_hal_set_ble_model_name,
    .lds_hal_ble_bind           = lds_hal_ble_bind,
    .lds_hal_ble_unbind         = lds_hal_ble_unbind,
    .lds_hal_ble_start_advertise= lds_hal_ble_start_advertise,
    .lds_hal_ble_send_data      = lds_hal_ble_send_data,
    .lds_hal_ble_recv_data      = lds_hal_ble_recv_data,
};