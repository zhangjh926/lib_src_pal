#ifndef __LIBLDS_HAL_VIDEO_ENCODE_H
#define __LIBLDS_HAL_VIDEO_ENCODE_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_VIDEO_ENCODE_ErrorNo{
	LDS_VIDEO_ENCODE_OPEN_ERROR,
	LDS_VIDEO_ENCODE_INIT_ERROR,
	LDS_VIDEO_ENCODE_START_ERROR,
}LDS_VIDEO_ENCODE_ErrorNo;

//编码类型
 typedef enum
 {
    LDS_VIDEOENCODE_TYPE_H264,
    LDS_VIDEOENCODE_TYPE_H265,
    LDS_VIDEOENCODE_TYPE_MJPEG,
    LDS_VIDEOENCODE_TYPE_YUV422,
    LDS_VIDEOENCODE_TYPE_YUV420,
}LDS_VIDEOENCODE_TYPE;

 //比特率控制方式，0 VBR, 1 CBR, 2 CVBR …
typedef enum
{
     LDS_VIDEOENCODE_TYPE_VBR,
      LDS_VIDEOENCODE_TYPE_CBR,
     LDS_VIDEOENCODE_TYPE_CVBR,
}LDS_BITCTR_MODE;
  
//帧类型 I frame, P frame, B frame …
 typedef enum
 {
    LDS_FRAME_TYPE_IFRAME,
    LDS_FRAME_TYPE_PFRAME,
    LDS_FRAME_TYPE_BFRAME,
    LDS_FRAME_TYPE_CFRAME,
    LDS_FRAME_TYPE_DFRAME,
}LDS_FRAME_TYPE;

typedef enum {
    LDS_ENCODE_CHANNEL_MAIN_STREAM,
    LDS_ENCODE_CHANNEL_SUB_STREAM,
    LDS_ENCODE_CHANNEL_THREE_STREAM,
    LDS_ENCODE_CHANNEL_FOURTH_STREAM,
}LDS_ENCODE_CHANNEL;

typedef struct _VIDEO_OSD_OVERLAY{
    unsigned int    org_x;
    unsigned int    org_y;
    char            overlay_str[128];
}VIDEO_OSD_OVERLAY;

typedef struct _VIDEO_PARAM{
    unsigned int        width;            //video width
    unsigned int        height;           //video height
    LDS_FRAME_TYPE      frametype;        //Frame type,    I frame, P frame, B frame ... LDS_FRAME_TYPE
    LDS_VIDEOENCODE_TYPE encodetype;      //Encoding type,   0 H264, 1 H265, 2 MJPEG ... LDS_VIDEOENCODE_TYPE
    LDS_FRAME_TYPE      bitctlmode;       //Bit rate control method, 0 VBR, 1 CBR, 2 CVBR ... LDS_BITCTR_MODE
    unsigned char       framerate;        //Frame rate
    unsigned int        bitrate;          //Bit rate, bps
    unsigned int        rotation;         //rotation 90°,180°,270°
    unsigned int        gop;              //GOP
    unsigned int        iframe_freq;      //I Frame Frequency
    unsigned int        iframe_max_size;  //Maximum I Frame Size Limit
    LDS_ENCODE_CHANNEL  channel;          //stream channel
    VIDEO_OSD_OVERLAY   osd_info[4];      //osd overlay info
}VIDEO_PARAM;

typedef struct _VIDEO_CAPTURE_BUFFER{
    void *              buffer;
    unsigned int        size;
    LDS_ENCODE_CHANNEL  channel;
    unsigned int        frametype;
    unsigned int        timestamp;
}VIDEO_CAPTURE_BUFFER;

typedef int (*GET_VIDEO_FRAME)(VIDEO_CAPTURE_BUFFER *capture_buffer);

struct LDS_VIDEO_ENCODE_OPERATION
{
    struct  LDS_HAL_COMMON comm;
    const   char          *name;

    int     (*lds_hal_set_video_encode_config_param)(VIDEO_PARAM * config_param);
    
    int     (*lds_hal_set_video_encode_frame_callback)(GET_VIDEO_FRAME video_frame_callback);
};

/********************************************************************************
*                             EXTERN FUNCTIONS
*********************************************************************************/

extern struct LDS_VIDEO_ENCODE_OPERATION lds_hal_video_encoder;

#ifdef __cplusplus
}
#endif


#endif

