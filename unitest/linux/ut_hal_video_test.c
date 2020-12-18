#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "liblds_hal_video_encode_base.h"

static int gFlag = 1;
static int fd = -1;

static LDS_VIDENC_CXT video_ctx1 = {
    .dev_name = "/dev/iav",
    .dev_fd   = 0,
    .curr_err_state = 0,
};

static LDS_VIDEO_PARAM main_stream_param = {
    .frametype = LDS_FRAME_MAIN_PROFILE,      
    .encodetype = LDS_VIDEOENCODE_TYPE_H264,
    .bitctlmode = LDS_VIDEOENCODE_TYPE_CBR,
    .framerate  = 25,
	.gop		= 30,
    .bitrate    = {
        .bitctl = LDS_VIDEOENCODE_TYPE_CBR,
        .min_bitrate = 2000000,
        .max_bitrate = 2000000,
    },
};

static LDS_VIDEO_PARAM secnod_stream_param = {
    .frametype = LDS_FRAME_MAIN_PROFILE,      
    .encodetype = LDS_VIDEOENCODE_TYPE_H264,
    .bitctlmode = LDS_VIDEOENCODE_TYPE_CBR,
    .framerate  = 25,
	.gop 		= 30,
    .bitrate    = {
        .bitctl = LDS_VIDEOENCODE_TYPE_CBR,
        .min_bitrate = 1000000,
        .max_bitrate = 2000000,
    }
};
// static LDS_VIDENC_CXT video_ctx2 = {
//     .dev_name = "/dev/iav2",
//     .dev_fd   = 0,
//     .curr_err_state = 0,
// };

#define TEST_WRITE_FILE  0

#if TEST_WRITE_FILE
static FILE *fp = NULL;
#endif

static void sigstop(int signum)
{
    gFlag = 0;
    printf("+++++++++++++signal num=%d++++++++++++++\n", signum);

#if TEST_WRITE_FILE
    fflush(fp);
    fclose(fp);
#endif

}

static int mian_stream_handler(LDS_VIDENC_CXT *ctx, LDS_VIDEO_CAPTURE_BUFFER *capture_buffer)
{
	// printf("====>>main_stream addr=0x%p, size=%d, channel=%d, frametype=%d\n",
 //    capture_buffer->buffer, capture_buffer->size, capture_buffer->channel, capture_buffer->frametype);
 	 #if TEST_WRITE_FILE
	 int ret = fwrite(capture_buffer->buffer, 1, capture_buffer->size, fp);
     if(ret != capture_buffer->size){
         printf("main stream fwrite len error = %d, origin=%d\n", ret, capture_buffer->size);
     }
	#endif
	return 0;
}

static int second_stream_handler(LDS_VIDENC_CXT *ctx, LDS_VIDEO_CAPTURE_BUFFER *capture_buffer)
{
	// printf("====>>second_stream addr=0x%p, size=%d, channel=%d, frametype=%d\n",
	// 		capture_buffer->buffer, capture_buffer->size, capture_buffer->channel, capture_buffer->frametype);
	return 0;
}

int main(int argc, char *argv[])
{
    signal(SIGINT, sigstop);
    signal(SIGQUIT, sigstop);
    signal(SIGTERM, sigstop);

    fd = lds_hal_video_encoder.base.lds_hal_open(&video_ctx1, NULL);
    if(fd <= 0){
        perror("open /dev/iav fail\n");
        return -1;
    }

	#if TEST_WRITE_FILE
    fp = fopen("test.h264","ab+");
    if(NULL == fp) {
        perror("open test.h264 fail...\n");
        return -1;
    }
	#endif
    // lds_hal_video_encoder.base.lds_hal_init(NULL); //lds_video_init(NULL);

    lds_hal_video_encoder.lds_hal_video_init_param(&video_ctx1, LDS_ENCODE_CHANNEL_MAIN_STREAM, &main_stream_param);
    lds_hal_video_encoder.lds_hal_video_init_param(&video_ctx1, LDS_ENCODE_CHANNEL_SUB_STREAM, &secnod_stream_param);

    lds_hal_video_encoder.lds_hal_video_frame_callback(&video_ctx1, LDS_ENCODE_CHANNEL_MAIN_STREAM, mian_stream_handler);
    lds_hal_video_encoder.lds_hal_video_frame_callback(&video_ctx1, LDS_ENCODE_CHANNEL_SUB_STREAM, second_stream_handler);

    lds_hal_video_encoder.base.lds_hal_start(&video_ctx1);  //lds_video_start(fd);

    while(gFlag){
        usleep(500000);
    }

    lds_hal_video_encoder.base.lds_hal_stop(&video_ctx1);  //lds_video_stop(fd);
    // lds_hal_video_encoder.base.lds_hal_deinit(&video_ctx1);
    lds_hal_video_encoder.base.lds_hal_close(&video_ctx1);

    return 0;
}
