#ifndef __LIBLDS_HAL_VIDEO_DECODE_H
#define __LIBLDS_HAL_VIDEO_DECODE_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_VIDEO_DECODE_ErrorNo{
	LDS_VIDEO_DECODE_OPEN_ERROR,
	LDS_VIDEO_DECODE_INIT_ERROR,
	LDS_VIDEO_DECODE_ERROR,
}LDS_VIDEO_DECODE_ErrorNo;

typedef enum
{
    LDS_VIDEOENCODE_TYPE_H264,
    LDS_VIDEOENCODE_TYPE_H265,
    LDS_VIDEOENCODE_TYPE_MJPEG,
}LDS_VIDEOENCODE_TYPE;

typedef enum
{
    LDS_VIDEOENCODE_TYPE_VBR,
    LDS_VIDEOENCODE_TYPE_CBR,
    LDS_VIDEOENCODE_TYPE_CVBR,
}LDS_BITCTR_MODE;
 
 typedef enum
 {
    LDS_FRAME_TYPE_IFRAME,
    LDS_FRAME_TYPE_PFRAME,
    LDS_FRAME_TYPE_BFRAME,
    LDS_FRAME_TYPE_CFRAME,
    LDS_FRAME_TYPE_DFRAME,
 }LDS_FRAME_TYPE;


typedef struct _VIDEO_PARAM{
    unsigned int  width;        //video width
    unsigned int  height;       //video height
    unsigned char frametype;    //Frame type,    I frame, P frame, B frame 
    unsigned char encodetype;   //Encoding type,   0 H264, 1 H265, 2 MJPEG 
    unsigned char bitctlmode;   //Bit rate control method, 0 VBR, 1 CBR, 2 CVBR
    unsigned char framerate;    //Frame rate
    unsigned int  bitrate;      //Bit rate, bps
    unsigned int  gop;          //GOP
    unsigned int  iframe_freq;  //I Frame Frequency
}VIDEO_PARAM;

typedef struct _VIDEO_PLAYBACK_BUFFER{
    void *       playback_buffer;
    unsigned int playback_size;
}VIDEO_PLAYBACK_BUFFER;

typedef int (*SET_PLAYBACK_VIDEO_FRAME)(VIDEO_PLAYBACK_BUFFER *playback_buffer);

struct LDS_VIDEO_DECODE_OPERATION
{
    struct  LDS_HAL_COMMON  comm;
    const   char            *name;
    
    int     (*set_playback_param)(VIDEO_PARAM * playback_param);
    int     (*set_video_playback_callback)(SET_PLAYBACK_VIDEO_FRAME video_playback_callback);
};

/********************************************************************************
*                             EXTERN FUNCTIONS
*********************************************************************************/

extern struct LDS_VIDEO_DECODE_OPERATION lds_hal_video_decoder;

#ifdef __cplusplus

}
#endif


#endif
