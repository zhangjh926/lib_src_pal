#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "liblds_hal_gyro_base.h"


/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/

static LDS_GYRO_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/

/* Function prototype  -------------------------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_hal_gyro_open(void *ctx_t,void *param)
{
	if(NULL == ctx_t ) return -1;
	else ctx = ctx_t;

	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_hal_gyro_close(void *ctx_t)
{
	if(NULL == ctx_t ) return -1;
	else ctx = ctx_t;

	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_gyro_start(void *ctx_t)
{
	if(NULL == ctx_t ) return -1;
	else ctx = ctx_t;

    return 0;

}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_gyro_stop(void *ctx_t)
{
	if(NULL == ctx_t ) return -1;
	else ctx = ctx_t;

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
    return 0;

}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_gyro_deinit(void *ctx_t)
{
	if(NULL == ctx_t ) return -1;
	else ctx = ctx_t;

    return 0;

}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_gyro_get_error(void *ctx_t)
{
	if(NULL == ctx_t) return -1;
	else ctx = ctx_t;

    return ctx->curr_err_state;

}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_hal_gyro_control(LDS_GYRO_CTX * ctx_t, LDS_CTRL_GYRO type, ...)
{
	/* check maxctrl */
	if (type >= LDS_CTRL_GYRO_MAX)
		return -1;

	if(NULL == ctx_t) return -1;
	else ctx = ctx_t;

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
	.base.lds_hal_open  	= lds_hal_gyro_open,
	.base.lds_hal_close		= lds_hal_gyro_close,
	.base.lds_hal_start 	= lds_hal_gyro_start,
	.base.lds_hal_stop  	= lds_hal_gyro_stop,
	.base.lds_hal_get_error = lds_hal_gyro_get_error,
	.ioctl   	        	= lds_hal_gyro_control,
};