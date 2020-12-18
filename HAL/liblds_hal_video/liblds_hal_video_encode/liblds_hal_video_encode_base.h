#ifndef __LIBLDS_HAL_VIDEO_ENCODE_H
#define __LIBLDS_HAL_VIDEO_ENCODE_H

#include "lds_common_media.h"
#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_VIDEO_ENCODE_ErrorNo{
	LDS_VIDEO_ENCODE_OPEN_ERROR,
	LDS_VIDEO_ENCODE_INIT_ERROR,
	LDS_VIDEO_ENCODE_START_ERROR,
}LDS_VIDEO_ENCODE_ErrorNo;

typedef struct _LDS_VIDEO_OSD_OVERLAY{
    unsigned int    org_x;
    unsigned int    org_y;
    char            overlay_str[128];
}LDS_VIDEO_OSD_OVERLAY;

typedef struct _LDS_VIDEO_BRATE_CTL{
    LDS_BITCTR_MODE     bitctl;
    int                 min_bitrate;   //cbr min=max
    int                 max_bitrate;   //cbr min=max
}LDS_VIDEO_BRATE_CTL;

typedef struct _LDS_VIDEO_PARAM{
    unsigned int        width;            //video width
    unsigned int        height;           //video height
    LDS_FRAME_PROFILE   frametype;        //Frame type,    I frame, P frame, B frame ... LDS_FRAME_TYPE
    LDS_VIDEOENCODE_TYPE  encodetype;       //Encoding type,   0 H264, 1 H265, 2 MJPEG ... LDS_VIDENCODE_TYPE
    LDS_BITCTR_MODE     bitctlmode;       //Bit rate control method, 0 VBR, 1 CBR, 2 CVBR ... LDS_BITCTR_MODE
    unsigned int        framerate;        //Frame rate
    LDS_VIDEO_BRATE_CTL bitrate;          //Bit rate, bps
    unsigned int        rotation;         //rotation 90°,180°,270°
    unsigned int        gop;              //GOP
    unsigned int        iframe_freq;      //I Frame Frequency
    unsigned int        iframe_max_size;  //Maximum I Frame Size Limit
    LDS_VIDEO_OSD_OVERLAY   osd_info[4];  //osd overlay info
}LDS_VIDEO_PARAM;

typedef struct _LDS_VIDEO_CAPTURE_BUFFER{
    void *              buffer;
    unsigned int        size;
    LDS_ENCODE_CHANNEL  channel;
    LDS_FRAME_TYPE      frametype;
    unsigned long       timestamp;
    unsigned int        width;
    unsigned int        height;
    LDS_VIDEOENCODE_TYPE  encodetype;
    unsigned int        framerate;
    LDS_VIDEO_BRATE_CTL bitrate;
    unsigned int        gop;
}LDS_VIDEO_CAPTURE_BUFFER;

typedef struct _LDS_VIDEO_ISP_PARAM{
    int brightness;         //亮度
    int sharpness;          //锐度
    int auto_exposure;      //自动曝光
    int manual_exposure;    //手动曝光
    int iso;                //感光度
    int shutter;            //快门
    int contrast;           //对比度
    int shutter_prority;    //快门优先
    int iso_prority;        //感光度优先
}LDS_VIDEO_ISP_PARAM;

typedef struct _LDS_VIDEO_ENCODE_CONTEXT{
    void *this_ctx;
    char dev_name[64];
    int  dev_fd;
    LDS_VIDEO_ENCODE_ErrorNo curr_err_state;
}LDS_VIDENC_CXT;

typedef int (*LDS_GET_VIDEO_FRAME)(LDS_VIDENC_CXT *ctx, LDS_VIDEO_CAPTURE_BUFFER *capture_buffer);

struct LDS_VIDEO_ENCODE_OPERATION
{
    struct  LDS_HAL_COMMON base;
    const   char          *name;

    /**
    * video capture callback function
    */
    int     (*lds_hal_video_init_param)(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL  channel, LDS_VIDEO_PARAM * config_param);
    int     (*lds_hal_video_frame_callback)(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL  channel, LDS_GET_VIDEO_FRAME video_frame_callback);

    /**
    * video param adjust
    */
    int     (*lds_hal_video_set_osd)(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL channel, LDS_VIDEO_OSD_OVERLAY *overlay_info);
    int     (*lds_hal_video_set_gop)(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL channel, int gop);
    int     (*lds_hal_video_set_framerate)(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL channel, int framerate);
    int     (*lds_hal_video_set_bitrate)(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL channel, LDS_VIDEO_BRATE_CTL *bitctl);
    int     (*lds_hal_video_set_rotation)(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL channel, int rotation);
    int     (*lds_hal_video_set_resolution)(LDS_VIDENC_CXT *ctx, LDS_ENCODE_CHANNEL channel, int width, int height);
    // int     (*lds_hal_video_set_bitctlmode)(LDS_ENCODE_CHANNEL channel, LDS_BITCTR_MODE bitctlmode);

    /** 
    * isp param adjust
    */
    int     (*lds_hal_video_set_brightness)(LDS_VIDENC_CXT *ctx, int brightness);
    int     (*lds_hal_video_set_sharpness)(LDS_VIDENC_CXT *ctx, int sharpness);
    int     (*lds_hal_video_set_auto_exposure)(LDS_VIDENC_CXT *ctx, int enable);
    int     (*lds_hal_video_set_manual_exposure)(LDS_VIDENC_CXT *ctx,int enable);
    int     (*lds_hal_video_set_iso)(LDS_VIDENC_CXT *ctx, int iso_value);
    int     (*lds_hal_video_set_shutter)(LDS_VIDENC_CXT *ctx,int shutter);
    int     (*lds_hal_video_set_contrast)(LDS_VIDENC_CXT *ctx, int contrast);
    int     (*lds_hal_video_set_shutter_priority)(LDS_VIDENC_CXT *ctx, int enable);
    int     (*lds_hal_video_set_iso_priority)(LDS_VIDENC_CXT *ctx, int enable);

    int     (*lds_hal_video_get_isp_param)(LDS_VIDENC_CXT *ctx, LDS_VIDEO_ISP_PARAM *isp_param);
};

/********************************************************************************
*                             EXTERN FUNCTIONS
*********************************************************************************/

extern struct LDS_VIDEO_ENCODE_OPERATION lds_hal_video_encoder;

#ifdef __cplusplus
}
#endif


#endif

