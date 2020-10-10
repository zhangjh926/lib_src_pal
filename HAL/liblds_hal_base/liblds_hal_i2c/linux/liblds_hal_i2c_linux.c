
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
struct LDS_I2C_CTX
{
	int					slave_addr;
	int					addr_register;
	int					reg_length;
	int					data_length;
	char				reg_address[4];
	char				i2c_name[12];
};

/* Define variable  ----------------------------------------------------------*/

/* Define extern variable & function  ----------------------------------------*/
struct LDS_I2C_CTX *ctx = NULL;
/* Function prototype  -------------------------------------------------------*/

/* Function implementation  --------------------------------------------------*/

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
******************************************************************************/
static int lds_i2c_open( char *dev_name)
{
	int ret = -1;
	/* memory reset */
	memset( ctx, 0, sizeof(struct LDS_I2C_CTX) );

	ctx->slave_addr 	= -1;

	//sprintf(ctx->i2c_name, "/dev/i2c-%d", 0);
	strcpy(ctx->i2c_name, dev_name);

	ctx->reg_length		= 1;
	ctx->data_length	= 1;
	//printf("..This device i2c-num is [%s]\n", ctx->i2c_name);
	return 0;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_i2c_close( int dev_fd )
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
static int lds_i2c_init(void)
{
    ctx = (struct LDS_I2C_CTX *)malloc(sizeof(struct LDS_I2C_CTX));
    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_i2c_deinit(void)
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
static int lds_i2c_start(void)
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
static int lds_i2c_stop(void)
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
static int lds_i2c_read(int fd, void *data, unsigned int size )
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
static int lds_i2c_write(int fd, void *data, unsigned int size )
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
static unsigned int lds_i2c_read2(char *addr, int addr_len, char *buf, int buf_len )
{
	int ret = -1;

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
static unsigned int lds_i2c_write2(char *buf, int buf_len )
{
	int ret = -1;

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
static int lds_i2c_control(LDS_CTRL_I2C type, ...)
{
	int ret = -1;

	/* check maxctrl */
	if (type >= LDS_CTRL_I2C_MAX)
		return ret;

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
				lds_i2c_write2(buf, buf_len);
			}
			break;

			case LDS_CTRL_I2C_GET:
			{
				char *param = va_arg(ctrl, char *);
//				printf("reg_addr = [0x%x], reg_len = [%d], data_len = [%d] slave_addr[0x%x]\n", *(ctx->reg_address), ctx->reg_length,  ctx->data_length , ctx->slave_addr);
				ret = lds_i2c_read2(ctx->reg_address, ctx->reg_length, param, ctx->data_length );
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
		.name			    = "lds_hal_i2c",
		.ctxsize		    = sizeof(struct LDS_I2C_CTX),
		.maxctrl		    = LDS_CTRL_I2C_MAX,
		.comm.lds_hal_open	= lds_i2c_open,
		.comm.lds_hal_close	= lds_i2c_close,
		.comm.lds_hal_start = lds_i2c_start,
		.comm.lds_hal_stop  = lds_i2c_stop,
		.comm.lds_hal_init  = lds_i2c_init,
		.comm.lds_hal_deinit= lds_i2c_deinit,
		.read			    = lds_i2c_read,
		.write			    = lds_i2c_write,
		.ioctl			    = lds_i2c_control,
};
