#ifndef __IO_LDS_PTZ_H__
#define __IO_LDS_PTZ_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif

/* Header file include --------------------------------------------------*/

typedef enum   _LDS_PTZ_ErrorNo{
	LDS_PTZ_OPEN_ERROR,
	LDS_PTZ_INIT_ERROR,
	LDS_PTZ_START_ERROR,
}LDS_PTZ_ErrorNo;

/* Define  --------------------------------------------------------------*/
typedef enum tagRTC_CTRL
{
	LDS_CTRL_PTZ_END,
	LDS_CTRL_PTZ_SET_SPEED,
	LDS_CTRL_PTZ_SET_STEP,
	LDS_CTRL_PTZ_GET_STEP,
	LDS_CTRL_PTZ_MAX
}LDS_CTRL_PTZ;

typedef struct _LDS_PTZ_CTX
{
	char 			dev_name[64];
	int 			dev_fd;
	LDS_PTZ_ErrorNo	curr_err_state;
}LDS_PTZ_CTX;

struct LDS_PTZ_OPERATION
{
    struct LDS_HAL_COMMON base;
	const char		*name;

	/* common function */
	int				(*ioctl)		(LDS_PTZ_CTX *ctx, LDS_CTRL_PTZ type, ...);

	/* component dependent fuction */
};

/* Define variable  -----------------------------------------------------*/
extern struct LDS_PTZ_OPERATION lds_hal_ptz;

/* Define extern variable & function  -----------------------------------*/

#ifdef __cplusplus
}
#endif

#endif 