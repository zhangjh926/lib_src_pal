#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "liblds_hal_video_encode_base.h"
#include "lds_video_interface.h"

/* Define  -------------------------------------------------------------------*/

/* Define variable  ----------------------------------------------------------*/
// static struct LDS_VIDEO_ENCODE_CONTEXT ctx;
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
    return hal_video_sample.hal_open((VIDENC_CXT*)ctx_t, param);
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
    return hal_video_sample.hal_close((VIDENC_CXT*)ctx_t);
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
    return hal_video_sample.hal_start((VIDENC_CXT*)ctx_t);
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
    return hal_video_sample.hal_stop((VIDENC_CXT*)ctx_t);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
// static int lds_hal_video_encoder_init(void *param)
// {
//     return amba_hal_video_sample.amba_hal_init(param);
// }

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
// static int lds_hal_video_encoder_deinit(void *ctx_t)
// {
//     return amba_hal_video_sample.amba_hal_deinit((AMBA_VIDENC_CXT*)ctx_t);
// }

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_video_encoder_get_error(void *ctx_t)
{
    return hal_video_sample.hal_get_error((VIDENC_CXT*)ctx_t);
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
    return hal_video_sample.hal_video_init_param((VIDENC_CXT*)ctx, channel, (VIDEO_PARAM*)config_param);
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
    return hal_video_sample.hal_video_frame_callback((VIDENC_CXT*)ctx, channel, (GET_VIDEO_FRAME)video_frame_callback);
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
    return hal_video_sample.hal_video_set_osd((VIDENC_CXT*)ctx, channel, (VIDEO_OSD_OVERLAY*)overlay_info);
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
    return hal_video_sample.hal_video_set_gop((VIDENC_CXT*)ctx, channel, gop);
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
    return hal_video_sample.hal_video_set_framerate((VIDENC_CXT*)ctx, channel, framerate);
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
    return hal_video_sample.hal_video_set_bitrate((VIDENC_CXT*)ctx, channel, (VIDEO_BRATE_CTL*)bitctl);
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
    return hal_video_sample.hal_video_set_rotation((VIDENC_CXT*)ctx, channel, rotation);
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
    return hal_video_sample.hal_video_set_resolution((VIDENC_CXT*)ctx, channel, width, height);
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
    return hal_video_sample.hal_video_set_brightness((VIDENC_CXT*)ctx, brightness);
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
    return hal_video_sample.hal_video_set_sharpness((VIDENC_CXT*)ctx, sharpness);
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
    return hal_video_sample.hal_video_set_auto_exposure((VIDENC_CXT*)ctx, enable);
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
    return hal_video_sample.hal_video_set_manual_exposure((VIDENC_CXT*)ctx, enable);
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
    return hal_video_sample.hal_video_set_iso((VIDENC_CXT*)ctx, iso_value);
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
    return hal_video_sample.hal_video_set_shutter((VIDENC_CXT*)ctx, shutter);
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
    return hal_video_sample.hal_video_set_contrast((VIDENC_CXT*)ctx, contrast);
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
    return hal_video_sample.hal_video_set_shutter_priority((VIDENC_CXT*)ctx, enable);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int lds_hal_video_set_iso_priority(LDS_VIDENC_CXT *ctx, int enable)
{
    return hal_video_sample.hal_video_set_iso_priority((VIDENC_CXT*)ctx, enable);
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
    return hal_video_sample.hal_video_get_isp_param((VIDENC_CXT*)ctx, (VIDEO_ISP_PARAM*)isp_param);
}

// static int lds_hal_video_set_bitctlmode(LDS_ENCODE_CHANNEL channel, LDS_BITCTR_MODE bitctlmode)
// {
//     return amba_hal_video_sample.amba_hal_video_set_bitctlmode(channel, bitctlmode);
// }

struct LDS_VIDEO_ENCODE_OPERATION   lds_hal_video_encoder = {
    .name                                       = "lds_hal_video_encoder",
    .base.lds_hal_open                          = lds_hal_video_encoder_open,
    .base.lds_hal_close                         = lds_hal_video_encoder_close,
    .base.lds_hal_start                         = lds_hal_video_encoder_start,
    .base.lds_hal_stop                          = lds_hal_video_encoder_stop,
    // .base.lds_hal_init                          = lds_hal_video_encoder_init,
    // .base.lds_hal_deinit                        = lds_hal_video_encoder_deinit,
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
