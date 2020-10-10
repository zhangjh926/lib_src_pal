#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_emmc_base.h"

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/

/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_emmc_open(char *dev_name)
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
static int lds_hal_emmc_close(int dev_fd)
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
static int lds_hal_emmc_init(void)
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
static int lds_hal_emmc_deinit(void)
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
static int lds_hal_emmc_start(void)
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
static int lds_hal_emmc_stop(void)
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
static int lds_hal_emmc_ioctl(LDS_CTRL_EMMC type, ...)
{
	switch(type)
	{
		default:
			break;
	}
	
	return 0;
}


struct LDS_EMMC_OPERATION lds_hal_emmc = {
    .name               = "lds_hal_emmc",
    .comm.lds_hal_open  = lds_hal_emmc_open,
    .comm.lds_hal_close = lds_hal_emmc_close,
    .comm.lds_hal_start = lds_hal_emmc_start,
    .comm.lds_hal_stop  = lds_hal_emmc_stop,
    .comm.lds_hal_init  = lds_hal_emmc_init,
    .comm.lds_hal_deinit= lds_hal_emmc_deinit,
    .ioctl              = lds_hal_emmc_ioctl,
};
