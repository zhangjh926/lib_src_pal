#ifndef __IO_LDS_RTC_H__
#define __IO_LDS_RTC_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_RTC_ErrorNo{
	LDS_RTC_OPEN_ERROR,
	LDS_RTC_INIT_ERROR,
	LDS_RTC_START_ERROR,
}LDS_RTC_ErrorNo;

/* Define  --------------------------------------------------------------*/
typedef enum tagRTC_CTRL
{
	LDS_CTRL_RTC_END,
	LDS_CTRL_RTC_VALUE_SET,
	LDS_CTRL_RTC_SET,
	LDS_CTRL_RTC_TIME_GET,
	LDS_CTRL_RTC_MAX
}LDS_CTRL_RTC;

struct LDS_RTC_OPERATION
{
    struct LDS_HAL_COMMON comm;
	const char		*name;
	int				ctxsize;
	int				maxctrl;

	/* common function */
	int				(*ioctl)		(LDS_CTRL_RTC type, ...);

	/* component dependent fuction */
};

/* Define variable  -----------------------------------------------------*/
extern struct LDS_RTC_OPERATION lds_hal_rtc;

/* Define extern variable & function  -----------------------------------*/

#ifdef __cplusplus
}
#endif

#endif 

