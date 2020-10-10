#ifndef __IO_LDS_SPI_H__
#define __IO_LDS_SPI_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif

/* Header file include --------------------------------------------------*/

/* Define  --------------------------------------------------------------*/
typedef enum tagSPI_CTRL
{
	LDS_CTRL_SPI_END,
	LDS_CTRL_SPI_SET_HZ,
	LDS_CTRL_SPI_SET_VALUE,
	LDS_CTRL_SPI_MAX
}LDS_CTRL_SPI;

struct LDS_SPI_OPERATION
{
    struct LDS_HAL_COMMON comm;
	const char		*name;

	/* common function */
	int				(*ioctl)		(LDS_CTRL_SPI type, ...);

	/* component dependent fuction */
};

/* Define variable  -----------------------------------------------------*/
extern struct LDS_SPI_OPERATION lds_hal_spi;

/* Define extern variable & function  -----------------------------------*/

#ifdef __cplusplus
}
#endif

#endif

