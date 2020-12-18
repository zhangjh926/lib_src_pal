#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include "liblds_hal_pir_base.h"


/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/
static LDS_PIR_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/

/* Function prototype  -------------------------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int  lds_hal_pir_open(void *ctx_t, void *param)
{
	if(NULL == ctx_t) return -1;
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
static int  lds_hal_pir_close(void *ctx_t)
{
	if(NULL == ctx_t) return -1;
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
static int  lds_hal_pir_start(void *ctx_t)
{
	if(NULL == ctx_t) return -1;
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
static int lds_hal_pir_stop(void *ctx_t)
{
	if(NULL == ctx_t) return -1;
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
static int  lds_hal_pir_init(void *param)
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
static int lds_hal_pir_deinit(void *ctx_t)
{
	if(NULL == ctx_t) return -1;
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
static int lds_hal_pir_get_error(void *ctx_t)
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
static int	lds_hal_pir_control(LDS_PIR_CTX *ctx, LDS_CTRL_PIR type, ...)
{
	/* check maxctrl */
	if (type >= LDS_CTRL_PIR_MAX)
		return -1;
	if(NULL == ctx) return -1;

	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;
	while( cur_ctrl != LDS_CTRL_PIR_END )
	{
		switch(cur_ctrl)
		{
			case LDS_CTRL_PIR_SET_INTERRUPT:{
					int *parma = va_arg(ctrl, int *);
				}
				break;
			case LDS_CTRL_PIR_SET_CALLBACK:{
					int *parma = va_arg(ctrl, int *);
				}
				break;
			default:{
					printf("[ERROR]  %s::%d >>> Bad CTRL Value = [%d] \n", __FUNCTION__, __LINE__,cur_ctrl);
					assert((cur_ctrl >= LDS_CTRL_PIR_END) && (cur_ctrl < LDS_CTRL_PIR_MAX) );
				}
				break;
		}
		cur_ctrl = va_arg(ctrl, int);
	}
	va_end( ctrl );
	return 0;
}



struct LDS_PIR_OPERATION lds_hal_pir = {
	.name 	                = "lds_hal_pir",
	.base.lds_hal_open      = lds_hal_pir_open,
	.base.lds_hal_close	    = lds_hal_pir_close,
	.base.lds_hal_start     = lds_hal_pir_start,
	.base.lds_hal_stop      = lds_hal_pir_stop,
	.base.lds_hal_get_error = lds_hal_pir_get_error,
	.ioctl   	            = lds_hal_pir_control,
};