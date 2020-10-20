#ifndef __IO_LDS_KEY_H__
#define __IO_LDS_KEY_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_KEY_ErrorNo{
	LDS_KEY_OPEN_ERROR,
	LDS_KEY_INIT_ERROR,
	LDS_KEY_START_ERROR,
}LDS_KEY_ErrorNo;

typedef enum tagKEY_CTRL
{
	LDS_CTRL_KEY_END,
	LDS_CTRL_KEY_CALLBACK,
	LDS_CTRL_KEY_INTERVAL,
	LDS_CTRL_KEY_MONITORING,
	LDS_CTRL_KEY_START,
	LDS_CTRL_KEY_STOP,
	LDS_CTRL_KEY_MAX
}LDS_CTRL_KEY;

typedef enum tagKEY_STATUS
{
	LDS_CTRL_KEY_PRESS,	// pressed
	LDS_CTRL_KEY_RELEASE,	// released
	LDS_CTRL_KEY_PRESSING// keep pressing
}LDS_KEY_STATUS;

struct LDS_KEY_OPERATION
{
    struct LDS_HAL_COMMON comm;
	const char		*name;
	int				ctxsize;
	int				maxctrl;

	int				(*ioctl)			(LDS_CTRL_KEY type, ...);

};

extern struct LDS_KEY_OPERATION lds_key_gpio;
extern struct LDS_KEY_OPERATION lds_key_dev;

#ifdef __cplusplus
}
#endif

#endif /* __NCA_KEY_H__ */

