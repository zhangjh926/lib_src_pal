#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_can_base.h"

/* Define  -------------------------------------------------------------------*/
struct LDS_CAN_CTX{
    LDS_CAN_ErrorNo curr_err_state;
};

/* Define variable  ----------------------------------------------------------*/
static struct LDS_CAN_CTX ctx;
/* Define extern variable & function  ----------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_can_open(char *dev_name)
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
static int lds_hal_can_close(int dev_fd)
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
static int lds_hal_can_deinit(void)
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
static int lds_hal_can_start(void)
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
static int lds_hal_can_stop(void)
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
static int  lds_hal_set_can_enable(int onoff)
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
static int  lds_hal_can_get_error(void)
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
static int  lds_hal_can_recv_data(char *recv_data)
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
static int  lds_hal_can_send_data(char *send_data)
{
    return 0;
}

struct LDS_CAN_OPERATION        lds_hal_can = {
    .name                       = "lds_hal_can",
    .comm.lds_hal_open          = lds_hal_can_open,
    .comm.lds_hal_close         = lds_hal_can_close,
    .comm.lds_hal_start         = lds_hal_can_start,
    .comm.lds_hal_stop          = lds_hal_can_stop,
    .comm.lds_hal_init          = lds_hal_can_init,
    .comm.lds_hal_deinit        = lds_hal_can_deinit,
    .comm.lds_hal_get_error     = lds_hal_can_get_error,
    .lds_hal_set_can_enable     = lds_hal_set_can_enable,
    .lds_hal_can_recv_data      = lds_hal_can_recv_data,
    .lds_hal_can_send_data      = lds_hal_can_send_data,
};