#ifndef __IO_LDS_WATCHDOG_H__
#define __IO_LDS_WATCHDOG_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif

/* Header file include --------------------------------------------------*/

/* Define  --------------------------------------------------------------*/
typedef enum tagWATCHDOG_CTRL
{
	LDS_CTRL_WATCHDOG_END,
	LDS_CTRL_WATCHDOG_DISABLE,
	LDS_CTRL_WATCHDOG_ENABLE,
	LDS_CTRL_WATCHDOG_SET_TIME,
	LDS_CTRL_WATCHDOG_GET_TIME,
	LDS_CTRL_WATCHDOG_SET_ALIVE,
	LDS_CTRL_WATCHDOG_MAX
}LDS_CTRL_WATCHDOG;

struct LDS_WATCHDOG_OPERATION
{
    struct LDS_HAL_COMMON comm;
	const char		*name;
	int				ctxsize;
	int				maxctrl;

	/* common function */
	int				(*ioctl)		(LDS_CTRL_WATCHDOG type, ...);
};

/* Define variable  -----------------------------------------------------*/
extern struct LDS_WATCHDOG_OPERATION lds_hal_wdt;

/* Define extern variable & function  -----------------------------------*/

#ifdef __cplusplus
}
#endif

#endif

