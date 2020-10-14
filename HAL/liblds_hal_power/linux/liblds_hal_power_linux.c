#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_power_base.h"

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/

/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
 * *	Description		:
 * *	Argurments		:
 * *	Return value	:
 * *	Modify			:
 * *	warning			:
 * *******************************************************************************/
static int lds_hal_power_open(char *dev_name)
{
	return 0;
}


/*******************************************************************************
 * *	Description		:
 * *	Argurments		:
 * *	Return value	:
 * *	Modify			:
 * *	warning			:
 * *******************************************************************************/
static int lds_hal_power_close(int dev_fd)
{
	return 0;
}

/*******************************************************************************
 * *	Description		:
 * *	Argurments		:
 * *	Return value	:
 * *	Modify			:
 * *	warning			:
 * *******************************************************************************/
static int lds_hal_power_init(void *param)
{
	return 0;
}

/*******************************************************************************
 * *	Description		:
 * *	Argurments		:
 * *	Return value	:
 * *	Modify			:
 * *	warning			:
 * *******************************************************************************/
static int lds_hal_power_deinit(void)
{
	return 0;
}

/*******************************************************************************
 * *	Description		:
 * *	Argurments		:
 * *	Return value	:
 * *	Modify			:
 * *	warning			:
 * *******************************************************************************/
static int lds_hal_power_start(void)
{
	return 0;
}

/*******************************************************************************
 * *	Description		:
 * *	Argurments		:
 * *	Return value	:
 * *	Modify			:
 * *	warning			:
 * *******************************************************************************/
static int lds_hal_power_stop(void)
{
	return 0;
}

/*******************************************************************************
 * *	Description		:
 * *	Argurments		:
 * *	Return value	:
 * *	Modify			:
 * *	warning			:
 * *******************************************************************************/
static int lds_hal_power_ioctl(LDS_CTRL_POWER type, ...)
{
	switch(type)
	{
	default:
		break;
	}

	return 0;
}


struct LDS_POWER_OPERATION lds_hal_power = {
	.name               = "lds_hal_power",
	.comm.lds_hal_open  = lds_hal_power_open,
	.comm.lds_hal_close = lds_hal_power_close,
	.comm.lds_hal_start = lds_hal_power_start,
	.comm.lds_hal_stop  = lds_hal_power_stop,
	.comm.lds_hal_init  = lds_hal_power_init,
	.comm.lds_hal_deinit= lds_hal_power_deinit,
	.ioctl              = lds_hal_power_ioctl,
};
