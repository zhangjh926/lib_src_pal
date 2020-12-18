#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "liblds_hal_gpio_base.h"

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/
#define GPIO_PINNO_MIN					0
#define GPIO_PINNO_MAX					159
#define SYSFS_GPIO_PATH					"/sys/class/gpio"

// static struct LDS_GPIO_CTX  *ctx = NULL;

static int lds_hal_gpio_pin_set(LDS_GPIO_CTX *ctx_t, int pin_num)
{
	int fd = 0; 
	int len = 0;
	char buf[65];
	char *sysfs_file = NULL;
	LDS_GPIO_CTX *ctx = NULL;
	memset(buf, 0, 65);
	
	if(NULL == ctx_t) return -1;
	else ctx = ctx_t;

	sysfs_file = ctx->sysfs_file;

	if( (pin_num < GPIO_PINNO_MIN) || (pin_num > GPIO_PINNO_MAX) )
	{
		printf("[ERROR] gpio num error unknown number %d \n", pin_num);
		return -1;
	}

	// Check gpio num
	sprintf( sysfs_file, SYSFS_GPIO_PATH"/gpio%d", pin_num);

	if( !access(sysfs_file, F_OK) ) 
	{
		//printf(" gpio%d already initialize.\n", pin_num);
	}
	else 
	{
		if( (fd = open(SYSFS_GPIO_PATH"/export", O_WRONLY)) < 0)
		{
			printf("[ERROR] cannot export gpio%d\n", pin_num);
			return -1;
		}

		len = snprintf(buf, sizeof(buf), "%d", pin_num);
	
		if( write(fd, buf, len) < 0 ) 
		{
			printf("[ERROR] cannot write gpio%d export file!\n", pin_num);
			close(fd);
			return -1;
		}
	}

	ctx->pin = pin_num;
	//printf("gpio pin [%d] setting\n", pin_num);
	return 0;
}

static int lds_hal_gpio_direction(LDS_GPIO_CTX *ctx_t, int direction)
{
	int fd = 0;
	int len = 0;
	char buf[148] = {0};
	LDS_GPIO_CTX *ctx = NULL;

	if(NULL == ctx_t) return -1;
	else ctx = ctx_t;

	if( ctx->pin < 0 )
	{
		printf("[ERROR] gpio pin not setting \n");
		return -1;
	}
	
	if( (direction > LDS_GPIO_DIRECTION_OUT ) || (direction < LDS_GPIO_DIRECTION_IN) )
	{
		printf("[ERROR] direction command error [%d] [%d]\n", direction,  ctx->pin);
		return -1;
	}
	len = snprintf(buf, sizeof(buf), "%s/direction", ctx->sysfs_file);

	fd = open(buf, O_WRONLY);
	if(fd < 0)
	{
		printf("[ERROR] direction read faile \n");
		return -1;
	}
 
	len = snprintf(buf, sizeof(buf), "%s", (direction == LDS_GPIO_DIRECTION_IN) ? "in" : "out");

	if( (write(fd, buf, len) ) < 0)
	{
		printf("[ERROR] direction write faile \n");
		close(fd);
		return -1;
	}
	close(fd);

	ctx->direction = direction;
	printf("gpio pin [%d] direction %sput setting\n", ctx->pin, buf);
	return 0;
}

static int lds_hal_gpio_set_value(LDS_GPIO_CTX *ctx_t,  int set_value)
{
	int fd = 0;
	int len = 0;
	char buf[148] = {0};
	LDS_GPIO_CTX *ctx = NULL;

	if(NULL == ctx_t) return -1;
	else ctx = ctx_t;

	if( ctx->pin < 0 )
	{
		printf("[ERROR] gpio pin not setting \n");
		return -1;
	}

	if( (set_value < LDS_GPIO_STATUS_LOW) || (set_value > LDS_GPIO_STATUS_HIGH) )
	{
		printf("[ERROR] wrong set_value [%d] \n", set_value);
		return -1;
	}
	len = snprintf(buf, sizeof(buf), "%s/value", ctx->sysfs_file);
	if((fd = open(buf, O_RDWR)) < 0 )
	{
		printf("[ERROR] cannot open gpio%d value!\n", ctx->pin);
		return -1;
	}

	len = snprintf(buf, sizeof(buf), "%d", set_value);
	if(write(fd, buf, len) < 0) 
	{
		printf("[ERROR] cannot write gpio%d value!\n", ctx->pin);
		close(fd);
		return -1;
	}

	close(fd);
	return 0;
}
static int lds_hal_gpio_get_value(LDS_GPIO_CTX *ctx_t)
{
	int fd = 0;
	int len = 0;
	char buf[148] = {0};
	LDS_GPIO_CTX *ctx = NULL;

	if(NULL == ctx_t) return -1;
	else ctx = ctx_t;

	if( ctx->pin < 0 )
	{
		printf("[ERROR] gpio pin not setting \n");
		return -1;
	}

	len = snprintf(buf,  sizeof(buf),"%s/value", ctx->sysfs_file);
	if( (fd = open(buf, O_RDWR)) < 0 )
	{
		printf("[ERROR] cannot open gpio%d value!\n",ctx->pin);
		return -1;
	}
	if( (len = read(fd, buf, sizeof(buf))) < 0 )
	{
		printf("[ERROR] cannot read gpio%d value!\n", ctx->pin);
		close(fd);
		return -1;
	}
	close(fd);
	return atoi(buf);
}

