/*
 * libwpa_test - Test program for libwpa_client.* library linking
 * Copyright (c) 2015, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */
#ifndef _LIBWPA_TEST_H
#define _LIBWPA_TEST_H

#ifdef __cplusplus
extern "C"{
#endif


#include <sys/ioctl.h>
#include <unistd.h>
#include "includes.h"

#include "wpa_ctrl.h"
#ifndef CONFIG_CTRL_IFACE_DIR
#define CONFIG_CTRL_IFACE_DIR "/var/run/wpa_supplicant"
#endif /* CONFIG_CTRL_IFACE_DIR */



#define WIFI_PORT_WLAN0          "wlan0"
#define WIFI_PORT_WLAN1          "wlan1"

typedef struct _WIFI_PARAM{
	int	wifi_mode;
	char ap_ssid[64];
	char ap_pwd[64];
	char ap_port[10];
	int ap_encrypt_type;
	int ap_channel;
	char sta_ssid[256];
	char sta_pwd[256];
	char sta_port[10];
	int sta_encrypt_type;
	int wifi_status;
	pthread_t sta_check_threadID;  
	int sta_thread_running_flag;
}WIFI_PARAM;

//struct WIFI_PARAM g_wifi_param;
/*
int g_lds_hal_wifi_mode               = -1;
char g_lds_hal_wifi_ssid              = [256];
char g_lds_hal_wifi_pwd               = [256];
int g_lds_hal_wifi_encrypt_mode       = -1;
int g_lds_hal_wifi_channel_numb       = 0;
int g_lds_hal_wifi_start_or_stop      = -1;
char g_device_name                   = [256];
*/

//static const char *ctrl_iface_dir = CONFIG_CTRL_IFACE_DIR;
//static struct wpa_ctrl *ctrl_conn = NULL;

/*
int lds_hal_wpa_scan(struct wpa_ctrl *ctrl, const char *ifname);
int lds_hal_wpa_scan_result(struct wpa_ctrl *ctrl, const char *ifname, char *reply, size_t *reply_size);
int lds_hal_wpa_add_network(struct wpa_ctrl *ctrl, const char *ifname, char *networkId);
int lds_hal_wpa_set_network(struct wpa_ctrl *ctrl, const char *ifname, char *cmd);
int lds_hal_wpa_enable_network(struct wpa_ctrl *ctrl, const char *ifname, char *cmd);
int lds_hal_wpa_select_network(struct wpa_ctrl *ctrl, const char *ifname, char *cmd);
int lds_hal_wpa_cli_cmd_save_config(struct wpa_ctrl *ctrl, const char *ifname, char *cmd);
int lds_hal_wpa_cli_cmd_reconnect(struct wpa_ctrl *ctrl, const char *ifname, char *cmd);
int lds_hal_wpa_cli_cmd_disconnect(struct wpa_ctrl *ctrl, const char *ifname, char *cmd);
int lds_hal_wpa_status(struct wpa_ctrl *ctrl, const char *ifname, char *reply, size_t *reply_size);
*/

int lds_get_wifi_status(void);
int lds_hal_init(void *param);
void lds_wifi_ap_stop(int fddev);
int lds_wifi_ap_mode(int dev_fd, char *devName);
int lds_wifi_sta_mode(int dev_fd, char* pdevName);
int lds_wifi_sta_stop(int fddev);
void lds_wifi_ap_stop(int fddev);
int lds_wpa_wifi_list(WIFI_LIST *wifi_list);

#ifdef __cplusplus
}
#endif

#endif
