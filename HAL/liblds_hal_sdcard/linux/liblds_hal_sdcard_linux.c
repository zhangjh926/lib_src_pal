#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <fcntl.h>

#include "liblds_hal_sdcard_base.h"

/* Define  -------------------------------------------------------------------*/
struct LDS_SDCARD_CTX{
    LDS_SDCARD_ErrorNo curr_err_state;
};

/* Define variable  ----------------------------------------------------------*/
static struct LDS_SDCARD_CTX ctx;
/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_sdcard_open(char *dev_name)
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
static int lds_hal_sdcard_close(int dev_fd)
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
static int lds_hal_sdcard_init(void *param)
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
static int lds_hal_sdcard_deinit(void)
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
static int lds_hal_sdcard_start(void)
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
static int lds_hal_sdcard_stop(void)
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
static int lds_hal_sdcard_get_total_space(void)
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
static int lds_hal_sdcard_get_free_space(void)
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
static SDCardState  lds_hal_sdcard_get_state(void)
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
static SDCardFsType lds_hal_sdcard_get_filesystem_type(void)
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
static int lds_hal_sdcard_set_format(SDCardFsType fs_type)
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
static int lds_hal_sdcard_fallocate(int fd, int mode, unsigned long offset, unsigned long len)
{
    //return fallocate(fd, mode, (off_t)offset, (off_t)len);
    return 0;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_sdcard_get_error(void)
{
    return ctx.curr_err_state;
}


struct LDS_SDCARD_OPERATION         lds_hal_sdcard = {
    .name                           = "lds_hal_sdcard",
    .comm.lds_hal_open              = lds_hal_sdcard_open,
    .comm.lds_hal_close             = lds_hal_sdcard_close,
    .comm.lds_hal_start             = lds_hal_sdcard_start,
    .comm.lds_hal_stop              = lds_hal_sdcard_stop,
    .comm.lds_hal_init              = lds_hal_sdcard_init,
    .comm.lds_hal_deinit            = lds_hal_sdcard_deinit,
    .comm.lds_hal_get_error         = lds_hal_sdcard_get_error,
    .lds_hal_sdcard_get_total_space = lds_hal_sdcard_get_total_space,
    .lds_hal_sdcard_get_free_space  = lds_hal_sdcard_get_free_space,
    .lds_hal_sdcard_get_state       = lds_hal_sdcard_get_state,
    .lds_hal_sdcard_get_filesystem_type = lds_hal_sdcard_get_filesystem_type,
    .lds_hal_sdcard_set_format      = lds_hal_sdcard_set_format,
    .lds_hal_sdcard_fallocate       = lds_hal_sdcard_fallocate,
};