static int lds_hal_gpio_togle(LDS_GPIO_CTX *ctx_t)
{
	if(ctx_t == NULL)
	{
		printf("[ERROR] ctx NULL error lds_gpio_togle\n");
		return -1;
	}
	
	int curr = lds_hal_gpio_get_value(ctx_t);
	
	lds_hal_gpio_set_value( ctx_t, !curr);

	return curr;
}

static int lds_hal_gpio_open(void  *ctx_t, void *param)
{
	if(NULL == ctx_t){
		return -1;
	}

	return 0;
}

static int lds_hal_gpio_start( void *ctx_t)
{
	if(NULL == ctx_t){
		return -1;
	}

    return 0;
}

static int lds_hal_gpio_stop( void *ctx_t)
{
	if(NULL == ctx_t){
		return -1;
	}

    return 0;
}

static int lds_hal_gpio_init( void *param)
{
    return 0;
}

static int lds_hal_gpio_deinit( void *ctx_t)
{	
	if(NULL == ctx_t) return -1;

    return 0;
}


static int lds_hal_gpio_close( void *ctx_t)
{
	int fd = 0;
	int len = 0;
	char buf[65];
	LDS_GPIO_CTX *ctx = NULL;

	if(NULL == ctx_t) return -1;
	ctx = ctx_t;
	
	memset(buf, 0, 65);
	
	if( (fd = open(SYSFS_GPIO_PATH"/unexport", O_WRONLY)) < 0 )
	{
		printf("cannot unexport gpio%d\n", ctx->pin);
		return -1;
	}
	
	len = snprintf(buf, sizeof(buf), "%d",  ctx->pin);

	if( write(fd, buf, len) < 0 ) 
	{
		printf("cannot write gpio%d unexport file!\n",  ctx->pin);
		return -1;
		close(fd);
	}
	close(fd);

	printf("gpio pin [%d] cloise\n", ctx->pin);
	return 0;
}

static unsigned int lds_hal_gpio_read(  unsigned int pin_num)
{
	return 0;
}

static unsigned int lds_hal_gpio_write( unsigned int pin_num, unsigned int value)
{	
	return 0;
}

static int lds_hal_gpio_get_error(void *ctx_t)
{
	LDS_GPIO_CTX *ctx = NULL;
	
	if(NULL == ctx_t ) return -1;
	else ctx = ctx_t;

	return ctx->curr_err_state;
}

static int lds_hal_gpio_ioctl(LDS_GPIO_CTX *ctx_t, LDS_CTRL_GPIO type, ...)
{
	int ret = 0;
	LDS_GPIO_CTX *ctx = NULL;
	/* check maxctrl */
	if (type >= LDS_CTRL_GPIO_MAX)
		return ret;

	if(NULL == ctx_t) return -1;
	ctx = ctx_t;

	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;
	while( cur_ctrl != LDS_CTRL_GPIO_END ){
		switch(cur_ctrl){
			case LDS_CTRL_GPIO_SET_PIN:{
					int param = va_arg(ctrl, int);
					ret = lds_hal_gpio_pin_set( ctx, param);
				}
				break;
			case LDS_CTRL_GPIO_DIRECTION:{
					int direction = va_arg(ctrl, int);
					ret = lds_hal_gpio_direction( ctx , direction);
				}
				break;
			case LDS_CTRL_GPIO_GET_VALUE:{
					int *param = va_arg(ctrl, int *);
					*param =  lds_hal_gpio_get_value(ctx);
					
				}
				break;
			case LDS_CTRL_GPIO_SET_VALUE:{
					int set_value = va_arg(ctrl, int);
					ret = lds_hal_gpio_set_value(ctx, set_value);
				}
				break;
			case LDS_CTRL_GPIO_TOGLE:{
					int status = va_arg(ctrl, int);

					if(status){
						lds_hal_gpio_togle(ctx);
					}
				}
				break;
		}
		cur_ctrl = va_arg(ctrl, int);
	}
	va_end( ctrl );

	return ret;
}

struct LDS_GPIO_OPERATION lds_hal_gpio = {
		.name			        = "lds_hal_gpio",
		.base.lds_hal_open	    = lds_hal_gpio_open,
		.base.lds_hal_close	    = lds_hal_gpio_close,
		.base.lds_hal_start     = lds_hal_gpio_start,
		.base.lds_hal_stop      = lds_hal_gpio_stop,
		.base.lds_hal_get_error = lds_hal_gpio_get_error,
		.ioctl			        = lds_hal_gpio_ioctl,
};
