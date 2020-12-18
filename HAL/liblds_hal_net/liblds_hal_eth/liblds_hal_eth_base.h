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

typedef struct _LDS_ETH_CTX{
	char dev_name[128];
	int  dev_fd;
    LDS_ETH_ErrorNo curr_err_state;
}LDS_ETH_CTX;

struct LDS_ETH_OPERATION
{
    struct  LDS_HAL_COMMON base;    
	const   char		  *name;

    // int     (*ioctl)(LDS_CTRL_ETH, ...);
	int		(*lds_hal_set_eth_enable)(LDS_ETH_CTX *ctx, int onoff);
	int		(*lds_hal_set_eth_mac_addr)(LDS_ETH_CTX *ctx, char *set_mac_addr);

	int		(*lds_hal_get_eth_ip)(LDS_ETH_CTX *ctx, char *get_ip);
	int		(*lds_hal_get_eth_gateway)(LDS_ETH_CTX *ctx, char *get_gateway);
	int		(*lds_hal_get_eth_mac_addr)(LDS_ETH_CTX *ctx, char *get_mac_addr);
	EthState(*lds_hal_get_eth_state)(LDS_ETH_CTX *ctx);
};

extern struct LDS_ETH_OPERATION lds_hal_eth;

#ifdef __cplusplus
}
#endif

#endif