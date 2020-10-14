#ifndef _LDS_WIFI_OPERATION_H
#define _LDS_WIFI_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_WIFI_ErrorNo{
	LDS_WIFI_OPEN_ERROR,
	LDS_WIFI_INIT_ERROR,
	LDS_WIFI_START_ERROR,
}LDS_DSP_ErrorNo;

typedef enum _LDS_WIFI_MODE{
	LDS_CTRL_WIFI_AP_MODE,
	LDS_CTRL_WIFI_STA_MODE,
	LDS_CTRL_WIFI_APSTA_MODE,
}LDS_WIFI_MODE;

typedef enum _LDS_WIFI_ENCRYPT_TYPE{
     LDS_WIFI_ENCRYPT_TYPE_NONE,
     LDS_WIFI_ENCRYPT_TYPE_WEP,
     LDS_WIFI_ENCRYPT_TYPE_WPA_TKIP,
     LDS_WIFI_ENCRYPT_TYPE_WPA_AES,
     LDS_WIFI_ENCRYPT_TYPE_WPA2_TKIP,
     LDS_WIFI_ENCRYPT_TYPE_WPA2_AES,
     LDS_WIFI_ENCRYPT_TYPE_WPA_PSK_TKIP,
     LDS_WIFI_ENCRYPT_TYPE_WPA_PSK_AES,
     LDS_WIFI_ENCRYPT_TYPE_WPA2_PSK_TKIP,
     LDS_WIFI_ENCRYPT_TYPE_WPA2_PSK_AES,
     LDS_WIFI_ENCRYPT_TYPE_WPA3,
}LDS_WIFI_ENCRYPT_TYPE;

typedef enum _LDS_WIFI_STATUS{
    LDS_WIFI_STATUS_CONNECTED,
    LDS_WIFI_STATUS_DISCONNECT,
}LDS_WIFI_STATUS;

typedef enum _LDS_WIFI_COUNTRY_CODE{
    US,
    TW,
    CN,
}LDS_WIFI_COUNTRY_CODE;

typedef struct _WIFILIST{
    char *  bssid[64];
    char *  ssid[128];
    int     channel;
    int     signal_dbm;
    int     encrypt_type;
}WIFI_LIST;

struct LDS_WIFI_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    //int     (*ioctl)(LDS_CTRL_WIFI, ...);
    int     (*lds_hal_set_wifi_switch_mode)(LDS_WIFI_MODE wifi_mode);
    int     (*lds_hal_set_wifi_ssid)(char *ssid);
    int     (*lds_hal_set_wifi_pwd)(char *pwd);
    int     (*lds_hal_set_wifi_encrypt)(LDS_WIFI_ENCRYPT_TYPE encrypt_mode);
    int     (*lds_hal_set_wifi_reset)(void);
    int     (*lds_hal_set_wifi_country_code)(LDS_WIFI_COUNTRY_CODE country_code);
    int     (*lds_hal_set_wifi_channel)(int channel);
    int     (*lds_hal_set_wifi_enable)(int onoff);
    int     (*lds_hal_set_wifi_macaddr)(char *set_mac_addr);
    
    int     (*lds_hal_get_wifi_ip)(char *get_ip);
    int     (*lds_hal_get_wifi_gateway)(char *get_gateway);
    int     (*lds_hal_get_wifi_macaddr)(char *get_mac_addr);
    int     (*lds_hal_get_wifi_list)(WIFI_LIST *wifi_list);
    int     (*lds_hal_get_wifi_signal_value)(void);
    LDS_WIFI_STATUS     (*lds_hal_get_wifi_state)(void);
    
};

extern struct LDS_WIFI_OPERATION lds_hal_wifi;

#ifdef __cplusplus
}
#endif

#endif
