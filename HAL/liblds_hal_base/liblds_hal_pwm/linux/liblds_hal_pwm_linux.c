#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "liblds_hal_pwm_base.h"


/* Define  -------------------------------------------------------------------*/
struct LDS_PWM_CTX
{
	void			*ctx;
	char 		dev_name[64];
};

/* Define variable  ----------------------------------------------------------*/
struct LDS_PWM_CTX *ctx;
/* Define extern variable & function  ----------------------------------------*/

/* Function prototype  -------------------------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_pwm_open(char *dev_name)
{
	memset(ctx, 0, sizeof(struct LDS_PWM_CTX));
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_pwm_close(int dev_fd)
{
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_pwm_init(void *param)
{
    ctx = (struct LDS_PWM_CTX*)malloc(sizeof(struct LDS_PWM_CTX));
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_pwm_deinit(void)
{
    if(ctx){
        free(ctx);
        ctx = NULL;
    }
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_pwm_start(void)
{
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_pwm_stop(void)
{
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_pwm_control(LDS_CTRL_PWM type, ...)
{
	/* check maxctrl */
	if (type >= LDS_CTRL_PWM_MAX)
		return -1;

	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;
	while( cur_ctrl != LDS_CTRL_PWM_END )
	{
		switch(cur_ctrl)
		{
			case LDS_CTRL_PWM_SET_HZ:{
					int *parma = va_arg(ctrl, int *);
				}
				break;
			case LDS_CTRL_PWM_SET_VALUE:{
					int *parma = va_arg(ctrl, int *);
				}
				break;
			default:{
					printf("[ERROR]  %s::%d >>> Bad CTRL Value = [%d] \n", __FUNCTION__, __LINE__,cur_ctrl);
					assert((cur_ctrl >= LDS_CTRL_PWM_END) && (cur_ctrl < LDS_CTRL_PWM_MAX) );
				}
				break;
		}
		cur_ctrl = va_arg(ctrl, int);
	}
	va_end( ctrl );
	return 0;
}



struct LDS_PWM_OPERATION lds_hal_pwm = {
	.name 	            = "lds_hal_pwm",
	.comm.lds_hal_open  = lds_pwm_open,
	.comm.lds_hal_close	= lds_pwm_close,
	.comm.lds_hal_start = lds_pwm_start,
	.comm.lds_hal_stop  = lds_pwm_stop,
	.comm.lds_hal_init  = lds_pwm_init,
	.comm.lds_hal_deinit= lds_pwm_deinit,
	.ioctl   	        = lds_pwm_control,
};