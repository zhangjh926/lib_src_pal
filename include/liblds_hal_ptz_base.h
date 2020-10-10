#ifndef __IO_LDS_PTZ_H__
#define __IO_LDS_PTZ_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif

/* Header file include --------------------------------------------------*/

/* Define  --------------------------------------------------------------*/
typedef enum tagRTC_CTRL
{
	LDS_CTRL_PTZ_END,
	LDS_CTRL_PTZ_SET_SPEED,
	LDS_CTRL_PTZ_SET_STEP,
	LDS_CTRL_PTZ_GET_STEP,
	LDS_CTRL_PTZ_MAX
}LDS_CTRL_PTZ;

/*
**ioctl
** 
**
*/
struct LDS_PTZ_OPERATION
{
    struct LDS_HAL_COMMON comm;
	const char		*name;

	/* common function */
	int				(*ioctl)		( LDS_CTRL_PTZ type, ...);

	/* component dependent fuction */
};

/* Define variable  -----------------------------------------------------*/
extern struct LDS_PTZ_OPERATION lds_hal_ptz;

/* Define extern variable & function  -----------------------------------*/

#ifdef __cplusplus
}
#endif

#endif 