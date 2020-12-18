#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_wifi_base.h"
#include "lds_wifi_wpa_cmd.h"

extern WIFI_PARAM g_wifi_param;

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/
static LDS_WIFI_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_wifi_open(void *ctx_t, void *param)
{
	
  //  if(NULL == ctx_t) return -1;
  //  else ctx = ctx_t;
	lds_hal_init(param);

    return 0;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_wifi_close(void *ctx_t)
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
static int lds_hal_wifi_init(void *param)
{
	lds_hal_init(param);
    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_wifi_deinit(void *ctx_t)
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
static int lds_hal_wifi_start(void *ctx_t)
{	

	int ret = -1;
	/*
	if(type == 0) //wlan0 sta
		return	lds_wifi_sta_mode(dev_fd);
	else //if(dev_fd == 1) //wlan1 ap
		return	lds_wifi_ap_mode(dev_fd);
   // return 0;
   */
   
	if(NULL == ctx_t) return -1;
		else ctx = ctx_t;
	
   	switch(ctx->dev_fd)
	{
		case LDS_CTRL_WIFI_AP_MODE:
			ret = lds_wifi_ap_mode(ctx->dev_fd, ctx->dev_name);
		break;
		
		case LDS_CTRL_WIFI_STA_MODE:
			ret = lds_wifi_sta_mode(ctx->dev_fd, ctx->dev_name);
		break;
		
		case LDS_CTRL_WIFI_APSTA_MODE:
			printf("lds_hal_wifi_start LDS_CTRL_WIFI_APSTA_MODE?\r\n");
		break;
		
		default:
			printf("lds_hal_wifi_start no support type?\r\n");
		break;
	}
	
	return ret;
	
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_wifi_stop(void *ctx_t)
{
	
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

	switch(ctx->dev_fd)
	{
		case LDS_CTRL_WIFI_AP_MODE:
			lds_wifi_ap_stop(ctx->dev_fd);
		break;
		
		case LDS_CTRL_WIFI_STA_MODE:
			lds_wifi_sta_stop(ctx->dev_fd);
		break;
		
		case LDS_CTRL_WIFI_APSTA_MODE:
			printf("lds_hal_wifi_stop stop ap and sta?\r\n");
		break;
		
		default:
			printf("lds_hal_wifi_stop no support type?\r\n");
		break;
	}
	
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
static int  lds_hal_set_wifi_switch_mode(LDS_WIFI_CTX *ctx, LDS_WIFI_MODE wifi_mode)
{
	switch(wifi_mode)
	{
		case LDS_CTRL_WIFI_AP_MODE:
			g_wifi_param.wifi_mode = LDS_CTRL_WIFI_AP_MODE;
			break;
			
		case LDS_CTRL_WIFI_STA_MODE:
			g_wifi_param.wifi_mode = LDS_CTRL_WIFI_STA_MODE;
			break;
			
		case LDS_CTRL_WIFI_APSTA_MODE:
			g_wifi_param.wifi_mode = LDS_CTRL_WIFI_APSTA_MODE;
			break;
			
		case LDS_CTRL_WIFI_WPS_MODE:
			g_wifi_param.wifi_mode = LDS_CTRL_WIFI_WPS_MODE;
			printf("lds_hal_set_wifi_switch_mode->LDS_CTRL_WIFI_WPS_MODE nosupport!\r\n");
			break;
		
		default:
			g_wifi_param.wifi_mode = -1;
			printf("lds_hal_set_wifi_switch_mode default!\r\n");
			break;
	}
	
    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:type: 0->sta,1->ap
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int  lds_hal_set_wifi_ssid(LDS_WIFI_CTX *ctx, LDS_WIFI_MODE type, char *ssid)
{
	if(ssid == NULL)
		return -1;
	if(0 == type)
	{
		memset(g_wifi_param.sta_ssid, 0, 256);
		strncpy(g_wifi_param.sta_ssid, ssid, strlen(ssid));
	}else if(1 == type){
		memset(g_wifi_param.ap_ssid, 0, 64);
		strncpy(g_wifi_param.ap_ssid, ssid, strlen(ssid));
	}
	
    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int  lds_hal_set_wifi_pwd(LDS_WIFI_CTX *ctx, LDS_WIFI_MODE type, char *pwd)
{
	if(pwd == NULL)
		return -1;
	
	if(0 == type)
	{
		memset(g_wifi_param.sta_pwd, 0, 256);
		strncpy(g_wifi_param.sta_pwd, pwd, strlen(pwd));
	}else if(1 == type){
		memset(g_wifi_param.ap_pwd, 0, 64);
		strncpy(g_wifi_param.ap_pwd, pwd, strlen(pwd));
	}

    return 0;
}
/*******************************************************************************
*   Description     :
*   Argurments      :
*   Return value    :
*   Modify          :
*   warning         :
*******************************************************************************/
static int  lds_hal_set_wifi_encrypt(LDS_WIFI_CTX *ctx, int type, LDS_WIFI_ENCRYPT_TYPE encrypt_mode)

{ 
	if(type == 0)
	{
		switch(encrypt_mode)
		{
		case LDS_WIFI_ENCRYPT_TYPE_WPA2_PSK_AES:
			g_wifi_param.sta_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA2_PSK_AES;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA2_PSK_TKIP:
			g_wifi_param.sta_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA2_PSK_TKIP;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA_PSK_AES:
			g_wifi_param.sta_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA_PSK_AES;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA_PSK_TKIP:
			g_wifi_param.sta_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA_PSK_TKIP;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA2_AES:
			g_wifi_param.sta_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA2_AES;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA2_TKIP:
			g_wifi_param.sta_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA2_TKIP;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA_AES:
			g_wifi_param.sta_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA_AES;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA_TKIP:
			g_wifi_param.sta_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA_TKIP;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WEP:
			g_wifi_param.sta_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WEP;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_NONE:
			g_wifi_param.sta_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_NONE;
			break;
			
		default:
			g_wifi_param.sta_encrypt_type = -1;
			break;
		}
	}else if(type == 1)
	{
		switch(encrypt_mode)
		{
		case LDS_WIFI_ENCRYPT_TYPE_WPA2_PSK_AES:
			g_wifi_param.ap_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA2_PSK_AES;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA2_PSK_TKIP:
			g_wifi_param.ap_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA2_PSK_TKIP;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA_PSK_AES:
			g_wifi_param.ap_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA_PSK_AES;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA_PSK_TKIP:
			g_wifi_param.ap_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA_PSK_TKIP;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA2_AES:
			g_wifi_param.ap_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA2_AES;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA2_TKIP:
			g_wifi_param.ap_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA2_TKIP;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA_AES:
			g_wifi_param.ap_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA_AES;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WPA_TKIP:
			g_wifi_param.ap_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WPA_TKIP;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_WEP:
			g_wifi_param.ap_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_WEP;
			break;
			
		case LDS_WIFI_ENCRYPT_TYPE_NONE:
			g_wifi_param.ap_encrypt_type = LDS_WIFI_ENCRYPT_TYPE_NONE;
			break;
			
		default:
			g_wifi_param.ap_encrypt_type = -1;
			break;
		}
	}
	
    return 0; 
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int  lds_hal_set_wifi_reset(LDS_WIFI_CTX *ctx)
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
static int  lds_hal_set_wifi_country_code(LDS_WIFI_CTX *ctx, LDS_WIFI_COUNTRY_CODE country_code)
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
static int  lds_hal_set_wifi_channel(LDS_WIFI_CTX *ctx, int channel)
{ 
	g_wifi_param.ap_channel = channel;
    return 0; 
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int  lds_hal_get_wifi_list(LDS_WIFI_CTX *ctx, WIFI_LIST *wifi_list)
{ 
	//lds_wpa_wifi_list(wifi_list);
    return lds_wpa_wifi_list(wifi_list); 
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int  lds_hal_get_wifi_signal_value(LDS_WIFI_CTX *ctx)
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
static LDS_WIFI_STATUS  lds_hal_get_wifi_state(LDS_WIFI_CTX *ctx)
{ 
    return lds_get_wifi_status(); 
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int     lds_hal_set_wifi_enable(LDS_WIFI_CTX *ctx, int onoff)
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
static int  lds_hal_set_wifi_macaddr(LDS_WIFI_CTX *ctx, char *set_mac_addr)
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
static int  lds_hal_get_wifi_macaddr(LDS_WIFI_CTX *ctx, char *get_mac_addr)
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
static int  lds_hal_get_wifi_ip(LDS_WIFI_CTX *ctx, char *get_ip)
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
static int  lds_hal_get_wifi_gateway(LDS_WIFI_CTX *ctx, char *get_gateway)
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
static int  lds_hal_wifi_get_error(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

    return ctx->curr_err_state;
}


struct LDS_WIFI_OPERATION lds_hal_wifi = {
    .name                           = "lds_hal_wifi",
    .base.lds_hal_open              = lds_hal_wifi_open,
    .base.lds_hal_close             = lds_hal_wifi_close,
    .base.lds_hal_start             = lds_hal_wifi_start,
    .base.lds_hal_stop              = lds_hal_wifi_stop,
    .base.lds_hal_get_error         = lds_hal_wifi_get_error,
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