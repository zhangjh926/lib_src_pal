#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_flash_base.h"

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/
static LDS_FLASH_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_flash_open(void *ctx_t, void *param)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

    return 0;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_flash_close(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

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
static int lds_hal_flash_deinit(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_flash_start(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

    return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_flash_stop(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

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
static int 	lds_hal_flash_copy(LDS_FLASH_CTX *ctx, char *filename, char *dev_name)
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
static int	lds_hal_flash_erase(LDS_FLASH_CTX *ctx, char *dev_name, unsigned long start_addr, unsigned int erase_block_count, int lock)
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
static int	lds_hal_flash_eraseall(LDS_FLASH_CTX *ctx, char *dev_name, int is_formated_jffs2)
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
static int	lds_hal_flash_read(LDS_FLASH_CTX *ctx, char *dev_name, unsigned int offset, char *out_data)
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
static int	lds_hal_flash_write(LDS_FLASH_CTX *ctx, char *dev_name, unsigned int offset, char *in_data)
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
static int	lds_hal_flash_dump(LDS_FLASH_CTX *ctx, char *filename, char *output_data)
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
static int	lds_hal_flash_compare(LDS_FLASH_CTX *ctx, char *source_file_name, char *new_file_name)
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
static int	lds_hal_flash_get_error(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

    return ctx->curr_err_state;
}


struct LDS_FLASH_OPERATION lds_hal_flash = {
    .name                   = "lds_hal_flash",
    .base.lds_hal_open      = lds_hal_flash_open,
    .base.lds_hal_close     = lds_hal_flash_close,
    .base.lds_hal_start     = lds_hal_flash_start,
    .base.lds_hal_stop      = lds_hal_flash_stop,
    .base.lds_hal_get_error = lds_hal_flash_get_error,
    .lds_hal_flash_copy     = lds_hal_flash_copy,
	.lds_hal_flash_erase    = lds_hal_flash_erase,
	.lds_hal_flash_eraseall = lds_hal_flash_eraseall,
	.lds_hal_flash_read     = lds_hal_flash_read,
	.lds_hal_flash_write    = lds_hal_flash_write,
	.lds_hal_flash_dump     = lds_hal_flash_dump,
	.lds_hal_flash_compare  = lds_hal_flash_compare,
};

