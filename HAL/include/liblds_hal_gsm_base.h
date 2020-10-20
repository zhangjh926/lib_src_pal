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

struct LDS_GSM_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    // int     (*ioctl)(LDS_CTRL_ETH, ...);
	int		(*lds_hal_set_gsm_enable)(int onoff);
	int		(*lds_hal_set_gsm_mac_addr)(char *set_mac_addr);

	int		(*lds_hal_get_gsm_ip)(char *get_ip);
	int		(*lds_hal_get_gsm_gateway)(char *get_gateway);
	int		(*lds_hal_get_gsm_mac_addr)(char *get_mac_addr);
	GSMState(*lds_hal_get_gsm_state)(void);
};

extern struct LDS_ETH_OPERATION lds_hal_eth;

#ifdef __cplusplus
}
#endif

#endif