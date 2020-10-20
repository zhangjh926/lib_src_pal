#ifndef _LDS_NFC_OPERATION_H
#define _LDS_NFC_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_NFC_ErrorNo{
	LDS_NFC_OPEN_ERROR,
	LDS_NFC_INIT_ERROR,
	LDS_NFC_START_ERROR,
}LDS_NFC_ErrorNo;

typedef enum _NFCState{
	LDS_NFC_STATE_CONNECTED,
	LDS_NFC_STATE_DISCONNECT,
}NFCState;

struct LDS_NFC_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    // int     (*ioctl)(LDS_CTRL_ETH, ...);
	int		(*lds_hal_set_nfc_enable)(int onoff);
	int		(*lds_hal_nfc_identification)(void);
	int		(*lds_hal_nfc_send_data)(char *send_data);
	int		(*lds_hal_nfc_recv_data)(char *recv_data);
};

extern struct LDS_NFC_OPERATION lds_hal_nfc;

#ifdef __cplusplus
}
#endif

#endif