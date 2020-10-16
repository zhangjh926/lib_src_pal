#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_lcd_base.h"

/* Define  -------------------------------------------------------------------*/
struct LDS_LCD_CTX{
    LDS_LCD_ErrorNo curr_err_state;
};

/* Define variable  ----------------------------------------------------------*/
static struct LDS_LCD_CTX ctx;
/* Define extern variable & function  ----------------------------------------*/


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_lcd_open(char *dev_name)
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
static int lds_hal_lcd_close(int dev_fd)
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
static int lds_hal_lcd_init(void *param)
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
static int lds_hal_lcd_deinit(void)
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
static int lds_hal_lcd_start(void)
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
static int lds_hal_lcd_stop(void)
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
static int lds_hal_lcd_get_error(void)
{
    return ctx.curr_err_state;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_lcd_ioctl(LDS_CTRL_LCD type, ...)
{
	switch(type)
	{
		default:
			break;
	}
	
	return 0;
}


struct LDS_LCD_OPERATION lds_hal_lcd = {
    .name                   = "lds_hal_lcd",
    .comm.lds_hal_open      = lds_hal_lcd_open,
    .comm.lds_hal_close     = lds_hal_lcd_close,
    .comm.lds_hal_start     = lds_hal_lcd_start,
    .comm.lds_hal_stop      = lds_hal_lcd_stop,
    .comm.lds_hal_init      = lds_hal_lcd_init,
    .comm.lds_hal_deinit    = lds_hal_lcd_deinit,
    .comm.lds_hal_get_error = lds_hal_lcd_get_error,
    .ioctl                  = lds_hal_lcd_ioctl,
};