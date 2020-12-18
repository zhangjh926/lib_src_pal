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

typedef struct _LDS_NFC_CTX{
	char dev_name[128];
	int  dev_fd;
    LDS_NFC_ErrorNo curr_err_state;
}LDS_NFC_CTX;


struct LDS_NFC_OPERATION
{
    struct  LDS_HAL_COMMON base;    
	const   char		  *name;

    // int     (*ioctl)(LDS_CTRL_ETH, ...);
	int		(*lds_hal_set_nfc_enable)(LDS_NFC_CTX *ctx, int onoff);
	int		(*lds_hal_nfc_identification)(LDS_NFC_CTX *ctx);
	int		(*lds_hal_nfc_send_data)(LDS_NFC_CTX *ctx, char *send_data);
	int		(*lds_hal_nfc_recv_data)(LDS_NFC_CTX *ctx, char *recv_data);
};

extern struct LDS_NFC_OPERATION lds_hal_nfc;

#ifdef __cplusplus
}
#endif

#endif