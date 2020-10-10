#ifndef __LDS_I2C_H__
#define __LDS_I2C_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif

typedef enum tagCTRL_I2C
{
	LDS_CTRL_I2C_END,
	LDS_CTRL_I2C_SLAVE_ADDRESS,
	LDS_CTRL_I2C_REGISTER_ADDRESS,
	LDS_CTRL_I2C_REGISTER_ADDRESS_LENGTH,
	LDS_CTRL_I2C_REGISTER_DATA_LENGTH,
	LDS_CTRL_I2C_SET,
	LDS_CTRL_I2C_GET,
	LDS_CTRL_I2C_TOGLE,
	LDS_CTRL_I2C_SET_I2CNUM,
	LDS_CTRL_I2C_FDOPEN,
	LDS_CTRL_I2C_MAX
}LDS_CTRL_I2C;

struct LDS_I2C_OPERATION
{
    struct LDS_HAL_COMMON comm;
	const char		*name;
	int				ctxsize;
	int				maxctrl;

	/* common function */
	int				(*read)			(int fd, void *data, unsigned int size );
	int				(*write)		(int fd, void *data, unsigned int size );
	int				(*ioctl)		(LDS_CTRL_I2C type, ...);
};


/* Define variable  -----------------------------------------------------*/
extern struct LDS_I2C_OPERATION lds_hal_i2c;

/* Define extern variable & function  -----------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __NCH_I2C_H__ */

