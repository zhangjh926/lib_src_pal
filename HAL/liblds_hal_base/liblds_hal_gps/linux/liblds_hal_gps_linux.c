
/* Header file include -------------------------------------------------------*/
//#define NDEBUG
#include <assert.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

#include "liblds_hal_uart_base.h"
#include "liblds_hal_gps_base.h"

/* Define  -------------------------------------------------------------------*/
#define GPS_DEVICE	"/dev/ttyS1"
#define TRUE	1
#define FALSE	0

enum
{
	LDS_GPS_SPEED_KMH =	0,
	LDS_GPS_SPEED_MPH,
	LDS_GPS_SPEED_NODE,
};

typedef struct	tagGPS_MESG
{
    unsigned char	data[50][20];
    unsigned char	data_num;
} NC_GPS_MESG, *PNC_GPS_MESG;

struct LDS_GPS_CTX
{
	void				*ctx_gps;
	int					(*callback)(void *, int, int);

	pthread_t			pthread;
	int					monitoring_start;
	int					intaval;
	NC_GPS_MESG 		gps_mesg;
	NC_GPS_GPRMC		gps_rmc;
};

/* Define variable  ----------------------------------------------------------*/

/* Define extern variable & function  ----------------------------------------*/
int	gps_thread_start;

struct LDS_GPS_CTX *ctx = NULL;
/* Function prototype  -------------------------------------------------------*/

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
float ConvertKnotToSpeedometer( float speed, int speed_mode )
{
	float	nSpeed = 0;

	if(speed_mode == LDS_GPS_SPEED_KMH)
	{
		const float g_kmh_unit = 1.852;
		nSpeed = speed * g_kmh_unit;
	}
	else if(speed_mode == LDS_GPS_SPEED_MPH)
	{
		const float g_mph_unit = 1.150;
		nSpeed = speed * g_mph_unit;
	}
	else
	{
		nSpeed = speed;
		printf("[ERROR] %s::%d >>>> Unknown speed convert mode [%d] \n", __FILE__, __LINE__, speed_mode);
	}
	return nSpeed;
}

/*******************************************************************************
*	Description		: 
*	Argurments		: 
*	Return value	: 
*	Modify			: 
*	warning			: 
*******************************************************************************/
static void lds_dump_gprmc( NC_GPS_GPRMC s_gps_info )
{
	printf("gprmc : time=%4d/%2d/%2d %2d:%2d:%2d  lati[deg=%f, dir=%d], longi[deg=%f,dir=%d], speed=%f\n",
					  	s_gps_info.date_yy, s_gps_info.date_mm, s_gps_info.date_dd, s_gps_info.utc_hh, s_gps_info.utc_mm, s_gps_info.utc_ss,
					  	s_gps_info.latitude_deg, s_gps_info.latitude_dir, s_gps_info.longitude_deg, s_gps_info.longitude_dir,
					  	s_gps_info.node_speed );
}

/*******************************************************************************
*	Description		: 
*	Argurments		: 
*	Return value	: 
*	Modify			: 
*	warning			: 
*******************************************************************************/
static int lds_gps_check_checksum( unsigned char *data,  unsigned char checksum)
{
	 unsigned char	result = 0;

	while( *data )
	{
		result ^= *data;
		data++;
	}

	return (result == checksum) ? 0 : -1;
}

/*******************************************************************************
*	Description		: 
*	Argurments		: 
*	Return value	: 
*	Modify			: 
*	warning			: 
*******************************************************************************/
static int lds_gps_parse_mesg(unsigned char *data, NC_GPS_MESG *gps_mesg)
{
	int		ret = -1;
	unsigned char	data_idx = 0;

	gps_mesg->data_num = 0;

	while( *data )
	{
		if( *data == ',' )
		{
			gps_mesg->data[gps_mesg->data_num][data_idx] = 0;
			gps_mesg->data_num++;
			data_idx = 0;
			ret = 0;
		}
		else
		{
			gps_mesg->data[gps_mesg->data_num][data_idx++] = *data;
		}

		data++;
	}

	gps_mesg->data[gps_mesg->data_num][data_idx] = 0;
	gps_mesg->data_num++;

	return ret;
}

