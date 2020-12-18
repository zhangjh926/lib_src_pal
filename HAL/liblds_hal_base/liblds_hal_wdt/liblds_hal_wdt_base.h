#ifndef __IO_LDS_WATCHDOG_H__
#define __IO_LDS_WATCHDOG_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_WDT_ErrorNo{
	LDS_WDT_OPEN_ERROR,
	LDS_WDT_INIT_ERROR,
	LDS_WDT_START_ERROR,
}LDS_WDT_ErrorNo;

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

typedef struct _LDS_WATCHDOG_CTX
{
    char            dev_name[64];
	int			    fd;
	int			    open_status;
	LDS_WDT_ErrorNo	curr_err_state;
}LDS_WATCHDOG_CTX;

struct LDS_WATCHDOG_OPERATION
{
    struct LDS_HAL_COMMON base;
	const char		*name;

	/* common function */
	int				(*ioctl)		(LDS_WATCHDOG_CTX *ctx, LDS_CTRL_WATCHDOG type, ...);
};

/* Define variable  -----------------------------------------------------*/
extern struct LDS_WATCHDOG_OPERATION lds_hal_wdt;

/* Define extern variable & function  -----------------------------------*/

#ifdef __cplusplus
}
#endif

#endif

