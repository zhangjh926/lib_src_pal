//#define NDEBUG
#include <assert.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "liblds_hal_led_base.h"

/* Define  -------------------------------------------------------------------*/
struct LDS_LED_CTX
{
	void 	*ctx;
	int		blink_time;
};

#define SYSFS_LED_PATH			"/sys/class/leds"

static int active_low_set = 0;

/* Define variable  ----------------------------------------------------------*/
struct LDS_LED_CTX *ctx;
/* Define extern variable & function  ----------------------------------------*/

/* Function prototype  -------------------------------------------------------*/

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_led_blink(void* ctx_t, int pin_num)
{	
	struct LDS_LED_CTX *ctx;

	if( ctx_t == NULL )
		return -1;
	else
		ctx = ctx_t;
	
	int fd = 0; 
	int len = 0;
	char buf[65];

	memset(buf, 0, 65);

	// Check gpio num
	sprintf(buf, SYSFS_LED_PATH"/LED%d/brightness", pin_num);
//	printf("LED path = [%s] [%d]\n", buf, onoff_flag);

	if(access(buf, F_OK) == 0)
	{
		if( (fd = open(buf, O_WRONLY)) < 0)
		{
			printf("[ERROR] cannot open trigger\n");
			return -1;
		}
		len = snprintf(buf, sizeof(buf), "timer");
		if( write(fd, buf, len) < 0 )
		{
			printf("[ERROR] %s::%d >>> cannot write timer!\n", __FILE__, __LINE__);
			close(fd);
			return -1;
		}
		if(fd)
			close(fd);
	}
	else
	{
		printf("[ERROR] No %s file \n", buf);
		return -1;
	}

	sprintf(buf, SYSFS_LED_PATH"/LED%d/delay_off", pin_num);
	if(access(buf, F_OK) == 0)
	{
		if( (fd = open(buf, O_WRONLY)) < 0)
		{
			printf("[ERROR] cannot open delay_off\n");
			return -1;
		}
		len = snprintf(buf, sizeof(buf), "%d", ctx->blink_time);

		if( write(fd, buf, len) < 0 )
		{
			printf("[ERROR] cannot write delay_off file!\n");
			close(fd);
			return -1;
		}
		if(fd)
			close(fd);
	}
	else
	{
		printf("[ERROR] No %s file \n", buf);
		return -1;
	}

	sprintf(buf, SYSFS_LED_PATH"/LED%d/delay_on", pin_num);
	if(access(buf, F_OK) == 0)
	{
		if( (fd = open(buf, O_WRONLY)) < 0)
		{
			printf("[ERROR] cannot open delay_on\n");
			return -1;
		}
		len = snprintf(buf, sizeof(buf), "%d", ctx->blink_time);

		if( write(fd, buf, len) < 0 )
		{
			printf("[ERROR] cannot write delay_on file!\n");
			close(fd);
			return -1;
		}
		if(fd)
			close(fd);
	}
	else
	{
		printf("[ERROR] No %s file \n", buf);
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
static int lds_led_on(int pin_num)
{
	int fd = 0; 
	int len = 0;
	char buf[65];
	int	value;

	if(active_low_set == 0)
		value = 1;
	else if(active_low_set == 1)
		value = 0;
	else
		value = 1;

	memset(buf, 0, 65);
	// Check gpio num

	sprintf(buf, SYSFS_LED_PATH"/LED%d/brightness", pin_num);
//	printf("LED path = [%s] [%d]\n", buf, onoff_flag);

	if(access(buf, F_OK) == 0)
	{
		if( (fd = open(buf, O_WRONLY)) < 0)
		{
			printf("[ERROR] cannot open LED%d\n", pin_num);
			return -1;
		}

		value ^= 1;
		len = snprintf(buf, sizeof(buf), "%d", value);
		if( write(fd, buf, len) < 0 )
		{
			printf("[ERROR] cannot write LED%d brightness file!led_on 0 \n", pin_num);
			close(fd);
			return -1;
		}

		value ^= 1;
		len = snprintf(buf, sizeof(buf), "%d", value);
		if( write(fd, buf, len) < 0 )
		{
			printf("[ERROR] cannot write LED%d brightness file!led_on 1\n", pin_num);
			close(fd);
			return -1;
		}

		if(fd)
			close(fd);
	}
	else
	{
		printf("[ERROR] No %s file \n", buf);
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
static int lds_led_off(int pin_num)
{
	int fd = 0; 
	int len = 0;
	char buf[65];
	int	value;

	if(active_low_set == 0)
		value = 0;
	else if(active_low_set == 1)
		value = 1;
	else
		value = 0;

	memset(buf, 0, 65);
	// Check gpio num
	sprintf(buf, SYSFS_LED_PATH"/LED%d/brightness", pin_num);
//	printf("LED path = [%s] [%d]\n", buf, onoff_flag);

	if(access(buf, F_OK) == 0)
	{
		if( (fd = open(buf, O_WRONLY)) < 0)
		{
			printf("[ERROR] cannot open LED%d\n", pin_num);
			return -1;
		}

		len = snprintf(buf, sizeof(buf), "%d", value);
		if( write(fd, buf, len) < 0 )
		{
			printf("[ERROR] cannot write LED%d brightness file!nca_led_off\n", pin_num);
			close(fd);
			return -1;
		}
		if(fd)
			close(fd);
	}
	else
	{
		printf("[ERROR] No %s file \n", buf);
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
static int lds_led_open(char *dev_name)
{	
	memset( ctx, 0, sizeof(struct LDS_LED_CTX));
	
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_led_close(int dev_fd)
{
    close(dev_fd);
	return 0;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_led_init(void)
{
    ctx = (struct LDS_LED_CTX*)malloc(sizeof(struct LDS_LED_CTX));
    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_led_deinit(void)
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
static int lds_led_start(void)
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
static int lds_led_stop(void)
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
static unsigned int lds_led_read(unsigned char *data, unsigned int size)
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
static unsigned int lds_led_write(unsigned char *data, unsigned int size)
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
static int lds_led_control(LDS_CTRL_LED type, ...)
{
	/* check maxctrl */
	if (type >= LDS_CTRL_LED_MAX)
		return -1;

	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;
	while( cur_ctrl != LDS_CTRL_LED_END )
	{
		switch(cur_ctrl)
		{
			case LDS_CTRL_LED_ON:{
					int param = va_arg(ctrl, int);
					lds_led_on(param);
				}
				break;
	
			case LDS_CTRL_LED_OFF:{
					int param = va_arg(ctrl, int);
					lds_led_off(param);
				}
				break;
			case LDS_CTRL_LED_SET_BLINK_TIME:{
					int param = va_arg(ctrl, int);
					ctx->blink_time = param;
				}
				break;
			case LDS_CTRL_LED_BLINK:{
					int param = va_arg(ctrl, int);	
					lds_led_blink(ctx, param);
				}
				break;
			case LDS_CTRL_LED_ACTIVELOW_SET:{
					int param = va_arg(ctrl, int);
					active_low_set = param;
				}
				break;

			default:{
					//printf("[ERROR]  %s::%d >>> Bad CTRL Value = [%d] \n", cur_ctrl);
					assert((cur_ctrl >= LDS_CTRL_LED_END) && (cur_ctrl < LDS_CTRL_LED_MAX) );
				}
				break;

		}
		cur_ctrl = va_arg(ctrl, int);
	}
	va_end( ctrl );
	
	return 0;
}
struct LDS_LED_OPERATION lds_hal_led = {
		.name		    = "lds_hal_led",
		.ctxsize		= sizeof(struct LDS_LED_CTX),
		.maxctrl		= LDS_CTRL_LED_MAX,

		.comm.lds_hal_open	 = lds_led_open,
		.comm.lds_hal_close	 = lds_led_close,
		.comm.lds_hal_start  = lds_led_start,
		.comm.lds_hal_stop   = lds_led_stop,
		.comm.lds_hal_init   = lds_led_init,
		.comm.lds_hal_deinit = lds_led_deinit,
		.ioctl		         = lds_led_control,
};