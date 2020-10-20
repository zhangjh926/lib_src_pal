#ifndef _LDS_BLUETOOTH_OPERATION_H
#define _LDS_BLUETOOTH_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   	_LDS_BLUETOOTH_ErrorNo{
	LDS_BLUETOOTH_OPEN_ERROR,
	LDS_BLUETOOTH_INIT_ERROR,
	LDS_BLUETOOTH_START_ERROR,

	LDS_BLUETOOTH_BLE_BIND_FAIL,
	LDS_BLUETOOTH_BLE_PAIR_FAIL,

	LDS_BLUETOOTH_SOUND_BIND_FAIL,
	LDS_BLUETOOTH_SOUND_PAIR_FAIL,
}LDS_BLUETOOTH_ErrorNo;

typedef enum	_LDS_BLE_STATE{
	LDS_BLE_PAIRING,
	LDS_BLE_PAIR_SUCCESS,
	LDS_BLE_PAIR_FAIL,
}LDS_BLE_STATE;

typedef enum	_LDS_SOUND_STATE{
	LDS_SOUND_PAIRING,
	LDS_SOUND_PAIR_SUCCESS,
	LDS_SOUND_PAIR_FAIL,
}LDS_SOUND_STATE;

typedef enum	_LDS_BLUETOOTH_MODE{
	LDS_BLUETOOTH_BLE_MODE,
	LDS_BLUETOOTH_SOUND_MODE,
	LDS_BLUETOOTH_NETWORK_MODE,
}LDS_BLUETOOTH_MODE;

struct LDS_BLUETOOTH_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    // int     (*ioctl)(LDS_CTRL_BLUETOOTH, ...);
	int		(*lds_hal_set_work_mode)(LDS_BLUETOOTH_MODE bluetooth_mode);
	int		(*lds_hal_set_ble_uuid)(char *uuid);
	int		(*lds_hal_set_ble_model_name)(char *model_name);

	int		(*lds_hal_ble_bind)(void);
	int		(*lds_hal_ble_unbind)(void);
	int		(*lds_hal_ble_start_advertise)(void);
	int		(*lds_hal_ble_get_state)(LDS_BLUETOOTH_MODE bluetooth_mode);
	int		(*lds_hal_ble_mesh_enable)(int onoff);

	int		(*lds_hal_ble_send_data)(char *send_data);
	int		(*lds_hal_ble_recv_data)(char* recv_data);

};

extern struct LDS_BLUETOOTH_OPERATION lds_hal_bluetooth;

#ifdef __cplusplus
}
#endif

#endif