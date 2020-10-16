#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_flash_base.h"

/* Define  -------------------------------------------------------------------*/
struct LDS_FLASH_CTX{
    LDS_FLASH_ErrorNo curr_err_state;
};
/* Define variable  ----------------------------------------------------------*/
static struct LDS_FLASH_CTX ctx;
/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_flash_open(char *dev_name)
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
static int lds_hal_flash_close(int dev_fd)
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
static int lds_hal_flash_init(void *param)
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
static int lds_hal_flash_deinit(void)
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
static int lds_hal_flash_start(void)
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
static int lds_hal_flash_stop(void)
{
    return 0;
}

#if 0
/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_flash_ioctl(LDS_CTRL_FLASH type, ...)
{
	switch(type)
	{
		default:
			break;
	}
	
	return 0;
}
#endif

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int 	lds_hal_flash_copy(char *filename, char *dev_name)
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
static int	lds_hal_flash_erase(char *dev_name, unsigned long start_addr, unsigned int erase_block_count, int lock)
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
static int	lds_hal_flash_eraseall(char *dev_name, int is_formated_jffs2)
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
static int	lds_hal_flash_read(char *dev_name, unsigned int offset, char *out_data)
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
static int	lds_hal_flash_write(char *dev_name, unsigned int offset, char *in_data)
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
static int	lds_hal_flash_dump(char *filename, char *output_data)
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
static int	lds_hal_flash_compare(char *source_file_name, char *new_file_name)
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
static int	lds_hal_flash_get_error(void)
{
    return ctx.curr_err_state;
}


struct LDS_FLASH_OPERATION lds_hal_flash = {
    .name                   = "lds_hal_flash",
    .comm.lds_hal_open      = lds_hal_flash_open,
    .comm.lds_hal_close     = lds_hal_flash_close,
    .comm.lds_hal_start     = lds_hal_flash_start,
    .comm.lds_hal_stop      = lds_hal_flash_stop,
    .comm.lds_hal_init      = lds_hal_flash_init,
    .comm.lds_hal_deinit    = lds_hal_flash_deinit,
    .comm.lds_hal_get_error = lds_hal_flash_get_error,
    .lds_hal_flash_copy     = lds_hal_flash_copy,
	.lds_hal_flash_erase    = lds_hal_flash_erase,
	.lds_hal_flash_eraseall = lds_hal_flash_eraseall,
	.lds_hal_flash_read     = lds_hal_flash_read,
	.lds_hal_flash_write    = lds_hal_flash_write,
	.lds_hal_flash_dump     = lds_hal_flash_dump,
	.lds_hal_flash_compare  = lds_hal_flash_compare,
};

