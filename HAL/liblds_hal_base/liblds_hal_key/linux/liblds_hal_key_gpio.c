//#define NDEBUG
#include <assert.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>
#include <stdarg.h>
#include <linux/input.h>

#include "liblds_hal_gpio_base.h"
#include "liblds_hal_key_base.h"

/* Define  -------------------------------------------------------------------*/
#define SW3_PIN				GPIOC6
#define SW4_PIN				GPIOC7
#define SW5_PIN				GPIOC4
#define SW6_PIN				GPIOC5

#define MAX_KEY_COUNT		4

struct LDS_KEY_INFO
{
	void*	ctx;
	int		pin;
	int		direction;
	int		pin_map;
    int     fd;
};

struct LDS_KEY_CTX
{
	struct LDS_KEY_INFO	info[MAX_KEY_COUNT];
	int					(*callback)(int, int);
	int					intaval;
	int					thread_start;
	int					monitoring_start;
	pthread_t			pthread;
	LDS_KEY_ErrorNo		curr_err_state;
}; 

/* Define variable  ----------------------------------------------------------*/
static struct LDS_KEY_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/
static int s_key_val, s_long_key, s_long_cnt;

/* Function prototype  -------------------------------------------------------*/
/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_key_read(void *ctx_t)
{
	int get_value = 1;
	int ret = 0;
	int i = 0;

 	struct LDS_KEY_CTX *ctx;
	if( ctx_t == NULL)
		return 0;
	else
		ctx = ctx_t;	
	
	for(i = 0; i < MAX_KEY_COUNT; i++)
	{
		lds_hal_gpio.ioctl(
			LDS_CTRL_GPIO_GET_VALUE, &get_value,
			LDS_CTRL_GPIO_END);
		
		if(!get_value)
		{
			ret = ctx->info[i].pin_map;
			break;
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
static void *t_key_monitoring( void *ctx_t )
{
	struct LDS_KEY_CTX *ctx;
	if( ctx_t == NULL)
		return 0;
	else
		ctx = ctx_t;	

	ctx->thread_start = 1;
	while(ctx->thread_start)
	{
		int key = 0;
		int status = -1;

		while(!ctx->monitoring_start)
			sleep(1);

		key = lds_hal_key_read(ctx);
		if(key)
		{
			if( s_long_key && s_key_val == 0 )
			{
				goto END;
			}
			else if( key == s_key_val )
			{
				if( s_long_cnt++ > 30 )
				{
					s_key_val	= 0;
					s_long_cnt	= 0;
					s_long_key	= 1;
				}
				else
				{
					s_key_val = key;
					goto END;
				}
			}
			else
			{
				s_key_val = key;
				goto END;
			}
		}
		else if( s_key_val && !key && !s_long_key )
		{
			key = s_key_val;
			s_key_val = 0;
			status = LDS_CTRL_KEY_PRESS;
		}
		else
		{
			s_key_val	= 0;
			s_long_cnt	= 0;
			s_long_key	= 0;
			goto END;
		}

		if(s_long_key)
		{
			status = LDS_CTRL_KEY_PRESSING;
		}
		
		ctx->callback(key, status);
END:
		usleep(ctx->intaval);
	}
}
/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_set_key_pin(void* ctx_t, int count)
{
	struct LDS_KEY_CTX *ctx;
	if( ctx_t == NULL)
		return -1;
	else
		ctx = ctx_t;
	
	ctx->info[count].ctx = malloc( lds_hal_gpio.ctxsize);
	
	if( ctx->info[count].ctx == NULL )
	{
		printf("[ERROR] KEY malloc faile : ctx \n");
		return -1;
	}
	
	lds_hal_gpio.comm.lds_hal_open("");
	lds_hal_gpio.ioctl(
	LDS_CTRL_GPIO_SET_PIN, ctx->info[count].pin,
	LDS_CTRL_GPIO_DIRECTION, ctx->info[count].direction,
	LDS_CTRL_GPIO_END);

	return 0;
}
/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_key_pin_open(void)
{
	int i = 0;
	int get_value = 0;
	
	ctx->info[0].pin_map = KEY_5;
	ctx->info[0].pin = GPIO68;
	ctx->info[0].direction  = LDS_GPIO_DIRECTION_IN;
	
	ctx->info[1].pin_map = KEY_6;
	ctx->info[1].pin = GPIO69;
	ctx->info[1].direction  = LDS_GPIO_DIRECTION_IN;
	
	ctx->info[2].pin_map = KEY_3;
	ctx->info[2].pin = GPIO70;
	ctx->info[2].direction  = LDS_GPIO_DIRECTION_IN;
	
	ctx->info[3].pin_map = KEY_4;
	ctx->info[3].pin = GPIO71;
	ctx->info[3].direction  = LDS_GPIO_DIRECTION_IN;

	for(i =0; i < MAX_KEY_COUNT; i++)
	{
		lds_hal_set_key_pin(ctx, i);
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
static int lds_hal_key_close_keypad_pin(void* ctx_t)
{
	int i = 0;

	struct LDS_KEY_CTX *ctx;

	if( ctx_t == NULL )
		return -1;
	else
		ctx = ctx_t;

	for(i = 0; i < MAX_KEY_COUNT; i++)
	{
		//lds_hal_gpio.comm.lds_hal_close(ctx->info[i].ctx);
		free(ctx->info[i].ctx);
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
static int  lds_hal_key_monitoring_open(void *ctx_t)
{
	struct LDS_KEY_CTX *ctx;
	if( ctx_t == NULL )
		return -1;
	else
		ctx = ctx_t;

	if((pthread_create( &ctx->pthread, NULL, t_key_monitoring, ctx)) < 0)
	{
		printf("[ERROR] key thread create falie \n");
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
static int lds_hal_key_gpio_open(char* dev_name)
{
	memset( ctx, 0, sizeof(struct LDS_KEY_CTX));
	
	ctx->thread_start = 0;
    
	lds_hal_key_pin_open();

	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_key_gpio_close(int fd)
{
	lds_hal_key_close_keypad_pin(ctx );
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_key_gpio_init(void *param)
{
    ctx = (struct LDS_KEY_CTX *)malloc(sizeof(struct LDS_KEY_CTX));
    return 0;

}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_key_gpio_deinit(void)
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
static int lds_hal_key_gpio_start(void)
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
static int lds_hal_key_gpio_stop(void)
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
static int lds_hal_key_get_error(void)
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
static int lds_hal_key_gpio_ioctl(LDS_CTRL_KEY type, ...)
{
	/* check maxctrl */
	if (type >= LDS_CTRL_KEY_MAX)
		return -1;

	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;
	while( cur_ctrl != LDS_CTRL_KEY_END )
	{
		switch(cur_ctrl)
		{
			case LDS_CTRL_KEY_CALLBACK:
			{
				int (*cb)(int , int) = va_arg(ctrl, int (*)(int , int));
				ctx->callback = cb;
			}
			break;
			case LDS_CTRL_KEY_INTERVAL:
				{
					ctx->intaval = va_arg(ctrl, int);
				}
				break;
			case LDS_CTRL_KEY_START:
				{
					int *param = va_arg(ctrl, int*);
				 	*param = lds_hal_key_monitoring_open(ctx);
				}
				break;
			case LDS_CTRL_KEY_MONITORING:
				{
					int param = va_arg(ctrl, int);
					ctx->monitoring_start = param;
				}
				break;
			case LDS_CTRL_KEY_STOP:
				{
					int* param = va_arg(ctrl , int*);
					int ret = -1;
					ctx->thread_start = 0;
					
					if(ctx->pthread)
					{
						ret = pthread_join(ctx->pthread, NULL);
						ctx->pthread = 0;
					}
					if(ret == 0)
					{
						*param = 0;
					}
					else
					{
						*param = -1;
					}
				}
				break;

			default:
				{
					//printf("[ERROR]  %s::%d >>> Bad CTRL Value = [%d] \n", cur_ctrl);
					assert((cur_ctrl >= LDS_CTRL_KEY_END) && (cur_ctrl < LDS_CTRL_KEY_MAX) );
				}
				break;
		}
		cur_ctrl = va_arg(ctrl, int);
	}
	va_end( ctrl );

	return 0;
}

struct LDS_KEY_OPERATION lds_key_gpio = {
		.name		            = "lds_key_gpio",
		.ctxsize		        = sizeof(struct LDS_KEY_CTX),
		.maxctrl		        = LDS_CTRL_KEY_MAX,
		.comm.lds_hal_open	    = lds_hal_key_gpio_open,
		.comm.lds_hal_close	    = lds_hal_key_gpio_close,
		.comm.lds_hal_start     = lds_hal_key_gpio_start,
		.comm.lds_hal_stop      = lds_hal_key_gpio_stop,
		.comm.lds_hal_init      = lds_hal_key_gpio_init,
		.comm.lds_hal_deinit    = lds_hal_key_gpio_deinit,
		.comm.lds_hal_get_error	= lds_hal_key_get_error,
		.ioctl		            = lds_hal_key_gpio_ioctl,
};

