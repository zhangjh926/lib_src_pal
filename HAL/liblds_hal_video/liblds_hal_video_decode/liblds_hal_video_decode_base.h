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
    unsigned int  output;       //buffer = 0, cvbs = 1, lvds = 2, lcd = 3
}LDS_VIDEO_PARAM;

typedef struct _VIDEO_PLAYBACK_BUFFER{
    void *       playback_buffer;
    unsigned int playback_size;
    unsigned int playback_total_time; //ms
    unsigned int playback_curr_time;  //ms
}LDS_VIDEO_PLAYBACK_BUFFER;


typedef struct _LDS_VIDEO_DECODE_CONTEXT{
    char dev_name[128];
    int  dev_fd;
    LDS_VIDEO_DECODE_ErrorNo curr_state;
}LDS_VIDDEC_CONTEXT;


typedef int (*LDS_PLAYBACK_VIDEO_FRAME)(LDS_VIDEO_PLAYBACK_BUFFER *playback_buffer);

struct LDS_VIDEO_DECODE_OPERATION
{
    struct  LDS_HAL_COMMON  base;
    const   char            *name;
    
    int     (*lds_hal_playback_set_param)(LDS_VIDDEC_CONTEXT *ctx, LDS_VIDEO_PARAM * playback_param);
    int     (*lds_hal_playback_video_callback)(LDS_VIDDEC_CONTEXT *ctx, LDS_PLAYBACK_VIDEO_FRAME video_playback_callback);

    int     (*lds_hal_playback_set_seek)(LDS_VIDDEC_CONTEXT *ctx, int file_idx, int ms);
    int     (*lds_hal_playback_set_play)(LDS_VIDDEC_CONTEXT *ctx, int file_idx);
    int     (*lds_hal_playback_set_pause)(LDS_VIDDEC_CONTEXT *ctx, int file_idx);
    int     (*lds_hal_playback_set_stop)(LDS_VIDDEC_CONTEXT *ctx, int file_idx);
    int     (*lds_hal_playback_set_prev)(LDS_VIDDEC_CONTEXT *ctx,int file_idx);
    int     (*lds_hal_playback_set_next)(LDS_VIDDEC_CONTEXT *ctx,int file_idx);

    int     (*lds_hal_playback_get_total_time)(LDS_VIDDEC_CONTEXT *ctx, int file_idx);
    int     (*lds_hal_playback_get_curr_time)(LDS_VIDDEC_CONTEXT *ctx,  int file_idx);
    int     (*lds_hal_playback_get_play_state)(LDS_VIDDEC_CONTEXT *ctx, int file_idx);
    int     (*lds_hal_playback_get_file_count)(LDS_VIDDEC_CONTEXT *ctx);
};

/********************************************************************************
*                             EXTERN FUNCTIONS
*********************************************************************************/

extern struct LDS_VIDEO_DECODE_OPERATION lds_hal_video_decoder;

#ifdef __cplusplus

}
#endif


#endif
