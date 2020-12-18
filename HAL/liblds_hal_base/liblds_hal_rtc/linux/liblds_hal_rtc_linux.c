/* Header file include -------------------------------------------------------*/
//#define NDEBUG
#include <assert.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

#include "liblds_hal_rtc_base.h"

/* Define  -------------------------------------------------------------------*/

/* Define variable  ----------------------------------------------------------*/
static LDS_RTC_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/

/* Function prototype  -------------------------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_rtc_time_get(struct tm *get_time)
{
	time_t current_time;
	
	time(&current_time);
	localtime_r(&current_time, get_time);

/*	
	get_time->tm_sec = 0;
	get_time->tm_min = 0;
	get_time->tm_hour = 0;
	get_time->tm_mday = 0;
	get_time->tm_mon = 0;
	get_time->tm_year = 0;
	get_time->tm_wday = 0;
	get_time->tm_yday = 0;
	get_time->tm_isdst = 0;
*/
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_rtc_time_set_value(struct tm *set_time)
{
	struct timeval 	tv;
	time_t time;
	int 	   ret;

	time = mktime(set_time);

	tv.tv_sec = time;
	tv.tv_usec = 0;

	settimeofday( &tv, NULL );

	ret = system("/sbin/hwclock -w");//set hardware clock frome system clock
	
	ret = system("date");
	return ret;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_rtc_time_set()
{
	int ret = -1;
	ret = system("/sbin/hwclock -w");//set hardware clock frome system clock
	if( (ret == 127) || (ret == -1) )
	{
		return -1;
	}
	
	ret = system("date");
	if( (ret == 127) || (ret == -1) )
	{
		return -1;
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
static int lds_hal_rtc_open(void *ctx_t, void *param)
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
static int lds_hal_rtc_close(void *ctx_t)
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
static int lds_hal_rtc_init( void *param)
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
static int lds_hal_rtc_deinit( void *ctx_t)
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
static int lds_hal_rtc_start( void *ctx_t )
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
static int lds_hal_rtc_stop( void *ctx_t )
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
static unsigned int lds_hal_rtc_read(unsigned char *data, unsigned int size)
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
static unsigned int lds_hal_rtc_write(unsigned char *data, unsigned int size)
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
static  int 		lds_hal_rtc_get_error(void *ctx_t)
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
static int lds_hal_rtc_control(LDS_RTC_CTX *ctx, LDS_CTRL_RTC type, ...)
{
	/* check maxctrl */
	if (type >= LDS_CTRL_RTC_MAX)
		return -1;

	if(NULL == ctx) return -1;
	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;
	while( cur_ctrl != LDS_CTRL_RTC_END )
	{
		switch(cur_ctrl)
		{
			case LDS_CTRL_RTC_VALUE_SET:
				{
					struct tm *param = va_arg(ctrl, struct tm *);
					lds_hal_rtc_time_set_value(param);
				}
				break;
			case LDS_CTRL_RTC_SET:
				{
					int *parma = va_arg(ctrl, int *);
					*parma = lds_hal_rtc_time_set();
				}
				break;
			case LDS_CTRL_RTC_TIME_GET:
				{
					struct tm *param = va_arg(ctrl, struct tm *);
					lds_hal_rtc_time_get(param);
				}
				break;

			default:
				{
					printf("[ERROR]  %s::%d >>> Bad CTRL Value = [%d] \n", __FUNCTION__, __LINE__,cur_ctrl);
					assert((cur_ctrl >= LDS_CTRL_RTC_END) && (cur_ctrl < LDS_CTRL_RTC_MAX) );
				}
				break;
		}
		cur_ctrl = va_arg(ctrl, int);
	}
	va_end( ctrl );
	
	return 0;
}
struct LDS_RTC_OPERATION lds_hal_rtc = {
	.name		        	= "lds_hal_rtc",
	.base.lds_hal_open		= lds_hal_rtc_open,
	.base.lds_hal_close		= lds_hal_rtc_close,
	.base.lds_hal_start 	= lds_hal_rtc_start,
	.base.lds_hal_stop  	= lds_hal_rtc_stop,
	.base.lds_hal_get_error = lds_hal_rtc_get_error,
	.ioctl		        	= lds_hal_rtc_control,

};

