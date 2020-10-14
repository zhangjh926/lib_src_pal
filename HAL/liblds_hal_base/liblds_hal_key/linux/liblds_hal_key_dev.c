#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <stdarg.h>
#include <linux/input.h>

#include "liblds_hal_key_base.h"

/* Define  -------------------------------------------------------------------*/
#define KEYPAD_DATA_COUNT	2

struct LDS_KEY_CTX
{
	 int		(*callback)(int, int);
	 int		intaval;
	 int		thread_start;
	 int		monitoring_start;
	 int		fd;

	 void*		ctx;
	 pthread_t	pthread;
}; 

/* Define variable  ----------------------------------------------------------*/
static struct LDS_KEY_CTX *ctx;
/* Define extern variable & function  ----------------------------------------*/

/* Function prototype  -------------------------------------------------------*/
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
	int ret = 0;
	if( ctx_t == NULL)
		return 0;
	else
		ctx = ctx_t;	

	if(ctx->fd < 0){
		printf("[ERROR] can not dev open t_key_monitoring()\n");
		return 0;
	}
	
	struct	input_event keypad_event[KEYPAD_DATA_COUNT] = {0,};
	struct	timeval tv; 
	
	int state = 0;
	fd_set    readfds, writefds;	
	
	ctx->thread_start = 1;
	while(ctx->thread_start)
	{
		int key = 0;
		int status = -1;
		
		while(!ctx->monitoring_start)
			sleep(1);

		ret = read(ctx->fd, &keypad_event, sizeof(struct input_event)*KEYPAD_DATA_COUNT);

		if(keypad_event[0].type == EV_KEY){
			key =  keypad_event[0].code;

			if(keypad_event[0].value)
			{
				FD_SET(ctx->fd, &readfds);

				tv.tv_sec = 0;
				tv.tv_usec = 20000 * 30;

				state = select(ctx->fd + 1, &readfds, (fd_set *)0, (fd_set *)0, &tv);

				if(state == 0){
					printf("key pressing = [%d] \n", state);
					status = LDS_CTRL_KEY_PRESSING;
				}else if(state == 1){
					printf("key_press = [%d] \n", state);
					status = LDS_CTRL_KEY_PRESS;
				}else{
					printf("%s::%d >>>>>> key status error : [%d] \n", __FILE__, __LINE__, state);
				}

				ctx->callback(key, status);
			}
		}
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
static int lds_key_pin_open(void* ctx_t, char* dev)
{
	struct LDS_KEY_CTX *ctx;

	if( ctx_t == NULL)
		return -1;
	else
		ctx = ctx_t;

	ctx->fd = open(dev, O_RDWR);
	if(ctx->fd < 0)
	{
		printf("[ERROR] can not dev open nca_key_pin_open()\n");
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
static int  lds_key_monitoring_open(void *ctx_t)
{
	struct LDS_KEY_CTX *ctx;

	if( ctx_t == NULL )
	{
		return -1;
	}
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
static int key_input_device_search(int *dev_num, char *dev_name)
{	
	FILE	*fp;
	char	buf[256];
	char	*proc_path = "/proc/bus/input/devices";
	int		found = 0;

	/* check file */
	if( access( proc_path, F_OK) != 0 )
	{
		printf("[ERROR] no devices file!! key_input_device_serch() \n");
		return -1;
	}
	/* read proc */
	fp = fopen( proc_path , "r");

	if(fp == NULL)
	{
		printf("[ERROR] %s::%d >>> Fopen faile~ keypad device name\n", __FILE__, __LINE__);
		return -1;
	}

	while( fgets(buf, 256, fp) != NULL )
	{
		if ((found == 0) && (strstr(buf, "N: Name") != NULL))
		{
			if((strstr(buf, dev_name) != NULL))
			{
				found = 1;
				continue;
			}
		}

		if( (found == 1) && ( strstr(buf, "H: Handlers") != NULL))
		{
			snprintf(buf, 4, "%s",strstr(buf, "event") + strlen("event") );
			*dev_num = atoi(buf);
			break;
		}
	}
	fclose( fp );
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_key_dev_open(char* dev_name)
{
	int dev_num = 0;
	char buf[36] = {0,};
	
	memset( ctx, 0, sizeof(struct LDS_KEY_CTX));
	ctx->thread_start = 0;

	key_input_device_search(&dev_num, dev_name);

	sprintf(buf, "/dev/input/event%d", dev_num);
	printf("keypad /dev/input/event%d\n", dev_num);

	if( lds_key_pin_open(ctx, buf) < 0)
	{
		printf("[ERROR] %s::%d >>>> keypad device open faile \n", __FILE__, __LINE__);
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
static int lds_key_dev_close(int dev_fd)
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
static int lds_key_dev_start(void)
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
static int lds_key_dev_stop(void)
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
static int lds_key_dev_init(void *param)
{
    ctx = (struct LDS_KEY_CTX*)malloc(sizeof(struct LDS_KEY_CTX));
    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_key_dev_deinit(void)
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
static int lds_key_dev_ioctl(LDS_CTRL_KEY type, ...)
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
					
					if( lds_key_monitoring_open(ctx) < 0)
					{
					 	*param = -1;
					}
					else
					{
						*param = 0;
					}
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

struct LDS_KEY_OPERATION lds_key_dev = {
		.name		        = "lds_key_dev",
		.ctxsize	        = sizeof(struct LDS_KEY_CTX),
		.maxctrl	        = LDS_CTRL_KEY_MAX,

		.comm.lds_hal_open	= lds_key_dev_open,
		.comm.lds_hal_close = lds_key_dev_close,
		.comm.lds_hal_start = lds_key_dev_start,
		.comm.lds_hal_stop  = lds_key_dev_stop,
		.comm.lds_hal_init  = lds_key_dev_init,
		.comm.lds_hal_deinit= lds_key_dev_deinit,
		.ioctl	 	        = lds_key_dev_ioctl,
};

