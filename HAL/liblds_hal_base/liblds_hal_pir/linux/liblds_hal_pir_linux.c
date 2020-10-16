#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include "liblds_hal_pir_base.h"


/* Define  -------------------------------------------------------------------*/
struct LDS_PIR_CTX
{
	void			*ctx;
	char 			dev_name[64];
	LDS_PIR_ErrorNo	curr_err_state;
};

/* Define variable  ----------------------------------------------------------*/
static struct LDS_PIR_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/

/* Function prototype  -------------------------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int  lds_hal_pir_open(char *dev_name)
{
	memset(ctx, 0, sizeof(struct LDS_PIR_CTX));
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int  lds_hal_pir_close(int dev_fd)
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
static int  lds_hal_pir_start(void)
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
static int lds_hal_pir_stop(void)
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
static int  lds_hal_pir_init(void *param)
{
    ctx = (struct LDS_PIR_CTX*)malloc(sizeof(struct LDS_PIR_CTX));
    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_pir_deinit(void)
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
static int lds_hal_pir_get_error(void)
{
    return ctx->curr_err_state;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_hal_pir_control(LDS_CTRL_PIR type, ...)
{
	/* check maxctrl */
	if (type >= LDS_CTRL_PIR_MAX)
		return -1;

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
	.comm.lds_hal_open      = lds_hal_pir_open,
	.comm.lds_hal_close	    = lds_hal_pir_close,
	.comm.lds_hal_start     = lds_hal_pir_start,
	.comm.lds_hal_stop      = lds_hal_pir_stop,
	.comm.lds_hal_init      = lds_hal_pir_init,
	.comm.lds_hal_deinit    = lds_hal_pir_deinit,
	.comm.lds_hal_get_error = lds_hal_pir_get_error,
	.ioctl   	            = lds_hal_pir_control,
};