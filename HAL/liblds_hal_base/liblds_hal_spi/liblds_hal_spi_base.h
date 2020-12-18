#ifndef __IO_LDS_SPI_H__
#define __IO_LDS_SPI_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_SPI_ErrorNo{
	LDS_SPI_OPEN_ERROR,
	LDS_SPI_INIT_ERROR,
	LDS_SPI_START_ERROR,
}LDS_SPI_ErrorNo;

/* Define  --------------------------------------------------------------*/
typedef enum tagSPI_CTRL
{
	LDS_CTRL_SPI_END,
	LDS_CTRL_SPI_SET_HZ,
	LDS_CTRL_SPI_SET_VALUE,
	LDS_CTRL_SPI_MAX
}LDS_CTRL_SPI;


typedef struct _LDS_SPI_CTX
{
	char 			dev_name[64];
	LDS_SPI_ErrorNo	curr_err_state;
}LDS_SPI_CTX;

struct LDS_SPI_OPERATION
{
    struct LDS_HAL_COMMON base;
	const char		*name;

	/* common function */
	int				(*ioctl)		(LDS_SPI_CTX *ctx, LDS_CTRL_SPI type, ...);

	/* component dependent fuction */
};

/* Define variable  -----------------------------------------------------*/
extern struct LDS_SPI_OPERATION lds_hal_spi;

/* Define extern variable & function  -----------------------------------*/

#ifdef __cplusplus
}
#endif

#endif

