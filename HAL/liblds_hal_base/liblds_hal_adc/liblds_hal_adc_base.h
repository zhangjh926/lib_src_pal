#ifndef _LDS_ADC_OPERATION_H
#define _LDS_ADC_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum tagCTRL_ADC
{
	LDS_CTRL_ADC_END,
	LDS_CTRL_ADC_GET_VALUE,
	LDS_CTRL_ADC_MAX
}LDS_CTRL_ADC;


/*
	LDS_CTRL_ADC_GET_VALUE
*/
struct LDS_ADC_OPERATION
{
    struct LDS_HAL_COMMON comm;
       
	const char		*name;
    
	int				(*ioctl)    (LDS_CTRL_ADC type, ...);
};

extern struct LDS_ADC_OPERATION lds_hal_adc;


#ifdef __cplusplus
}
#endif

#endif
