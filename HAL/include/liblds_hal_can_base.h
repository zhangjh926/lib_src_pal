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

struct LDS_CAN_OPERATION
{
    struct  LDS_HAL_COMMON comm;
	const   char		  *name;

    // int     (*ioctl)(LDS_CTRL_ETH, ...);
	int		(*lds_hal_set_can_enable)(int onoff);

	int		(*lds_hal_can_recv_data)(char *recv_data);
	int		(*lds_hal_can_send_data)(char *send_data);
};

extern struct LDS_CAN_OPERATION lds_hal_can;

#ifdef __cplusplus
}
#endif

#endif