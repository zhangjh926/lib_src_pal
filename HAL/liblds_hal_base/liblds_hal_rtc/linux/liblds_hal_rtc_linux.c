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
struct LDS_RTC_CTX
{
	void			*ctx;
	char 		dev_name[64];
};

/* Define variable  ----------------------------------------------------------*/
struct LDS_RTC_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/

/* Function prototype  -------------------------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_rtc_time_get(struct tm *get_time)
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
static int lds_rtc_time_set_value(struct tm *set_time)
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
static int lds_rtc_time_set()
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
static int lds_rtc_open(char *dev_name)
{
	memset(ctx, 0, sizeof(struct LDS_RTC_CTX));
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_rtc_close( int dev_fd )
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
static int lds_rtc_init( void )
{
    ctx = (struct LDS_RTC_CTX *)malloc(sizeof(struct LDS_RTC_CTX));
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_rtc_deinit( void )
{
    if(ctx){
        free(ctx);
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
static int lds_rtc_start( void )
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
static int lds_rtc_stop( void )
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
static unsigned int lds_rtc_read(unsigned char *data, unsigned int size)
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
static unsigned int lds_rtc_write(unsigned char *data, unsigned int size)
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
static int lds_rtc_control(LDS_CTRL_RTC type, ...)
{
	/* check maxctrl */
	if (type >= LDS_CTRL_RTC_MAX)
		return -1;

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
					lds_rtc_time_set_value(param);
				}
				break;
			case LDS_CTRL_RTC_SET:
				{
					int *parma = va_arg(ctrl, int *);
					*parma = lds_rtc_time_set();
				}
				break;
			case LDS_CTRL_RTC_TIME_GET:
				{
					struct tm *param = va_arg(ctrl, struct tm *);
					lds_rtc_time_get(param);
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
		.name		        = "lds_hal_rtc",
		.ctxsize		    = sizeof(struct LDS_RTC_CTX),
		.maxctrl		    = LDS_CTRL_RTC_MAX,

		.comm.lds_hal_open	= lds_rtc_open,
		.comm.lds_hal_close	= lds_rtc_close,
		.comm.lds_hal_start = lds_rtc_start,
		.comm.lds_hal_stop  = lds_rtc_stop,
		.comm.lds_hal_init  = lds_rtc_init,
		.comm.lds_hal_deinit= lds_rtc_deinit,
		.ioctl		        = lds_rtc_control,

};

