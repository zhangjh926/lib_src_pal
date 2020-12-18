#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <fcntl.h>
#include <sys/vfs.h>

#include "liblds_hal_sdcard_base.h"

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/
static LDS_SDCARD_CTX *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_sdcard_open(void *ctx_t, void *param)
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
static int lds_hal_sdcard_close(void *ctx_t)
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
static int lds_hal_sdcard_deinit(void *ctx_t)
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
static int lds_hal_sdcard_start(void *ctx_t)
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
static int lds_hal_sdcard_stop(void *ctx_t)
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
static int lds_hal_sdcard_get_total_space(LDS_SDCARD_CTX *ctx, char *mount_path)
{
    struct statfs mystatfs;
    int    total_size = 0;
    if (statfs(mount_path, &mystatfs) == -1){
        perror("get total space fail...\n");
        return -1;
    }

    total_size = (((long long)mystatfs.f_bsize * (long long)mystatfs.f_blocks) /
                 (long long) 1024 / (long long) 1024);

    return total_size;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_sdcard_get_free_space(LDS_SDCARD_CTX *ctx, char *mount_path)
{
    struct statfs mystatfs;
    int    free_size = 0;
    if (statfs(mount_path, &mystatfs) == -1){
        perror("get free space fail...\n");
        return -1;
    }

    free_size = (((long long)mystatfs.f_bsize * (long long)mystatfs.f_bfree) /
                 (long long) 1024 / (long long) 1024);

    return free_size;
}


/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static SDCardState  lds_hal_sdcard_get_state(LDS_SDCARD_CTX *ctx, LDS_SDCARD_STATE_CALLBACK state_callback)
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
static SDCardFsType lds_hal_sdcard_get_filesystem_type(LDS_SDCARD_CTX *ctx)
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
static int lds_hal_sdcard_set_format(LDS_SDCARD_CTX *ctx, SDCardFsType fs_type)
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
static int lds_hal_sdcard_fallocate(LDS_SDCARD_CTX *ctx, int fd, int mode, unsigned long offset, unsigned long len)
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
static int lds_hal_sdcard_get_error(void *ctx_t)
{
    if(NULL == ctx_t) return -1;
    else ctx = ctx_t;

    return ctx->curr_err_state;
}


struct LDS_SDCARD_OPERATION         lds_hal_sdcard = {
    .name                           = "lds_hal_sdcard",
    .base.lds_hal_open              = lds_hal_sdcard_open,
    .base.lds_hal_close             = lds_hal_sdcard_close,
    .base.lds_hal_start             = lds_hal_sdcard_start,
    .base.lds_hal_stop              = lds_hal_sdcard_stop,
    .base.lds_hal_get_error         = lds_hal_sdcard_get_error,
    .lds_hal_sdcard_get_total_space = lds_hal_sdcard_get_total_space,
    .lds_hal_sdcard_get_free_space  = lds_hal_sdcard_get_free_space,
    .lds_hal_sdcard_get_state       = lds_hal_sdcard_get_state,
    .lds_hal_sdcard_get_filesystem_type = lds_hal_sdcard_get_filesystem_type,
    .lds_hal_sdcard_set_format      = lds_hal_sdcard_set_format,
    .lds_hal_sdcard_fallocate       = lds_hal_sdcard_fallocate,
};