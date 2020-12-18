#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/watchdog.h>

#include "liblds_hal_wdt_base.h"


/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/
static LDS_WATCHDOG_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/

/* Function prototype  -------------------------------------------------------*/

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int _wdt_start( int fd )
{
	int ret = -1;
    int flags = WDIOS_ENABLECARD;

	if( fd )
	{
		if( ioctl( fd, WDIOC_SETOPTIONS, &flags ) != 0 )
		{
			fprintf(stderr, ">>ERROR WdtStop!n");
			return ret;
		}
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
static int _wdt_stop( int fd )
{
	int ret = -1;
    int flags = WDIOS_DISABLECARD;

	if( fd )
	{
		if( ioctl( fd, WDIOC_SETOPTIONS, &flags ) != 0 )
		{
			fprintf(stderr, ">>ERROR WdtStop!n");
			return ret;
		}
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
static int _wdt_set_time( int fd , int time)
{
	int ret = -1;

	if( fd )
	{
		if( ioctl( fd, WDIOC_SETTIMEOUT, &time ) != 0 )
		{
			fprintf(stderr, ">>ERROR WdtSetTime!n");
			return ret;
		}
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
static int _wdt_get_time( int fd )
{
	int ret = -1;

	if( fd )
	{
		if( ioctl( fd, WDIOC_GETTIMEOUT, &ret ) != 0 )
		{
			fprintf(stderr, ">>ERROR WdtGetTime!n");
			return ret;
		}
	}

	return ret;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int _wdt_alive( int fd )
{
	if( fd )
	{
		if( ioctl( fd, WDIOC_KEEPALIVE, 0 ) != 0 )
		{
			printf("[ERROR] keep alive!\n");
			return -1;
		}
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
static int 			watchdog_dev_open( void *ctx_t)
{
	if( ctx_t == NULL )
		return -1;
	else
		ctx = ctx_t;

	ctx->open_status = -1;

	ctx->fd = open(ctx->dev_name, O_WRONLY);
	if (ctx->fd < 0) 
	{
		printf("Watchdog device not enabled.\n");
		return -1;
	}

	ctx->open_status = 1;

	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int 			lds_hal_wdt_open( void *ctx_t, void *param )
{   
    if(NULL == ctx_t){
        return -1;
    }else ctx = ctx_t;
    
	watchdog_dev_open(ctx_t);

	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int 			lds_hal_wdt_close( void *ctx_t )
{
	if(NULL == ctx_t) return -1;
	else ctx = ctx_t;

	if(ctx->open_status)
		close(ctx->fd);

	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int 			lds_hal_wdt_start( void *ctx_t )
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
static int 			lds_hal_wdt_stop( void *ctx_t)
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
static int 			lds_hal_wdt_init( void *param)
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
static int 			lds_hal_wdt_deinit( void *ctx_t)
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
static unsigned int lds_hal_wdt_read( unsigned char *data, unsigned int size)
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
static unsigned int lds_hal_wdt_write( unsigned char *data, unsigned int size)
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
static int lds_hal_wdt_get_error( void *ctx_t)
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
static int 			lds_hal_wdt_control(LDS_WATCHDOG_CTX *ctx, LDS_CTRL_WATCHDOG type, ...)
{
	/* check maxctrl */
	if (type >= LDS_CTRL_WATCHDOG_MAX)
		return -1;
	if(NULL == ctx) return -1;

	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;
	while( cur_ctrl != LDS_CTRL_WATCHDOG_END )
	{
		switch(cur_ctrl)
		{
			case LDS_CTRL_WATCHDOG_DISABLE:
				{
					int status = va_arg(ctrl, int);

					if(status)
						_wdt_stop(ctx->fd);
				}
				break;
				
			case LDS_CTRL_WATCHDOG_ENABLE:
				{
					int status = va_arg(ctrl, int);

					if(status)
						_wdt_start(ctx->fd);
				}
				break;
				
			case LDS_CTRL_WATCHDOG_SET_TIME:
				{
					int time = va_arg(ctrl, int);
					_wdt_set_time(ctx->fd, time);
				}
				break;
				
			case LDS_CTRL_WATCHDOG_GET_TIME:
				{
					int *wdt_time_sec = va_arg(ctrl, int *);
					*wdt_time_sec = _wdt_get_time(ctx->fd);
				}
				break;
				
			case LDS_CTRL_WATCHDOG_SET_ALIVE:{
					int *param = va_arg(ctrl, int *);
					*param = _wdt_alive(ctx->fd);
				}
				break;
		}
		cur_ctrl = va_arg(ctrl, int);
	}
	va_end( ctrl );
	
	return 0;
}

struct LDS_WATCHDOG_OPERATION lds_hal_wdt = {
	.name			    	= "lds_hal_watchdog",
	.base.lds_hal_open		= lds_hal_wdt_open,
	.base.lds_hal_close		= lds_hal_wdt_close,
	.base.lds_hal_start 	= lds_hal_wdt_start,
	.base.lds_hal_stop  	= lds_hal_wdt_stop,
	.base.lds_hal_get_error = lds_hal_wdt_get_error,
	.ioctl	            	= lds_hal_wdt_control,
};

