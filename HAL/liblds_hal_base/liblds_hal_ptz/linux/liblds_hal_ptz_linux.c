#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "liblds_hal_ptz_base.h"


/* Define  -------------------------------------------------------------------*/
struct LDS_PTZ_CTX
{
	void			*ctx;
	char 		dev_name[64];
};

/* Define variable  ----------------------------------------------------------*/
struct LDS_PTZ_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/

/* Function prototype  -------------------------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_ptz_open(char * dev_name)
{
	memset(ctx, 0, sizeof(struct LDS_PTZ_CTX));
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_ptz_close(int dev_fd)
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
static int	lds_ptz_init(void)
{
    ctx = (struct LDS_PTZ_CTX *)malloc(sizeof(struct LDS_PTZ_CTX));
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int	lds_ptz_deinit(void)
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
static int	lds_ptz_start(void)
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
static int	lds_ptz_stop(void)
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
static int	lds_ptz_control(LDS_CTRL_PTZ type, ...)
{
	/* check maxctrl */
	if (type >= LDS_CTRL_PTZ_MAX)
		return -1;

	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;
	while( cur_ctrl != LDS_CTRL_PTZ_END )
	{
		switch(cur_ctrl)
		{
			case LDS_CTRL_PTZ_SET_SPEED:{
					int *parma = va_arg(ctrl, int *);
				}
				break;
			case LDS_CTRL_PTZ_SET_STEP:{
					int *parma = va_arg(ctrl, int *);
				}
				break;
			case LDS_CTRL_PTZ_GET_STEP:{
					int *parma = va_arg(ctrl, int *);
				}
				break;
			default:{
					printf("[ERROR]  %s::%d >>> Bad CTRL Value = [%d] \n", __FUNCTION__, __LINE__,cur_ctrl);
					assert((cur_ctrl >= LDS_CTRL_PTZ_END) && (cur_ctrl < LDS_CTRL_PTZ_MAX) );
				}
				break;
		}
		cur_ctrl = va_arg(ctrl, int);
	}
	va_end( ctrl );
	return 0;
}



struct LDS_PTZ_OPERATION lds_hal_ptz = {
	.name 	                = "lds_hal_ptz",
	.comm.lds_hal_open  	= lds_ptz_open,
	.comm.lds_hal_close	    = lds_ptz_close,
	.comm.lds_hal_start     = lds_ptz_start,
	.comm.lds_hal_stop      = lds_ptz_stop,
	.comm.lds_hal_init      = lds_ptz_init,
	.comm.lds_hal_deinit    = lds_ptz_deinit,
	.ioctl   	            = lds_ptz_control,
};