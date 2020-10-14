#ifndef _LDS_ETH_OPERATION_H
#define _LDS_ETH_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_ETH_ErrorNo{
	LDS_ETH_OPEN_ERROR,
	LDS_ETH_INIT_ERROR,
	LDS_ETH_START_ERROR,
}LDS_ETH_ErrorNo;

typedef enum _EthState{
	LDS_ETH_STATE_CONNECTED,
	LDS_ETH_STATE_DISCONNECT,
	LDS_ETH_STATE_NO_IP,
}EthState;

struct LDS_ETH_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    // int     (*ioctl)(LDS_CTRL_ETH, ...);
	int		(*lds_hal_set_eth_enable)(int onoff);
	int		(*lds_hal_set_eth_mac_addr)(char *set_mac_addr);

	int		(*lds_hal_get_eth_ip)(char *get_ip);
	int		(*lds_hal_get_eth_gateway)(char *get_gateway);
	int		(*lds_hal_get_eth_mac_addr)(char *get_mac_addr);
	EthState(*lds_hal_get_eth_state)(void);
};

extern struct LDS_ETH_OPERATION lds_hal_eth;

#ifdef __cplusplus
}
#endif

#endif