/*******************************************************************************
*	Description		: 
*	Argurments		: 
*	Return value	: 
*	Modify			: 
*	warning			: 
*******************************************************************************/
static int lds_gps_process(unsigned char data, NC_GPS_MESG *p_gps_msg)
{
	static unsigned char	msg_idx = 0; // 0: none, 1: message, 2: checksum
	static unsigned char	buf_idx = 0;
	static unsigned char	buf[255];
	static unsigned char	checksum_buf_idx = 0;
	static unsigned char	checksum_buf[3]; // 2 byte hex code
	unsigned char			checksum = 0;
	int					ret = -1;

	switch( msg_idx )
	{
		case 0 : // Start char
			if( data == '$' )
			{
				msg_idx++;
				buf_idx = 0;
				checksum_buf_idx = 0;
			}
			else
			{
				msg_idx = 0;
			}
			break;

		case 1 : // Message
			if( data == '*' )
			{
				buf[buf_idx] = 0;
				msg_idx++;
			}
			else
			{
				buf[buf_idx++] = data;
			}
			break;

		case 2 : // Checksum
			checksum_buf[checksum_buf_idx++] = data;
			if( checksum_buf_idx == 2 )
			{
				char *end;

				checksum_buf[2] = 0;
				checksum = strtol( (char*)checksum_buf, &end, 16 );
				msg_idx = 0;

				if( lds_gps_check_checksum(buf, checksum) == 0 ) // Checksum
//				if( 1 )
				{
					ret = lds_gps_parse_mesg( buf, p_gps_msg );
				}
			}
			break;
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
static int lds_nmea_gprmc(NC_GPS_GPRMC *gps_rmc, NC_GPS_MESG *gps_mesg)
{
	int		ret = -1;
	int		i;
	float		f;

	if( gps_rmc && gps_mesg )
	{
		// [Field 1] "hhmmss" - Time of fix UTC
		i = atoi( (char*)gps_mesg->data[1] );
		gps_rmc->utc_hh = i / 10000;

		i -= (gps_rmc->utc_hh * 10000);
		gps_rmc->utc_mm = i / 100;

		i -= (gps_rmc->utc_mm * 100);
		gps_rmc->utc_ss = i;

		// [Field 2] Navigation receiver warning A = OK, V = warning
		if( gps_mesg->data[2][0] == 'A' )
			gps_rmc->receive_ok = 1;
		else
			gps_rmc->receive_ok = 0;

		// [Field 3] Latitude
		f = atof( (char*)gps_mesg->data[3] );
		gps_rmc->latitude_deg = f;

		// [Field 4] N/S Indicator, N = north, S = south
		if( gps_mesg->data[4][0] == 'N' )
			gps_rmc->latitude_dir = 1;
		else
			gps_rmc->latitude_dir = 0;

		// [Field 5] Longitude
		f = atof( (char*)gps_mesg->data[5] );
		gps_rmc->longitude_deg = f;

		// [Field 6] E/W Indicator, E = east, W = west
		if( gps_mesg->data[6][0] == 'E' )
			gps_rmc->longitude_dir = 1;
		else
			gps_rmc->longitude_dir = 0;

		// [Field 7] Speed over ground, Knots
		f = atof( (char*)gps_mesg->data[7] );
		gps_rmc->node_speed = f;
		gps_rmc->kmh_speed = ConvertKnotToSpeedometer(f, LDS_GPS_SPEED_KMH);
		gps_rmc->mph_speed = ConvertKnotToSpeedometer(f, LDS_GPS_SPEED_MPH);

		// [Field 9] "ddmmyy" Date of fix
		i = atoi( (char*)gps_mesg->data[9] );
		gps_rmc->date_dd = i / 10000;

		i -= gps_rmc->date_dd * 10000;
		gps_rmc->date_mm = i / 100;

		i -= gps_rmc->date_mm * 100;
		gps_rmc->date_yy = i;

#if 1
		if( gps_rmc->receive_ok )
			ret = 0;
#endif
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
static int lds_gps_ParseData( char *gps_data, void* ctx_t )
{

	struct LDS_GPS_CTX *ctx;
	if( ctx_t == NULL )
		return -1;
	else
		ctx = ctx_t;
	do
	{
		if( lds_gps_process(*gps_data, &ctx->gps_mesg) == 0 )
		{
			if( strcmp((const char*)ctx->gps_mesg.data, "GPRMC") == 0 )
			{
				if( lds_nmea_gprmc(&ctx->gps_rmc, &ctx->gps_mesg) == 0 )
				{
//					nca_dump_gprmc( ctx->gps_rmc );
				}
				else
				{
					memset( &ctx->gps_rmc, 0, sizeof(NC_GPS_GPRMC) );
//					nca_dump_gprmc( ctx->gps_rmc );
				}
			}
		}
		gps_data++;
	} while( *gps_data );

	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_gps_DataPut( char *gps_data, void *ctx_t )
{
	struct LDS_GPS_CTX *ctx;
	if( ctx_t == NULL )
		return 0;
	else
		ctx = ctx_t;

	if(gps_data == NULL)
	{
		return -1;
	}

	return lds_gps_ParseData( gps_data , ctx);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void *t_gps_monitoring(void *ctx_t)
{

	int			ret = 0;
	int			status = 0;
	char			*gprmc_start;
	char			*gprmc_end;

	const int		buf_size = 4096;
	unsigned char	buf[buf_size];	// Tx, Rx Buffer
	
	struct LDS_GPS_CTX *ctx;
	if( ctx_t == NULL )
		return 0;
	else
		ctx = ctx_t;
	
	gps_thread_start = 1;
	while(gps_thread_start)
	{
		while(!ctx->monitoring_start)
			sleep(1);

		ret = 0;
		memset( buf, 0, buf_size);

		ret = lds_hal_rs232.read(buf, buf_size );
		if( !ret )
		{
			memset( &ctx->gps_rmc, 0, sizeof(NC_GPS_GPRMC) );
			ctx->callback( &ctx->gps_rmc, sizeof(NC_GPS_GPRMC), GPS_DISCONNECT );
			goto END;
		}
		if( ((gprmc_start = strstr(buf, "$GPRMC")) != NULL) && ((gprmc_end = strstr(gprmc_start, "\n")) != NULL ))
		{
			*gprmc_end = '\0';

			lds_gps_DataPut(gprmc_start, ctx);
//			nca_gps_DataPut( "$GPRMC,055138.00,A,3729.22275,N,12701.99313,E,4.298,,281111,,,A*7C,A*542", ctx);

			if(ctx->gps_rmc.receive_ok)
			{
				ctx->callback( &ctx->gps_rmc, sizeof(NC_GPS_GPRMC), GPS_CONNECT_OKDATA );
			}
			else
			{
				ctx->callback( &ctx->gps_rmc, sizeof(NC_GPS_GPRMC), GPS_CONNECT_NODATA );
			}
				
		}
END:
		usleep(ctx->intaval);

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
static int lds_gps_monitoring_open(void *ctx_t)
{
	struct LDS_GPS_CTX *ctx;
	if( ctx_t == NULL )
		return -1;
	else
		ctx = ctx_t;

	if((pthread_create( &ctx->pthread, NULL, t_gps_monitoring, ctx)) < 0)
	{
		printf("[ERROR] gsensor thread create falie \n");
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
static int lds_gps_device_open(void * ctx_t)
{
	struct LDS_GPS_CTX *ctx;

	if( ctx_t == NULL )
		return -1;
	else
		ctx = ctx_t;


	if(ctx->ctx_gps != NULL)
	{
		return 0;
	}	
	
	ctx->ctx_gps = malloc( lds_hal_rs232.ctxsize );

	lds_hal_rs232.comm.lds_hal_open(GPS_DEVICE);

	lds_hal_rs232.ioctl(
		LDS_CTRL_RS232_BAUD, LDS_RS232_BAUD_9600,
		LDS_CTRL_RS232_READ_TIMEOUT, 5000,
		LDS_CTRL_RS232_WRITE_TIMEOUT, 5000,
		LDS_CTRL_RS232_END );

	return 0;
}
/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_gps_open(char *dev_name)
{
	memset( ctx, 0, sizeof(struct LDS_GPS_CTX));

	gps_thread_start = 0;
	lds_gps_device_open(ctx);
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_gps_close( int dev_fd)
{
	lds_hal_rs232.comm.lds_hal_close(dev_fd);
    
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_gps_start(void)
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
static int lds_gps_stop(void)
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
static int lds_gps_init(void)
{
    ctx = (struct LDS_GPS_CTX*)malloc( sizeof(struct LDS_GPS_CTX) );
    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_gps_deinit(void)
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
static unsigned int lds_gps_read(void *data,  int size)
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
static unsigned int lds_gps_write(unsigned char *data, unsigned int size)
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
static int lds_gps_control(LDS_CTRL_GPS type, ...)
{
	/* check maxctrl */
	if (type >= LDS_CTRL_GPS_MAX)
		return -1;

	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;
	while( cur_ctrl != LDS_CTRL_GPS_END )
	{
		switch(cur_ctrl)
		{
			case LDS_CTRL_GPS_MONITORING:
				{
					int param = va_arg(ctrl, int);
					ctx->monitoring_start = param;
				}
				break;
			case LDS_CTRL_GPS_CALLBACK:
				{
					int (*cb)(void *, int, int) = va_arg(ctrl, int (*)(void *, int, int));
					ctx->callback = cb;					
				}
				break;
			case LDS_CTRL_GPS_INTERVAL:
				{
					ctx->intaval = va_arg(ctrl, int);
				}
				break;
			case LDS_CTRL_GPS_START:
				{
					int *param = va_arg(ctrl, int*);
					
					if( lds_gps_monitoring_open(ctx) < 0)
					{
					 	*param = -1;
					}
					else
					{
						*param = 0;
					}
				}
				break;
			case LDS_CTRL_GPS_STOP:
				{
					int* param = va_arg(ctrl , int*);
					int ret = -1;
					gps_thread_start = 0;
					
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
					printf("[ERROR]  %s::%d >>> Bad CTRL Value = [%d] \n",__FUNCTION__, __LINE__,  cur_ctrl);
					assert((cur_ctrl >= LDS_CTRL_GPS_END) && (cur_ctrl < LDS_CTRL_GPS_MAX) );
				}
				break;
		}
		cur_ctrl = va_arg(ctrl, int);
	}

	va_end( ctrl );
 
	return 0;
}
struct LDS_GPS_OPERATION lds_hal_gps = {
		.name		    = "lds_hal_gps",
		.ctxsize		= sizeof(struct LDS_GPS_CTX),
		.maxctrl		= LDS_CTRL_GPS_MAX,

		.comm.lds_hal_open      = lds_gps_open,
		.comm.lds_hal_close     = lds_gps_close,
		.comm.lds_hal_start     = lds_gps_start,
		.comm.lds_hal_stop      = lds_gps_stop,
		.comm.lds_hal_init      = lds_gps_init,
		.comm.lds_hal_deinit    = lds_gps_deinit,
		.ioctl		            = lds_gps_control,
};