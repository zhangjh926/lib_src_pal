#ifndef _LDS_ADC_OPERATION_H
#define _LDS_ADC_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_ADC_ErrorNo{
	LDS_ADC_OPEN_ERROR,
	LDS_ADC_INIT_ERROR,
	LDS_ADC_START_ERROR,
}LDS_ADC_ErrorNo;


typedef enum tagADC_INTERRUPT
{
	LDS_ADC_INTERRUPT_CLOSE = 0,
	LDS_ADC_INTERRUPT_OPEN,
}LDS_ADC_INTERRUPT;


typedef enum tagCTRL_ADC
{
	LDS_CTRL_ADC_END,
	LDS_CTRL_ADC_SET_INTERRUPT,
	LDS_CTRL_ADC_SET_THRESHOLD,
	LDS_CTRL_ADC_GET_VALUE,
	LDS_CTRL_ADC_MAX
}LDS_CTRL_ADC;

typedef struct _LDS_ADC_CXT{
	char adc_interrupt[128];
	char adc_thresf_rise[128];
	char adc_thresf_fail[128];
	char adc_dev[128];
	LDS_ADC_ErrorNo curr_err_state;
}LDS_ADC_CTX;

/*
	LDS_CTRL_ADC_GET_VALUE
*/
struct LDS_ADC_OPERATION
{
    struct 			LDS_HAL_COMMON base;
       
	const 			char		  *name;
    
	int				(*ioctl)    (LDS_ADC_CTX *ctx_t, LDS_CTRL_ADC type, ...);
};

extern struct LDS_ADC_OPERATION lds_hal_adc;


#ifdef __cplusplus
}
#endif

#endif
