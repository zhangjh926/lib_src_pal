#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_gsm_base.h"

/* Define  -------------------------------------------------------------------*/
struct LDS_GSM_CTX{
    LDS_GSM_ErrorNo curr_err_state;
};

/* Define variable  ----------------------------------------------------------*/
static struct LDS_GSM_CTX ctx;
/* Define extern variable & function  ----------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_gsm_open(char *dev_name)
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
static int lds_hal_gsm_close(int dev_fd)
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
static int lds_hal_gsm_deinit(void)
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
static int lds_hal_gsm_start(void)
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
static int lds_hal_gsm_stop(void)
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
static int  lds_hal_set_gsm_enable(int onoff)
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
static int  lds_hal_set_gsm_mac_addr(char *set_mac_addr)
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
static int  lds_hal_get_gsm_mac_addr(char *get_mac_addr)
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
static int  lds_hal_get_gsm_ip(char *get_ip)
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
static int  lds_hal_get_gsm_gateway(char *get_gateway)
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
static int  lds_hal_gsm_get_error(void)
{
    return ctx.curr_err_state;
}


struct LDS_GSM_OPERATION        lds_hal_gsm = {
    .name                       = "lds_hal_gsm",
    .comm.lds_hal_open          = lds_hal_gsm_open,
    .comm.lds_hal_close         = lds_hal_gsm_close,
    .comm.lds_hal_start         = lds_hal_gsm_start,
    .comm.lds_hal_stop          = lds_hal_gsm_stop,
    .comm.lds_hal_init          = lds_hal_gsm_init,
    .comm.lds_hal_deinit        = lds_hal_gsm_deinit,
    .comm.lds_hal_get_error     = lds_hal_gsm_get_error,
    .lds_hal_set_gsm_enable     = lds_hal_set_gsm_enable,
    .lds_hal_get_gsm_mac_addr   = lds_hal_get_gsm_mac_addr,
    .lds_hal_set_gsm_mac_addr   = lds_hal_set_gsm_mac_addr,
    .lds_hal_get_gsm_state      = lds_hal_get_gsm_state,
    .lds_hal_get_gsm_ip         = lds_hal_get_gsm_ip,
    .lds_hal_get_gsm_gateway    = lds_hal_get_gsm_gateway,
};