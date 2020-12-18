
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdint.h>
#include <errno.h>

#include "liblds_hal_i2c_io.h"
#include "liblds_hal_i2c_base.h"

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/

/* Define extern variable & function  ----------------------------------------*/
static LDS_I2C_CTX *ctx = NULL;
/* Function prototype  -------------------------------------------------------*/

/* Function implementation  --------------------------------------------------*/

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
******************************************************************************/
static int lds_hal_i2c_open( void *ctx_t, void *param)
{
	int ret = -1;
	/* memory reset */
	if(NULL == ctx_t) return -1;
	else ctx = ctx_t;

	ctx->slave_addr 	= -1;

	//sprintf(ctx->i2c_name, "/dev/i2c-%d", 0);
	// strcpy(ctx->i2c_name, dev_name);

	ctx->reg_length		= 1;
	ctx->data_length	= 1;
	printf("..This device i2c-num is [%s]\n", ctx->i2c_name);
	return 0;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_i2c_close( void *ctx_t)
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
static int lds_hal_i2c_init(void *param)
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
static int lds_hal_i2c_deinit(void *ctx_t)
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
static int lds_hal_i2c_start(void *ctx_t)
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
static int lds_hal_i2c_stop(void *ctx_t)
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
static int lds_hal_i2c_read(LDS_I2C_CTX *ctx, int fd, void *data, unsigned int size )
{
	int ret = -1;

	/* open i2c device */
	uint8_t slave_addr = ctx->slave_addr >> 1;

	/* read packet */
	ret = i2c_read( fd, slave_addr, 0x00, data, 1, size);

	if( ret < 0 )
	{
		printf("%s::%d >>errno: %d strerror: %s %s\n", __FILE__, __LINE__,
		    errno, strerror(errno), "I2C_ERR_IOCTL");

		close ( fd );
		return ret;
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
static int lds_hal_i2c_write(LDS_I2C_CTX *ctx, int fd, void *data, unsigned int size )
{
	int ret = -1;

	/* open i2c device */
	uint8_t slave_addr = ctx->slave_addr >> 1;

	/* write packet */

	ret = i2c_write( fd, slave_addr, data, 1, size);

	if( ret < 0 )
	{
		printf("%s::%d >> slave_addr:%#x, errno: %d strerror: %s %s\n", __FILE__, __LINE__,
				slave_addr, errno, strerror(errno), "IOCTL");

		close ( fd );
		return ret;
	}

	return size;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static unsigned int lds_hal_i2c_read2(LDS_I2C_CTX *ctx_t, char *addr, int addr_len, char *buf, int buf_len )
{
	int ret = -1;
	LDS_I2C_CTX *ctx = NULL;

	if(NULL == ctx_t) return -1;
	else ctx = ctx_t;

	if(ctx->slave_addr < 0)
	{
		printf("salve addr not setting \n");
		return -1;
	}

	/* open i2c device */
	uint8_t slave_addr = ctx->slave_addr >> 1;
	int fd = i2c_open(ctx->i2c_name, slave_addr);

	if( fd < 0 )
		return ret;

	/* read packet */
	ret = i2c_read2( fd, slave_addr, addr, addr_len, buf, buf_len);
	if( ret < 0 )
	{
		printf("%s::%d >>errno: %d strerror: %s %s\n", __FILE__, __LINE__,
		    errno, strerror(errno), "I2C_ERR_IOCTL");

		close ( fd );
		return ret;
	}


	close ( fd );
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static unsigned int lds_hal_i2c_write2(LDS_I2C_CTX *ctx_t, char *buf, int buf_len )
{
	int ret = -1;
	LDS_I2C_CTX *ctx = NULL;

	if(NULL == ctx_t) return -1;
	else ctx = ctx_t;

	if(ctx->slave_addr < 0)
	{
		printf("salve addr not setting \n");
		return -1;
	}

	/* open i2c device */
	uint8_t slave_addr = ctx->slave_addr >> 1;
	int fd = i2c_open(ctx->i2c_name, slave_addr);
	if( fd < 0 )
	{
		printf("%s::%d >>i2c_open errno: %d \n", __FILE__, __LINE__, fd);
		return ret;
	}

	/* write packet */
	ret = i2c_write2( fd, buf, buf_len);

	if( ret < 0 )
	{
		printf("%s::%d >> slave_addr:%#x, errno: %d strerror: %s %s\n", __FILE__, __LINE__,
				slave_addr, errno, strerror(errno), "IOCTL");

		close ( fd );
		return ret;
	}

	close ( fd );

	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static 	int 	lds_hal_i2c_get_error(void *ctx_t)
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
static int lds_hal_i2c_control(LDS_I2C_CTX *ctx_t, LDS_CTRL_I2C type, ...)
{
	int ret = -1;
	LDS_I2C_CTX *ctx = NULL;
	/* check maxctrl */
	if (type >= LDS_CTRL_I2C_MAX)
		return ret;

	if(NULL == ctx_t) return -1;
	else ctx = ctx_t;

	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;

	while( cur_ctrl != LDS_CTRL_I2C_END )
	{
		switch(cur_ctrl)
		{
			case LDS_CTRL_I2C_SLAVE_ADDRESS:
			{
				ctx->slave_addr		= va_arg(ctrl, int);
			}
			break;

			case LDS_CTRL_I2C_REGISTER_ADDRESS:
			{
				unsigned int param = va_arg(ctrl,unsigned int);
				int temp = 0;

				memset( ctx->reg_address, 0, 4);
				if( ctx->reg_length == 1)
				{
					ctx->reg_address[0]= param;
				}
				else//16 bit
				{
					temp = param >> 8;
					ctx->reg_address[0] = temp;

					temp = param ^ (temp << 8);
					ctx->reg_address[1] = temp;
				}
			}
			break;

			case LDS_CTRL_I2C_REGISTER_ADDRESS_LENGTH:
			{
				int param = va_arg(ctrl, int);
				if( (param == 1) || (param == 2) )
				{
					ctx->reg_length = param;
				}
				else
				{
					printf("[ERROR] bad i2c addr length input [%d]\n", param);
				}
			}
			break;

			case LDS_CTRL_I2C_REGISTER_DATA_LENGTH:
			{
				int param = va_arg(ctrl, int);
				if( (param == 1) || (param == 2) )
				{
					ctx->data_length = param;
				}
				else
				{
					printf("[ERROR] bad i2c data length input [%d]\n", param);
				}
			}
			break;

			case LDS_CTRL_I2C_SET:
			{
				int buf_len = 0;
				char buf[32];
				char *param = va_arg(ctrl, char *);
				/* address */
				memcpy( buf, ctx->reg_address, ctx->reg_length);
				buf_len = ctx->reg_length;

				/* data */
				memcpy( buf + buf_len, param, ctx->data_length);
				buf_len += ctx->reg_length;
				lds_hal_i2c_write2(ctx, buf, buf_len);
			}
			break;

			case LDS_CTRL_I2C_GET:
			{
				char *param = va_arg(ctrl, char *);
//				printf("reg_addr = [0x%x], reg_len = [%d], data_len = [%d] slave_addr[0x%x]\n", *(ctx->reg_address), ctx->reg_length,  ctx->data_length , ctx->slave_addr);
				ret = lds_hal_i2c_read2(ctx, ctx->reg_address, ctx->reg_length, param, ctx->data_length );
			}
			break;
			case LDS_CTRL_I2C_SET_I2CNUM:
			{
				int num = va_arg(ctrl, int);
				sprintf(ctx->i2c_name, "/dev/i2c-%d", num);
				printf("....This device i2c-num is [%s]\n", ctx->i2c_name);
			}
			break;
			case LDS_CTRL_I2C_FDOPEN:
			{
				int *param = va_arg(ctrl, int *);
				uint8_t slave_addr = ctx->slave_addr >> 1;
				*param = i2c_open(ctx->i2c_name, slave_addr);
			}
			break;
		}
		cur_ctrl = va_arg(ctrl, int);
	}
	va_end( ctrl );

	return ret;
}

struct LDS_I2C_OPERATION lds_hal_i2c = {
		.name			    	= "lds_hal_i2c",
		.base.lds_hal_open		= lds_hal_i2c_open,
		.base.lds_hal_close		= lds_hal_i2c_close,
		.base.lds_hal_start 	= lds_hal_i2c_start,
		.base.lds_hal_stop  	= lds_hal_i2c_stop,
		.base.lds_hal_get_error	= lds_hal_i2c_get_error,
		.read			    	= lds_hal_i2c_read,
		.write			    	= lds_hal_i2c_write,
		.ioctl			    	= lds_hal_i2c_control,
};
