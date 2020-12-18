#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_video_encode_base.h"

/* Define  -------------------------------------------------------------------*/

/* Define variable  ----------------------------------------------------------*/
static LDS_VIDEO_ENCODE_CONTEXT *ctx = NULL;
/* Define extern variable & function  ----------------------------------------*/



/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/

static int lds_hal_video_encoder_open(void *ctx_t, void *param)
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
static int lds_hal_video_encoder_close(void *ctx_t)
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
static int lds_hal_video_encoder_start(void *ctx_t)
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
static int lds_hal_video_encoder_stop(void *ctx_t)
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
static int lds_hal_video_encoder_init(void *param)
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
static int lds_hal_video_encoder_deinit(void *ctx_t)
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
static int lds_hal_video_encoder_get_error(void *ctx_t)
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
static int lds_hal_video_init_param(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL  channel, LDS_VIDEO_PARAM * config_param)
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
static int lds_hal_video_frame_callback(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL  channel, LDS_GET_VIDEO_FRAME video_frame_callback)
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
static int lds_hal_video_set_osd(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL channel, LDS_VIDEO_OSD_OVERLAY *overlay_info)
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
static int lds_hal_video_set_gop(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL channel, int gop)
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
static int lds_hal_video_set_framerate(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL channel, int framerate)
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
static int lds_hal_video_set_bitrate(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL channel, LDS_VIDEO_BRATE_CTL *bitctl)
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
static int lds_hal_video_set_rotation(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL channel, int rotation)
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
static int lds_hal_video_set_resolution(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL channel, int width, int height)
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
static int lds_hal_video_set_brightness(LDS_VIDENC_CXT *ctx, int brightness)
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
static int lds_hal_video_set_sharpness(LDS_VIDENC_CXT *ctx, int sharpness)
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
static int lds_hal_video_set_auto_exposure(LDS_VIDENC_CXT *ctx, int enable)
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
static int lds_hal_video_set_manual_exposure(LDS_VIDENC_CXT *ctx, int enable)
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
static int lds_hal_video_set_iso(LDS_VIDENC_CXT *ctx, int iso_value)
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
static int lds_hal_video_set_shutter(LDS_VIDENC_CXT *ctx, int shutter)
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
static int lds_hal_video_set_contrast(LDS_VIDENC_CXT *ctx, int contrast)
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
static int lds_hal_video_set_shutter_priority(LDS_VIDENC_CXT *ctx, int enable)
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
static int lds_hal_video_set_iso_priority(LDS_VIDENC_CXT *ctx , int enable)
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
static int lds_hal_video_get_isp_param(LDS_VIDENC_CXT *ctx, LDS_VIDEO_ISP_PARAM *isp_param)
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
static int lds_hal_video_set_bitctlmode(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL channel, AMBA_BITCTR_MODE bitctlmode)
{

}

struct LDS_VIDEO_ENCODE_OPERATION   lds_hal_video_encoder = {
    .name                                       = "lds_hal_video_encoder",
    .base.lds_hal_open                          = lds_hal_video_encoder_open,
    .base.lds_hal_close                         = lds_hal_video_encoder_close,
    .base.lds_hal_start                         = lds_hal_video_encoder_start,
    .base.lds_hal_stop                          = lds_hal_video_encoder_stop,
    .base.lds_hal_get_error                     = lds_hal_video_encoder_get_error,
    .lds_hal_video_frame_callback               = lds_hal_video_frame_callback,
    .lds_hal_video_init_param                   = lds_hal_video_init_param,
    .lds_hal_video_set_osd                      = lds_hal_video_set_osd,
    .lds_hal_video_set_gop                      = lds_hal_video_set_gop,
    // .lds_hal_video_set_bitctlmode               = lds_hal_video_set_bitctlmode,
    .lds_hal_video_set_framerate                = lds_hal_video_set_framerate,
    .lds_hal_video_set_bitrate                  = lds_hal_video_set_bitrate,
    .lds_hal_video_set_rotation                 = lds_hal_video_set_rotation,
    .lds_hal_video_set_resolution               = lds_hal_video_set_resolution,
    .lds_hal_video_set_brightness               = lds_hal_video_set_brightness,
    .lds_hal_video_set_sharpness                = lds_hal_video_set_sharpness,
    .lds_hal_video_set_auto_exposure            = lds_hal_video_set_auto_exposure,
    .lds_hal_video_set_manual_exposure          = lds_hal_video_set_manual_exposure,
    .lds_hal_video_set_iso                      = lds_hal_video_set_iso,
    .lds_hal_video_set_shutter                  = lds_hal_video_set_shutter,
    .lds_hal_video_set_contrast                 = lds_hal_video_set_contrast,
    .lds_hal_video_set_shutter_priority         = lds_hal_video_set_shutter_priority,
    .lds_hal_video_set_iso_priority             = lds_hal_video_set_iso_priority,
    .lds_hal_video_get_isp_param                = lds_hal_video_get_isp_param,
};
