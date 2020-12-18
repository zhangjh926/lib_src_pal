#ifndef __IO_LDS_GYRO_H__
#define __IO_LDS_GYRO_H__

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Header file include --------------------------------------------------*/

typedef enum   _LDS_GYRO_ErrorNo{
	LDS_GYRO_OPEN_ERROR,
	LDS_GYRO_INIT_ERROR,
	LDS_GYRO_START_ERROR,
}LDS_DSP_ErrorNo;

/* Define  --------------------------------------------------------------*/
typedef enum tagRTC_CTRL
{
	LDS_CTRL_GYRO_END,
	LDS_CTRL_GYRO_SET_CALIBRATION,
	LDS_CTRL_GYRO_MAX
}LDS_CTRL_GYRO;

typedef struct _LDS_GYRO_CTX
{
	char 			dev_name[64];
	int 			dev_fd;
	LDS_DSP_ErrorNo	curr_err_state;
}LDS_GYRO_CTX;

struct LDS_GYRO_OPERATION
{
    struct LDS_HAL_COMMON base;
	const char		     *name;

	/* common function */
	int				(*ioctl)		(LDS_GYRO_CTX *ctx_t, LDS_CTRL_GYRO type, ...);

	/* component dependent fuction */
};

/* Define variable  -----------------------------------------------------*/
extern struct LDS_GYRO_OPERATION lds_hal_gyro;

/* Define extern variable & function  -----------------------------------*/


#ifdef __cplusplus
}
#endif
#endif 