#ifndef __IO_LDS_PWM_H__
#define __IO_LDS_PWM_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "lds_hal_common.h"
/* Header file include --------------------------------------------------*/
typedef enum   _LDS_PWM_ErrorNo{
	LDS_PWM_OPEN_ERROR,
	LDS_PWM_INIT_ERROR,
	LDS_PWM_START_ERROR,
}LDS_PWM_ErrorNo;

/* Define  --------------------------------------------------------------*/
typedef enum tagRTC_CTRL
{
	LDS_CTRL_PWM_END,
	LDS_CTRL_PWM_SET_HZ,
	LDS_CTRL_PWM_SET_VALUE,
	LDS_CTRL_PWM_MAX
}LDS_CTRL_PWM;

typedef struct _LDS_PWM_CTX
{
	char 			dev_name[64];
	int 			dev_fd;
	LDS_PWM_ErrorNo curr_err_state;
}LDS_PWM_CTX;


struct LDS_PWM_OPERATION
{
    struct LDS_HAL_COMMON base;
	const char		*name;

	/* common function */
	int				(*ioctl)		(LDS_PWM_CTX *ctx, LDS_CTRL_PWM type, ...);

	/* component dependent fuction */
};

/* Define variable  -----------------------------------------------------*/
extern struct LDS_PWM_OPERATION lds_hal_pwm;

/* Define extern variable & function  -----------------------------------*/

#ifdef __cplusplus
}
#endif

#endif 