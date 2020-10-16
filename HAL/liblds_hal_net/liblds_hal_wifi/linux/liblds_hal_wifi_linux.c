#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_wifi_base.h"

/* Define  -------------------------------------------------------------------*/
struct LDS_WIFI_CTX{
    LDS_DSP_ErrorNo curr_err_state;
};

/* Define variable  ----------------------------------------------------------*/
static struct LDS_WIFI_CTX ctx;
/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_wifi_open(char *dev_name)
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
static int lds_hal_wifi_close(int dev_fd)
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
static int lds_hal_wifi_init(void *param)
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
static int lds_hal_wifi_deinit(void)
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
static int lds_hal_wifi_start(void)
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
static int lds_hal_wifi_stop(void)
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
static int lds_hal_wifi_ioctl(LDS_CTRL_WIFI type, ...)
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
static int  lds_hal_set_wifi_switch_mode(LDS_WIFI_MODE wifi_mode)
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
static int  lds_hal_set_wifi_ssid(char *ssid)
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
static int  lds_hal_set_wifi_pwd(char *pwd)
{

    return 0;
}

static int  lds_hal_set_wifi_encrypt(LDS_WIFI_ENCRYPT_TYPE encrypt_mode)
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
static int  lds_hal_set_wifi_reset(void)
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
static int  lds_hal_set_wifi_country_code(LDS_WIFI_COUNTRY_CODE country_code)
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
static int  lds_hal_set_wifi_channel(int channel)
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
static int  lds_hal_get_wifi_list(WIFI_LIST *wifi_list)
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
static int  lds_hal_get_wifi_signal_value(void)
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
static LDS_WIFI_STATUS  lds_hal_get_wifi_state(void)
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
static int     lds_hal_set_wifi_enable(int onoff)
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
static int  lds_hal_set_wifi_macaddr(char *set_mac_addr)
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
static int  lds_hal_get_wifi_macaddr(char *get_mac_addr)
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
static int  lds_hal_get_wifi_ip(char *get_ip)
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
static int  lds_hal_get_wifi_gateway(char *get_gateway)
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
static int  lds_hal_wifi_get_error(void)
{
    return ctx.curr_err_state;
}


struct LDS_WIFI_OPERATION lds_hal_wifi = {
    .name                           = "lds_hal_wifi",
    .comm.lds_hal_open              = lds_hal_wifi_open,
    .comm.lds_hal_close             = lds_hal_wifi_close,
    .comm.lds_hal_start             = lds_hal_wifi_start,
    .comm.lds_hal_stop              = lds_hal_wifi_stop,
    .comm.lds_hal_init              = lds_hal_wifi_init,
    .comm.lds_hal_deinit            = lds_hal_wifi_deinit,
    .comm.lds_hal_get_error         = lds_hal_wifi_get_error,
    .lds_hal_set_wifi_switch_mode   = lds_hal_set_wifi_switch_mode,
    .lds_hal_set_wifi_ssid          = lds_hal_set_wifi_ssid,
    .lds_hal_set_wifi_pwd           = lds_hal_set_wifi_pwd,
    .lds_hal_set_wifi_encrypt       = lds_hal_set_wifi_encrypt,
    .lds_hal_set_wifi_reset         = lds_hal_set_wifi_reset,
    .lds_hal_set_wifi_country_code  = lds_hal_set_wifi_country_code,
    .lds_hal_set_wifi_channel       = lds_hal_set_wifi_channel,
    .lds_hal_get_wifi_list          = lds_hal_get_wifi_list,
    .lds_hal_get_wifi_signal_value  = lds_hal_get_wifi_signal_value,
    .lds_hal_get_wifi_state         = lds_hal_get_wifi_state,
    .lds_hal_set_wifi_enable        = lds_hal_set_wifi_enable,
    .lds_hal_set_wifi_macaddr       = lds_hal_set_wifi_macaddr,
    .lds_hal_get_wifi_macaddr       = lds_hal_get_wifi_macaddr,
    .lds_hal_get_wifi_ip            = lds_hal_get_wifi_ip,
    .lds_hal_get_wifi_gateway       = lds_hal_get_wifi_gateway,
};