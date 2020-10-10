#ifndef __IO_LDS_PWM_H__
#define __IO_LDS_PWM_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "lds_hal_common.h"
/* Header file include --------------------------------------------------*/

/* Define  --------------------------------------------------------------*/
typedef enum tagRTC_CTRL
{
	LDS_CTRL_PWM_END,
	LDS_CTRL_PWM_SET_HZ,
	LDS_CTRL_PWM_SET_VALUE,
	LDS_CTRL_PWM_MAX
}LDS_CTRL_PWM;

struct LDS_PWM_OPERATION
{
    struct LDS_HAL_COMMON comm;
	const char		*name;

	/* common function */
	int				(*ioctl)		(LDS_CTRL_PWM type, ...);

	/* component dependent fuction */
};

/* Define variable  -----------------------------------------------------*/
extern struct LDS_PWM_OPERATION lds_hal_pwm;

/* Define extern variable & function  -----------------------------------*/

#ifdef __cplusplus
}
#endif

#endif 