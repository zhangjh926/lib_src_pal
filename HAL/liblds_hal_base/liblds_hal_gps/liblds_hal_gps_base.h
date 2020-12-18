
#ifndef __LDS_GPS_H__
#define __LDS_GPS_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif
/* Header file include --------------------------------------------------*/

typedef enum   _LDS_GPS_ErrorNo{
	LDS_GPS_OPEN_ERROR,
	LDS_GPS_INIT_ERROR,
	LDS_GPS_START_ERROR,
}LDS_GPS_ErrorNo;

/* Define  --------------------------------------------------------------*/
typedef enum 	_LDS_GPS_STATUS
{
	GPS_DISCONNECT	=	0,
	GPS_CONNECT_NODATA,
	GPS_CONNECT_OKDATA,
}LDS_GPS_STATUS;

typedef struct 	_LDS_GPS_GPRMC
{
	unsigned char	date_dd;
	unsigned char	date_mm;
	unsigned char	date_yy;

	unsigned char	utc_hh;
	unsigned char	utc_mm;
	unsigned char	utc_ss;

	unsigned char	receive_ok;

	float			latitude_deg;
	unsigned char	latitude_dir;

	float			longitude_deg;
	unsigned char	longitude_dir;

	float			node_speed;
	float			mph_speed;
	float			kmh_speed;

} NC_GPS_GPRMC, *PNC_GPS_GPRMC;

typedef struct	tagGPS_MESG
{
    unsigned char	data[50][20];
    unsigned char	data_num;
} NC_GPS_MESG, *PNC_GPS_MESG;

typedef enum tagGPS_CTRL
{
	LDS_CTRL_GPS_END,
	LDS_CTRL_GPS_CALLBACK,
	LDS_CTRL_GPS_INTERVAL,
	LDS_CTRL_GPS_MONITORING,
	LDS_CTRL_GPS_START,
	LDS_CTRL_GPS_STOP,
	LDS_CTRL_GPS_MAX
}LDS_CTRL_GPS;

typedef struct _LDS_GPS_CTX
{
	int					(*callback)(void *, int, int);
	char				dev_name[64];
	pthread_t			pthread;
	int					monitoring_start;
	int					intaval;
	NC_GPS_MESG 		gps_mesg;
	NC_GPS_GPRMC		gps_rmc;
	LDS_GPS_ErrorNo		curr_err_state;
}LDS_GPS_CTX;

struct LDS_GPS_OPERATION
{
    struct LDS_HAL_COMMON base;
	const char		*name;

	int				(*ioctl)		(LDS_GPS_CTX *ctx_t, LDS_CTRL_GPS type, ...);
};

/* Define variable  -----------------------------------------------------*/
extern struct LDS_GPS_OPERATION lds_hal_gps;

#ifdef __cplusplus
}
#endif

#endif

