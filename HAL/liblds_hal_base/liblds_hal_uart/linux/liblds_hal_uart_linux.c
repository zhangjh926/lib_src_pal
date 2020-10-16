
/* Header file include -------------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "liblds_hal_uart_base.h"
#include "liblds_hal_uart_util.h"

/* Define  -------------------------------------------------------------------*/
struct LDS_RS232_CTX
{
	struct rs232_port_t	*p;
	int					read_timeout;	// ms
	int					write_timeout;	// ms
	int					debug_msg;
	LDS_UART_ErrorNo	curr_err_state;
};

/* Define variable  ----------------------------------------------------------*/
static struct LDS_RS232_CTX *lds_rs232_ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/
extern unsigned short rs232_crc16_ccitt(unsigned char *data, int size);

/* Function prototype  -------------------------------------------------------*/

/* Function implementation  --------------------------------------------------*/

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static unsigned int lds_hal_rs232_err(unsigned int e)
{
	printf("%s (%s)\n", rs232_strerror(e), errno > 0 ? strerror(errno) : "");
	return e;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int 			lds_hal_rs232_open(char *dev_name )
{
	int ret = -1;

	if(  dev_name == NULL )
		return ret;

	/* init rs232 module */
	lds_rs232_ctx->p = rs232_init();
	if( lds_rs232_ctx->p == NULL )
		return ret;

	/* set device */
	rs232_set_device(lds_rs232_ctx->p, dev_name);

	/* open device */
	if( rs232_open(lds_rs232_ctx->p) > 0)
	{
		rs232_end(lds_rs232_ctx->p);
		ret =  -lds_hal_rs232_err(ret);
	}
#if 0
	/* default setting */
	rs232_set_baud(ncl_rs232_ctx->p, RS232_BAUD_9600);
	printf("[NCL_RS232] OPEN : %s\n", rs232_to_string(ncl_rs232_ctx->p));

	rs232_flush(ncl_rs232_ctx->p);
#endif

	/* init ctx value */
	lds_rs232_ctx->read_timeout		= 1000;
	lds_rs232_ctx->write_timeout	= 1000;

	return ret;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int 			lds_hal_rs232_close( int dev_fd )
{
	int ret = -1;

	rs232_end(lds_rs232_ctx->p);

	return ret;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int 			lds_hal_rs232_init( void *param)
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
static int 			lds_hal_rs232_deinit( void)
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
static int 			lds_hal_rs232_start( void )
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
static int 			lds_hal_rs232_stop( void)
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
static unsigned int lds_hal_rs232_read(unsigned char *data, unsigned int size )
{
	unsigned int ret = 0;
	unsigned int bytes;

	ret = rs232_read_timeout(lds_rs232_ctx->p, data, size, &bytes, lds_rs232_ctx->read_timeout);
	if( ret > 0 )
	{
		if( lds_rs232_ctx->debug_msg )
			lds_hal_rs232_err(ret);

		return 0;
	}
#if 0
	else
		printf("0x%02x len: %d\n", data[0], bytes);
#endif

	return bytes;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static unsigned int lds_hal_rs232_write(unsigned char *data, unsigned int size )
{
	unsigned int ret = 0;
	unsigned int bytes;

	ret = rs232_write_timeout(lds_rs232_ctx->p, data, size, &bytes, lds_rs232_ctx->write_timeout);
	if( ret > 0 )
	{
		if( lds_rs232_ctx->debug_msg )
			lds_hal_rs232_err(ret);
		return 0;
	}
#if 0
	else
		printf("0x%02x len: %d\n", data[0], bytes);
#endif

	return bytes;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int 			lds_hal_rs232_control(LDS_CTRL_RS232 type, ...)
{
	int ret = -1;
	struct LDS_RS232_CTX *ncl_rs232_ctx;

    ncl_rs232_ctx = lds_rs232_ctx;

	/* check maxctrl */
	if (type >= LDS_CTRL_RS232_MAX)
		return ret;

	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;
	while( cur_ctrl != LDS_CTRL_RS232_END )
	{
		switch(cur_ctrl)
		{
		case LDS_CTRL_RS232_BAUD :
			{
				int baud = va_arg(ctrl, int);
				rs232_set_baud(ncl_rs232_ctx->p, baud);
				rs232_flush(ncl_rs232_ctx->p);

				printf("[ncl_rs232] CTRL_MICOM_BAUD : %s\n", rs232_to_string(ncl_rs232_ctx->p));
			}
			break;

		case LDS_CTRL_RS232_READ_TIMEOUT :
			ncl_rs232_ctx->read_timeout = va_arg(ctrl, int);
			break;

		case  LDS_CTRL_RS232_WRITE_TIMEOUT :
			ncl_rs232_ctx->write_timeout = va_arg(ctrl, int);
			break;

		case  LDS_CTRL_RS232_DEBUG :
			ncl_rs232_ctx->debug_msg = va_arg(ctrl, int);
			break;

		case  LDS_CTRL_RS232_TCSBRKP :
			{
				int txd = va_arg(ctrl, int);
				rs232_set_txd_break(ncl_rs232_ctx->p, txd);
			}
			break;
		}

		cur_ctrl = va_arg(ctrl, int);
	}
	va_end( ctrl );

	return ret;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static unsigned short 	lds_hal_rs232_crc(unsigned char *data, int size)
{
	return rs232_crc16_ccitt(data, size);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static	int 		lds_hal_rs232_get_error(void)
{
	return lds_rs232_ctx->curr_err_state;
}

struct LDS_RS232_OPERATION lds_hal_rs232 = {
		.name			        = "lds_hal_rs232",
		.ctxsize		        = sizeof(struct LDS_RS232_CTX),
		.maxctrl		        = LDS_CTRL_RS232_MAX,
		.comm.lds_hal_open		= lds_hal_rs232_open,
		.comm.lds_hal_close		= lds_hal_rs232_close,
		.comm.lds_hal_start     = lds_hal_rs232_start,
		.comm.lds_hal_stop      = lds_hal_rs232_stop,
		.comm.lds_hal_init      = lds_hal_rs232_init,
		.comm.lds_hal_deinit    = lds_hal_rs232_deinit,
		.comm.lds_hal_get_error = lds_hal_rs232_get_error,
		.read			        = lds_hal_rs232_read,
		.write			        = lds_hal_rs232_write,
		.ioctl		            = lds_hal_rs232_control,
		.crc			        = lds_hal_rs232_crc
};

