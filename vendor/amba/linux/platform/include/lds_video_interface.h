
#ifndef __AMBA_VIDEO_INTERFACE_H
#define __AMBA_VIDEO_INTERFACE_H

#ifdef __cplusplus
extern "C"{
#endif
#include "lds_video_common.h"

//  //比特率控制方式，0 VBR, 1 CBR, 2 CVBR …
// typedef enum
// {
//      AMBA_VIDEOENCODE_TYPE_VBR,
//      AMBA_VIDEOENCODE_TYPE_CBR,
//      AMBA_VIDEOENCODE_TYPE_CVBR,
// }AMBA_BITCTR_MODE;
  
//帧类型 I frame, P frame, B frame …
//  typedef enum
//  {
//     AMBA_FRAME_BASELINE_PROFILE, //提供I/P帧，仅支持progressive(逐行扫描)和CAVLC.
//     AMBA_FRAME_MAIN_PROFILE,     //提供I/P/B帧，支持progressive(逐行扫描)和interlaced(隔行扫描)，提供CAVLC或CABAC.
//     AMBA_FRAME_EXTENDED_CFRAME,  //提供I/P/B/SP/SI帧，仅支持progressive(逐行扫描)和CAVLC.
//     AMBA_FRAME_HIGH_PROFILE,     //在Main Profile基础上新增：8x8 intra prediction(8x8 帧内预测), custom quant(自定义量化), lossless video coding(无损视频编码), 更多的yuv格式（4:4:4...）；
// }AMBA_FRAME_PROFILE;

// typedef enum {
//     AMBA_ENCODE_CHANNEL_MAIN_STREAM,
//     AMBA_ENCODE_CHANNEL_SUB_STREAM,
//     AMBA_ENCODE_CHANNEL_THREE_STREAM,
//     AMBA_ENCODE_CHANNEL_FOURTH_STREAM,
// }AMBA_ENCODE_CHANNEL;

// typedef struct _VIDEO_OSD_OVERLAY{
//     unsigned int    org_x;
//     unsigned int    org_y;
//     char            overlay_str[128];
// }VIDEO_OSD_OVERLAY;

// typedef struct _AMBA_VIDEO_PARAM{
//     unsigned int        width;            //video width
//     unsigned int        height;           //video height
//     AMBA_FRAME_PROFILE  frametype;        //Frame type,    I frame, P frame, B frame ... AMBA_FRAME_TYPE
//     AMBA_VIDENCODE_TYPE encodetype;       //Encoding type,   0 H264, 1 H265, 2 MJPEG ... AMBA_VIDENCODE_TYPE
//     AMBA_BITCTR_MODE    bitctlmode;       //Bit rate control method, 0 VBR, 1 CBR, 2 CVBR ... AMBA_BITCTR_MODE
//     unsigned char       framerate;        //Frame rate
//     AMBA_VIDEO_BRATE_CTL bitrate;          //Bit rate, bps
//     unsigned int        rotation;         //rotation 90°,180°,270°
//     unsigned int        gop;              //GOP
//     unsigned int        iframe_freq;      //I Frame Frequency
//     unsigned int        iframe_max_size;  //Maximum I Frame Size Limit
//     AMBA_ENCODE_CHANNEL channel;          //stream channel
//     AMBA_VIDEO_OSD_OVERLAY osd_info[4];   //osd overlay info
// }AMBA_VIDEO_PARAM;

// typedef struct _AMBA_VIDEO_CAPTURE_BUFFER{
//     void *              buffer;
//     unsigned int        size;
//     AMBA_ENCODE_CHANNEL  channel;
//     unsigned int        frametype;
//     unsigned int        timestamp;
// }AMBA_VIDEO_CAPTURE_BUFFER;


// typedef struct _AMBA_VIDEO_ISP_PARAM{
//     int brightness;         //亮度
//     int sharpness;          //锐度
//     int auto_exposure;      //自动曝光
//     int manual_exposure;    //手动曝光
//     int iso;                //感光度
//     int shutter;            //快门
//     int contrast;           //对比度
//     int shutter_prority;    //快门优先
//     int iso_prority;        //感光度优先
// }AMBA_VIDEO_ISP_PARAM;


// typedef int (*AMBA_GET_VIDEO_FRAME)(AMBA_VIDEO_CAPTURE_BUFFER *capture_buffer);

struct VIDEO_SAMPLE
{
    const   char          		  *name;
    int     (*hal_open)      (VIDENC_CXT *ctx, void *param); 
	int     (*hal_close)     (VIDENC_CXT *ctx);
    // int     (*amba_hal_init)      (void *param);
    // int     (*amba_hal_deinit)    (AMBA_VIDENC_CXT *ctx);
    int 	(*hal_start)     (VIDENC_CXT *ctx); //resume
    int 	(*hal_stop) 	 (VIDENC_CXT *ctx); //pause
    int     (*hal_get_error) (VIDENC_CXT *ctx);
    /**
    * video capture callback function
    */
    int     (*hal_video_init_param)(VIDENC_CXT *ctx, STREAM_BUFFER_ID stream_id, VIDEO_PARAM * config_param);
    int     (*hal_video_frame_callback)(VIDENC_CXT *ctx, STREAM_BUFFER_ID stream_id, GET_VIDEO_FRAME video_frame_callback);

    /**
    * video param adjust
    */
    int     (*hal_video_set_osd)(VIDENC_CXT *ctx, STREAM_BUFFER_ID stream_id, VIDEO_OSD_OVERLAY *overlay_info);
    int     (*hal_video_set_gop)(VIDENC_CXT *ctx, STREAM_BUFFER_ID stream_id, int gop);
    int     (*hal_video_set_framerate)(VIDENC_CXT *ctx, STREAM_BUFFER_ID stream_id, int framerate);
    int     (*hal_video_set_bitrate)(VIDENC_CXT *ctx, STREAM_BUFFER_ID stream_id, VIDEO_BRATE_CTL *bitmode);
    int     (*hal_video_set_rotation)(VIDENC_CXT *ctx, STREAM_BUFFER_ID stream_id, int rotation);
    // int     (*amba_hal_video_set_bitctlmode)(STREAM_BUFFER_ID stream_id, AMBA_BITCTR_MODE bitctlmode);
    int     (*hal_video_set_resolution)(VIDENC_CXT *ctx, STREAM_BUFFER_ID stream_id, int width, int height);

    /** 
    * isp param adjust
    */
    int     (*hal_video_set_brightness)(VIDENC_CXT *ctx, int brightness);
    int     (*hal_video_set_sharpness)(VIDENC_CXT *ctx, int sharpness);
    int     (*hal_video_set_auto_exposure)(VIDENC_CXT *ctx, int enable);
    int     (*hal_video_set_manual_exposure)(VIDENC_CXT *ctx, int enable);
    int     (*hal_video_set_iso)(VIDENC_CXT *ctx, int iso_value);
    int     (*hal_video_set_shutter)(VIDENC_CXT *ctx, int shutter);
    int     (*hal_video_set_contrast)(VIDENC_CXT *ctx, int contrast);
    int     (*hal_video_set_shutter_priority)(VIDENC_CXT *ctx, int enable);
    int     (*hal_video_set_iso_priority)(VIDENC_CXT *ctx, int enable);


  	int 	(*hal_video_get_isp_param)(VIDENC_CXT *ctx, VIDEO_ISP_PARAM *isp_param);
};

/********************************************************************************
*                             EXTERN FUNCTIONS
*********************************************************************************/

extern struct VIDEO_SAMPLE hal_video_sample;


#ifdef __cplusplus
}
#endif

#endif
