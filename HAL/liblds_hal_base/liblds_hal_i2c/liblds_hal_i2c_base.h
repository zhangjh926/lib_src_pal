#ifndef __LDS_I2C_H__
#define __LDS_I2C_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_I2C_ErrorNo{
	LDS_I2C_OPEN_ERROR,
	LDS_I2C_INIT_ERROR,
	LDS_I2C_START_ERROR,
}LDS_I2C_ErrorNo;

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

typedef struct _LDS_I2C_CTX
{
	int					slave_addr;
	int					addr_register;
	int					reg_length;
	int					data_length;
	char				reg_address[4];
	char				i2c_name[12];
	LDS_I2C_ErrorNo		curr_err_state;
}LDS_I2C_CTX;

struct LDS_I2C_OPERATION
{
    struct LDS_HAL_COMMON base;
	const char		*name;
	/* common function */
	int				(*read)			(LDS_I2C_CTX *ctx_t, int fd, void *data, unsigned int size );
	int				(*write)		(LDS_I2C_CTX *ctx_t, int fd, void *data, unsigned int size );
	int				(*ioctl)		(LDS_I2C_CTX *ctx_t, LDS_CTRL_I2C type, ...);
};


/* Define variable  -----------------------------------------------------*/
extern struct LDS_I2C_OPERATION lds_hal_i2c;

/* Define extern variable & function  -----------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __NCH_I2C_H__ */

