#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "liblds_hal_adc_base.h"


/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/
// static struct LDS_ADC_CXT *adc_ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_adc_open(void *ctx_t, void *param)
{
	if(NULL == ctx_t){
		return -1;
	}

	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_adc_close(void *ctx_t)
{
	if(NULL == ctx_t){
		return -1;
	}
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_adc_start(void *ctx_t)
{
	if(NULL == ctx_t){
		return -1;
	}
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_adc_init(void *param)
{
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_adc_deinit(void *ctx_t)
{
	if(NULL == ctx_t) return -1;

	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_adc_stop(void *ctx_t)
{
	if(NULL == ctx_t){
		return -1;
	}
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_adc_get_error(void*ctx_t)
{
	LDS_ADC_CTX * ctx = NULL;

	if(NULL == ctx_t) return -1;
	else ctx = ctx_t;

	return ctx->curr_err_state;
}



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_set_adc_interrupt(LDS_ADC_CTX *ctx_t, int set_value){
	
	int ret = 0;
	int sys_fd;
	LDS_ADC_CTX * ctx = NULL;

	if(NULL == ctx_t) return -1;
	ctx = ctx_t;

	if( (set_value < LDS_ADC_INTERRUPT_CLOSE) || (set_value > LDS_ADC_INTERRUPT_OPEN) )
	{
		printf("[ERROR] wrong set_value [%d] \n", set_value);
		return -1;
	}


	sys_fd = open(ctx->adc_interrupt, O_WRONLY);
	if( sys_fd < 0){
		perror("Open sys error\n");
		ret =  -2;
	}else{
		if(set_value == LDS_ADC_INTERRUPT_CLOSE){
			ret=  write(sys_fd, "0", 1);
			printf("close_adc_interrupt ret = %d \r\n",ret ); 
		}else if( set_value == LDS_ADC_INTERRUPT_OPEN ){
			ret=  write(sys_fd, "1", 1);
			printf("open_adc_interrupt ret = %d \r\n",ret ); 
		}
		
		if(ret < 0 ){
			ret = -3;
		}else{
			//printf("adc_value= %d \r\n",ret );
			ret = 0;
		}
		close(sys_fd);
	}
	
	return ret ;
}




/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/

static int lds_hal_set_adc_thresh_value(LDS_ADC_CTX *ctx_t, int thresh_value){
	
	int ret = 0;
	int write_size = 0;
	int sys_fd;
	char adc_thresh_value[10];
	LDS_ADC_CTX *ctx = NULL;
	
	if(NULL == ctx_t) return -1;
	ctx = ctx_t;

	if( thresh_value < 0){
		printf(" thresh_value < 0 \r\n" );
		return - 1;
	}
	
	memset(adc_thresh_value, 0 , sizeof(adc_thresh_value));
	
	write_size = sprintf(adc_thresh_value,"%d",thresh_value);////3v 4096   1v 1241 4d9
	
	printf("write_size = %d  adc_thresh_value =%s\r\n",write_size ,adc_thresh_value);
	
	
	sys_fd = open(ctx->adc_thresf_fail, O_WRONLY);
	if( sys_fd < 0){
		perror("Open sys error\n");
		ret =  -2;
	}else{
		
		//printf("sizeof(adc_value) = %d\r\n",sizeof(adc_value));
		ret=  write(sys_fd, adc_thresh_value, write_size);
		printf("write adc  thresh ret = %d \r\n",ret ); 
		if(ret < 0 ){
			ret = -3;
		}else{
			//printf("adc_value= %d \r\n",ret );
			ret = 0;
		}
		close(sys_fd);
	}
	
	return ret ;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/

static int lds_hal_read_adc_value(LDS_ADC_CTX *ctx_t){
	
	int ret = 0;
	int sys_fd;
	char adc_value[10];
	LDS_ADC_CTX *ctx = NULL;

	if(NULL == ctx_t ) return -1;
	ctx = ctx_t;

	sys_fd = open(ctx->adc_dev, O_RDONLY);
	if( sys_fd < 0){
		perror("Open sys error\n");
		ret =  -1;
	}else{
		
		//printf("sizeof(adc_value) = %d\r\n",sizeof(adc_value));
		ret=  read(sys_fd, adc_value, sizeof(adc_value));
		//printf("read adc ret = %d \r\n",ret ); 
		if(ret < 0 ){
			ret = -2;
		}else{
			ret = atoi(adc_value);
			if(ret < 0){
				ret -3;
			}else{
				//printf("adc_value= %d \r\n",ret ); //// 3v 4096   1v 1241 4d9
			}

		}
		close(sys_fd);
	}
	
	return ret ;
}





/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/

static int lds_hal_adc_ioctl(LDS_ADC_CTX *ctx_t, LDS_CTRL_ADC type, ...)
{
	int ret = 0;
	LDS_ADC_CTX *ctx = NULL;
	/* check maxctrl */
	if (type >= LDS_CTRL_ADC_MAX)
		return ret;


	if(NULL == ctx_t) return -1;
	ctx = ctx_t;

	/* Parse multi param */
	va_list ctrl;
	int		cur_ctrl;

	va_start (ctrl, type );
	cur_ctrl = type;
	while( cur_ctrl != LDS_CTRL_ADC_END ){
		switch(cur_ctrl){
			case LDS_CTRL_ADC_SET_INTERRUPT:{
					int param = va_arg(ctrl, int);
					ret = lds_hal_set_adc_interrupt(ctx, param);
				}
				break;
			case LDS_CTRL_ADC_SET_THRESHOLD:{
					int param = va_arg(ctrl, int );
					ret = lds_hal_set_adc_thresh_value(ctx ,param);
				}
				break;
			case LDS_CTRL_ADC_GET_VALUE:{
					int * param = va_arg(ctrl, int *);
					
					ret = lds_hal_read_adc_value(ctx);
					if( ret >= 0 ){
						*param = ret ;
						ret = 0;
					}else{
						*param = 0 ;
						ret = -1;
					}
					
				}
				break;
		}
		cur_ctrl = va_arg(ctrl, int);
	}
	va_end( ctrl );

	return ret;
}







struct LDS_ADC_OPERATION  lds_hal_adc = {
	.name                       = "LDS_HAL_ADC",
	.base.lds_hal_open          = lds_hal_adc_open,
	.base.lds_hal_close         = lds_hal_adc_close,
	.base.lds_hal_start         = lds_hal_adc_start,
	.base.lds_hal_stop          = lds_hal_adc_stop,
	.base.lds_hal_get_error		= lds_hal_adc_get_error,
	.ioctl                      = lds_hal_adc_ioctl, 
	
};
