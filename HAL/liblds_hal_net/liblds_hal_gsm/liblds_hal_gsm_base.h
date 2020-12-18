#ifndef _LDS_GSM_OPERATION_H
#define _LDS_GSM_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_GSM_ErrorNo{
	LDS_GSM_OPEN_ERROR,
	LDS_GSM_INIT_ERROR,
	LDS_GSM_START_ERROR,
}LDS_GSM_ErrorNo;

typedef enum _GSMState{
	LDS_GSM_STATE_CONNECTED,
	LDS_GSM_STATE_DISCONNECT,
	LDS_GSM_STATE_NO_IP,
    LDS_GSM_STATE_NO_SIM_CARD,
    LDS_GSM_STATE_NO_MONEY,
}GSMState;

typedef struct _LDS_GSM_CTX{
	char dev_name[128];
	int  dev_fd;
    LDS_GSM_ErrorNo curr_err_state;
}LDS_GSM_CTX;


struct LDS_GSM_OPERATION
{
    struct  LDS_HAL_COMMON base;    
	const   char		  *name;

    // int     (*ioctl)(LDS_CTRL_ETH, ...);
	int		(*lds_hal_set_gsm_enable)(LDS_GSM_CTX *ctx, int onoff);
	int		(*lds_hal_set_gsm_mac_addr)(LDS_GSM_CTX *ctx, char *set_mac_addr);

	int		(*lds_hal_get_gsm_ip)(LDS_GSM_CTX *ctx, char *get_ip);
	int		(*lds_hal_get_gsm_gateway)(LDS_GSM_CTX *ctx, char *get_gateway);
	int		(*lds_hal_get_gsm_mac_addr)(LDS_GSM_CTX *ctx, char *get_mac_addr);
	GSMState(*lds_hal_get_gsm_state)(LDS_GSM_CTX *ctx);
};

extern struct LDS_ETH_OPERATION lds_hal_eth;

#ifdef __cplusplus
}
#endif

#endif