#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_video_decode_base.h"

/* Define  -------------------------------------------------------------------*/
/* Define variable  ----------------------------------------------------------*/
static LDS_VIDDEC_CONTEXT *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_video_open(void *ctx_t, void *param)
{
    if(NULL == ctx) return -1;
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
static int lds_hal_video_close(void *ctx_t)
{
    if(NULL == ctx) return -1;
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
static int lds_hal_video_start(void *ctx_t)
{
    if(NULL == ctx) return -1;
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
static int lds_hal_video_stop(void *ctx_t)
{
    if(NULL == ctx) return -1;
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
static int lds_hal_video_init(void *param)
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
static int lds_hal_video_deinit(void *ctx_t)
{
    if(NULL == ctx) return -1;
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
static int lds_hal_video_get_error(void *ctx_t)
{
    if(NULL == ctx) return -1;
    else ctx = ctx_t;

    return ctx->curr_state;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_playback_video_callback(LDS_PLAYBACK_VIDEO_FRAME capture_buffer)
{
    return 0;
}

/*******************************************************************************
*   Description     :
*   Argurments      :
*   Return value    :
*   Modify          :
*   warning         :
*******************************************************************************/
static int lds_hal_playback_set_param(LDS_PLAYBACK_VIDEO_FRAME capture_buffer)
{
    return 0;
}

/*******************************************************************************
*   Description     :
*   Argurments      :
*   Return value    :
*   Modify          :
*   warning         :
*******************************************************************************/
static int lds_hal_playback_set_seek(LDS_VIDDEC_CONTEXT *ctx, int file_idx, int ms)
{
    return 0;
}

/*******************************************************************************
*   Description     :
*   Argurments      :
*   Return value    :
*   Modify          :
*   warning         :
*******************************************************************************/
static int lds_hal_playback_set_play(LDS_VIDDEC_CONTEXT *ctx, int file_idx)
{
    return 0;
}

/*******************************************************************************
*   Description     :
*   Argurments      :
*   Return value    :
*   Modify          :
*   warning         :
*******************************************************************************/
static int lds_hal_playback_set_pause(LDS_VIDDEC_CONTEXT *ctx, int file_idx)
{
    return 0;
}

/*******************************************************************************
*   Description     :
*   Argurments      :
*   Return value    :
*   Modify          :
*   warning         :
*******************************************************************************/
static int lds_hal_playback_set_stop(LDS_VIDDEC_CONTEXT *ctx, int file_idx)
{
    return 0;
}

/*******************************************************************************
*   Description     :
*   Argurments      :
*   Return value    :
*   Modify          :
*   warning         :
*******************************************************************************/
static int lds_hal_playback_get_total_time(LDS_VIDDEC_CONTEXT *ctx, int file_idx)
{
    return 0;
}

/*******************************************************************************
*   Description     :
*   Argurments      :
*   Return value    :
*   Modify          :
*   warning         :
*******************************************************************************/
static int lds_hal_playback_get_curr_time(LDS_VIDDEC_CONTEXT *ctx,  int file_idx)
{
    return 0;
}

/*******************************************************************************
*   Description     :
*   Argurments      :
*   Return value    :
*   Modify          :
*   warning         :
*******************************************************************************/
static int lds_hal_playback_get_play_state(LDS_VIDDEC_CONTEXT *ctx, int file_idx)
{
    return 0;
}

/*******************************************************************************
*   Description     :
*   Argurments      :
*   Return value    :
*   Modify          :
*   warning         :
*******************************************************************************/
static int lds_hal_playback_get_file_count(LDS_VIDDEC_CONTEXT *ctx)
{
    return 0;
}


struct LDS_VIDEO_DECODE_OPERATION lds_hal_video_decoder = {
    .name                            = "lds_hal_video_decoder",
    .base.lds_hal_open               = lds_hal_video_open,
    .base.lds_hal_close              = lds_hal_video_close,
    .base.lds_hal_start              = lds_hal_video_start,
    .base.lds_hal_stop               = lds_hal_video_stop,
    .base.lds_hal_get_error          = lds_hal_video_get_error,
    .lds_hal_playback_video_callback = lds_hal_playback_video_callback,
    .lds_hal_playback_set_param      = lds_hal_playback_set_param,
    .lds_hal_playback_set_seek       = lds_hal_playback_set_seek,
    .lds_hal_playback_set_play       = lds_hal_playback_set_play,
    .lds_hal_playback_set_pause      = lds_hal_playback_set_pause,
    .lds_hal_playback_set_stop       = lds_hal_playback_set_stop,
    .lds_hal_playback_set_pause      = lds_hal_playback_set_pause,
    .lds_hal_playback_get_total_time = lds_hal_playback_get_total_time,
    .lds_hal_playback_get_curr_time  = lds_hal_playback_get_curr_time,
    .lds_hal_playback_get_play_state = lds_hal_playback_get_play_state,
    .lds_hal_playback_get_file_count = lds_hal_playback_get_file_count,
};

