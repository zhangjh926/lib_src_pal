#ifndef __IO_LDS_PIR_H__
#define __IO_LDS_PIR_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif

/* Header file include --------------------------------------------------*/

typedef enum   _LDS_PIR_ErrorNo{
	LDS_PIR_OPEN_ERROR,
	LDS_PIR_INIT_ERROR,
	LDS_PIR_START_ERROR,
}LDS_PIR_ErrorNo;

/* Define  --------------------------------------------------------------*/
typedef enum tagPIR_CTRL
{
	LDS_CTRL_PIR_END,
	LDS_CTRL_PIR_SET_INTERRUPT,
	LDS_CTRL_PIR_SET_CALLBACK,
	LDS_CTRL_PIR_MAX
}LDS_CTRL_PIR;

struct LDS_PIR_OPERATION
{
    struct LDS_HAL_COMMON comm;
	const char		*name;

	/* common function */
	int				(*ioctl)		(LDS_CTRL_PIR type, ...);

	/* component dependent fuction */
};

/* Define variable  -----------------------------------------------------*/
extern struct LDS_PIR_OPERATION lds_hal_pir;

/* Define extern variable & function  -----------------------------------*/

#ifdef __cplusplus
}
#endif


#endif 