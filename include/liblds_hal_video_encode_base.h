#ifndef __LIBLDS_HAL_VIDEO_ENCODE_H
#define __LIBLDS_HAL_VIDEO_ENCODE_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct _video_param{
    unsigned int  width;        //video width
    unsigned int  height;       //video height
    unsigned char frametype;    //Frame type,    I frame, P frame, B frame ... LDS_FRAME_TYPE
    unsigned char encodetype;   //Encoding type,   0 H264, 1 H265, 2 MJPEG ... LDS_VIDEOENCODE_TYPE
    unsigned char bitctlmode;   //Bit rate control method, 0 VBR, 1 CBR, 2 CVBR ... LDS_BITCTR_MODE
    unsigned char framerate;    //Frame rate
    unsigned int  bitrate;      //Bit rate, bps
}video_param;

typedef struct _video_capture_buffer{
    void *       buffer;
    unsigned int size;
    unsigned int channel;
    unsigned int frametype;
    unsigned int timestamp;
}video_capture_buffer;


typedef int (*get_video_frame)(video_capture_buffer *capture_buffer);

struct LDS_VIDEO_ENCODE_OPERATION
{
    struct LDS_HAL_COMMON comm;
    const char *name;

    int (*set_capture_config_param)(video_param * config_param);
    int (*set_video_frame_callback)(get_video_frame video_frame_callback);
};

/********************************************************************************
*                             EXTERN FUNCTIONS
*********************************************************************************/

extern struct LDS_VIDEO_ENCODE_OPERATION lds_hal_video_encoder;

#ifdef __cplusplus
}
#endif


#endif

