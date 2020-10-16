#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "liblds_hal_gyro_base.h"


/* Define  -------------------------------------------------------------------*/
struct LDS_GYRO_CTX
{
	void			*ctx;
	char 			dev_name[64];
	LDS_DSP_ErrorNo	curr_err_state;
};

/* Define variable  ----------------------------------------------------------*/

struct LDS_GYRO_CTX *ctx;
/* Define extern variable & function  ----------------------------------------*/

/* Function prototype  -------------------------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_hal_gyro_open(char *dev_name)
{
	memset(ctx, 0, sizeof(struct LDS_GYRO_CTX));
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_hal_gyro_close(int dev_name)
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
static int lds_hal_gyro_start(void)
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
static int lds_hal_gyro_stop(void)
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
static int lds_hal_gyro_init(void *param)
{
    ctx = (struct LDS_GYRO_CTX*)malloc(sizeof(struct LDS_GYRO_CTX));
    return 0;

}

static int lds_hal_gyro_deinit(void)
{
    if(ctx){
        free(ctx);
        ctx = NULL;
    }
    return 0;

}

static int lds_hal_gyro_get_error(void)
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
static int	lds_hal_gyro_control(LDS_CTRL_GYRO type, ...)
{
	/* check maxctrl */
	if (type >= LDS_CTRL_GYRO_MAX)
		return -1;

	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;
	while( cur_ctrl != LDS_CTRL_GYRO_END )
	{
		switch(cur_ctrl)
		{
			case LDS_CTRL_GYRO_SET_CALIBRATION:{
					int *parma = va_arg(ctrl, int *);
				}
				break;
			default:{
					printf("[ERROR]  %s::%d >>> Bad CTRL Value = [%d] \n", __FUNCTION__, __LINE__,cur_ctrl);
					assert((cur_ctrl >= LDS_CTRL_GYRO_END) && (cur_ctrl < LDS_CTRL_GYRO_MAX) );
				}
				break;
		}
		cur_ctrl = va_arg(ctrl, int);
	}
	va_end( ctrl );
	return 0;
}

struct LDS_GYRO_OPERATION lds_hal_gyro = {
	.name 	            	= "lds_hal_gyro",
	.comm.lds_hal_open  	= lds_hal_gyro_open,
	.comm.lds_hal_close		= lds_hal_gyro_close,
	.comm.lds_hal_start 	= lds_hal_gyro_start,
	.comm.lds_hal_stop  	= lds_hal_gyro_stop,
	.comm.lds_hal_init  	= lds_hal_gyro_init,
	.comm.lds_hal_deinit	= lds_hal_gyro_deinit,
	.comm.lds_hal_get_error = lds_hal_gyro_get_error,
	.ioctl   	        	= lds_hal_gyro_control,
};