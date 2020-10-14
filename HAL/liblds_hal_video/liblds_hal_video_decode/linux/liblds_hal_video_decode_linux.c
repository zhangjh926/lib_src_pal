#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_video_decode_base.h"

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
static int lds_hal_video_decoder_open(char *dev_name)
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
static int lds_hal_video_decoder_close(int dev_fd)
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
static int lds_hal_video_decoder_start(void)
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
static int lds_hal_video_decoder_stop(void)
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
static int lds_hal_video_decoder_init(void *param)
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
static int lds_hal_video_decoder_deinit(void)
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
static int lds_hal_video_playback_callback(set_playback_video_frame capture_buffer)
{
    return 0;
}


struct LDS_VIDEO_DECODE_OPERATION lds_hal_video_decoder = {
    .name                   = "lds_hal_video_decoder",
    .comm.lds_hal_open      = lds_hal_video_decoder_open,
    .comm.lds_hal_close     = lds_hal_video_decoder_close,
    .comm.lds_hal_start     = lds_hal_video_decoder_start,
    .comm.lds_hal_stop      = lds_hal_video_decoder_stop,
    .comm.lds_hal_init      = lds_hal_video_decoder_init,
    .comm.lds_hal_deinit    = lds_hal_video_decoder_deinit,
    .set_video_playback_callback = lds_hal_video_playback_callback,
};

