
#ifndef __LDS_GPS_H__
#define __LDS_GPS_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif
/* Header file include --------------------------------------------------*/

/* Define  --------------------------------------------------------------*/
typedef enum tagLDS_GPS_STATUS
{
	GPS_DISCONNECT	=	0,
	GPS_CONNECT_NODATA,
	GPS_CONNECT_OKDATA,
}LDS_GPS_STATUS;

typedef struct	tagGPS_GPRMC
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

struct LDS_GPS_OPERATION
{
    struct LDS_HAL_COMMON comm;
	const char		*name;
	int				ctxsize;
	int				maxctrl;

	int				(*ioctl)		(LDS_CTRL_GPS type, ...);
};

/* Define variable  -----------------------------------------------------*/
extern struct LDS_GPS_OPERATION lds_hal_gps;

#ifdef __cplusplus
}
#endif

#endif

