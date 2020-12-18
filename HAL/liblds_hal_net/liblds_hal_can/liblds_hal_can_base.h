#ifndef _LDS_CAN_OPERATION_H
#define _LDS_CAN_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_CAN_ErrorNo{
	LDS_CAN_OPEN_ERROR,
	LDS_CAN_INIT_ERROR,
	LDS_CAN_START_ERROR,
}LDS_CAN_ErrorNo;

typedef enum _CANState{
	LDS_CAN_STATE_CONNECTED,
	LDS_CAN_STATE_DISCONNECT,
	LDS_CAN_STATE_NO_IP,
}CANState;


typedef struct _LDS_CAN_CTX{
	char dev_name[128];
	int  dev_fd;
    LDS_CAN_ErrorNo curr_err_state;
}LDS_CAN_CTX;


struct LDS_CAN_OPERATION
{
    struct  LDS_HAL_COMMON base;
	const   char		  *name;

    // int     (*ioctl)(LDS_CTRL_ETH, ...);
	int		(*lds_hal_set_can_enable)(LDS_CAN_CTX *ctx, int onoff);

	int		(*lds_hal_can_recv_data)(LDS_CAN_CTX *ctx, char *recv_data);
	int		(*lds_hal_can_send_data)(LDS_CAN_CTX *ctx, char *send_data);
};

extern struct LDS_CAN_OPERATION lds_hal_can;

#ifdef __cplusplus
}
#endif

#endif