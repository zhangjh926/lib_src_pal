#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_nfc_base.h"

/* Define  -------------------------------------------------------------------*/
struct LDS_NFC_CTX{
    LDS_NFC_ErrorNo curr_err_state;
};

/* Define variable  ----------------------------------------------------------*/
static struct LDS_NFC_CTX ctx;
/* Define extern variable & function  ----------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_nfc_open(char *dev_name)
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
static int lds_hal_nfc_close(int dev_fd)
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
static int lds_hal_nfc_init(void *param)
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
static int lds_hal_nfc_deinit(void)
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
static int lds_hal_nfc_start(void)
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
static int lds_hal_nfc_stop(void)
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
static int  lds_hal_set_nfc_enable(int onoff)
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
static int  lds_hal_nfc_get_error(void)
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
static int  lds_hal_nfc_identification(void)
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
static int  lds_hal_nfc_send_data(char *send_data)
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
static int  lds_hal_nfc_recv_data(char *recv_data)
{
    return 0;
}

struct LDS_NFC_OPERATION        lds_hal_nfc = {
    .name                       = "lds_hal_nfc",
    .comm.lds_hal_open          = lds_hal_nfc_open,
    .comm.lds_hal_close         = lds_hal_nfc_close,
    .comm.lds_hal_start         = lds_hal_nfc_start,
    .comm.lds_hal_stop          = lds_hal_nfc_stop,
    .comm.lds_hal_init          = lds_hal_nfc_init,
    .comm.lds_hal_deinit        = lds_hal_nfc_deinit,
    .comm.lds_hal_get_error     = lds_hal_nfc_get_error,
    .lds_hal_set_nfc_enable     = lds_hal_set_nfc_enable,
    .lds_hal_nfc_identification = lds_hal_nfc_identification,
    .lds_hal_nfc_send_data      = lds_hal_nfc_send_data,
    .lds_hal_nfc_recv_data      = lds_hal_nfc_recv_data,
};