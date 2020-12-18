#ifndef _LDS_VIDEO_COMMON_H
#define _LDS_VIDEO_COMMON_H

#ifdef __cplusplus
extern "C"{
#endif

#ifndef AM_IOCTL
#define AM_IOCTL(_filp, _cmd, _arg)	\
		do { 						\
			if (ioctl(_filp, _cmd, _arg) < 0) {	\
				perror(#_cmd);		\
				return -1;			\
			}						\
		} while (0)
#endif

#ifndef VERIFY_STREAMID
#define VERIFY_STREAMID(x)   do {		\
			if (((x) < 0) || ((x) >= MAX_ENCODE_STREAM_NUM)) {	\
				printf ("stream id wrong %d \n", (x));			\
				return -1; 	\
			}	\
		} while(0)
#endif

#ifndef VERIFY_AREAID
#define VERIFY_AREAID(x)	do {		\
			if (((x) < 0) || ((x) >= MAX_OVERLAY_AREA_NUM)) {	\
				printf("area id wrong %d, not in range [0~3].\n", (x));	\
				return -1;	\
			}	\
		} while (0)
#endif

#ifndef VERIFY_PTR
#define VERIFY_PTR(x)	do {		\
			if ((x) == NULL) {	\
				printf("Wrong msg format, please re-draw all!\n");	\
				return -1;	\
			}	\
		} while (0)
#endif

#ifndef VERIFY_BUFFERID
#define VERIFY_BUFFERID(x)	do {		\
			if ((x) >= IAV_MAX_CANVAS_BUF_NUM) {	\
				printf("Invalid canvas buffer id %d.\n", (x));	\
				return -1;	\
			}	\
		} while (0)
#endif

#define VERIFY_CHANNEL_ID(x)	do {		\
		if ((x) < 0 || ((x) >= CONFIG_AMBARELLA_MAX_CHANNEL_NUM)) {	\
			printf("Invalid channel id %d.\n", (x)); \
			return -1;	\
		}	\
	} while (0)

#define MAX_FILE_LEN 					(256)
#define MAX_ENCODE_STREAM_NUM			(13)
#define PRINT_CHARACTER_AMOUNT			1024

#define COLOR_PRINT0(msg)				printf("\033[34m"msg"\033[39m")
#define COLOR_PRINT(msg, arg...)		printf("\033[34m"msg"\033[39m", arg)
#define BOLD_PRINT0(msg, arg...)		printf("\033[1m"msg"\033[22m")
#define BOLD_PRINT(msg, arg...)			printf("\033[1m"msg"\033[22m", arg)
    
#define ASCII_COLOR_RED                 "\033[1;31m"
#define ASCII_COLOR_WHITE               "\033[1;37m"
#define ASCII_COLOR_YELLOW              "\033[1;33m"
#define ASCII_COLOR_BLUE                "\033[1;36m"
#define ASCII_COLOR_GREEN               "\033[1;32m"
#define ASCII_COLOR_END                 "\033[0m" 
#define AMBA_INFO(fmt, args...)     	({do{printf(ASCII_COLOR_GREEN"[VIDEO INFO ]:%s[%d]: ", __FUNCTION__,__LINE__);printf(fmt, ##args);printf(ASCII_COLOR_END);}while(0);})
#define AMBA_DEBUG(fmt, args...)        ({do{printf(ASCII_COLOR_YELLOW"[VIDEO DEBUG]:%s[%d]: ", __FUNCTION__,__LINE__);printf(fmt, ##args);printf(ASCII_COLOR_END);}while(0);})  
#define AMBA_ERROR(fmt, args...)      	({do{printf(ASCII_COLOR_RED  "[VIDEO ERROR]:%s[%d]: ", __FUNCTION__,__LINE__);printf(fmt, ##args);printf(ASCII_COLOR_END);}while(0);})


enum {
	/* osd blending mixer selection, used for blur or color privacy mask */
	OSD_BLENDING_OFF = 0,
	OSD_BLENDING_FROM_MIXER_A = 1,
	OSD_BLENDING_FROM_MIXER_B = 2,
};

typedef enum STREAM_BUFFER{
	STREAM_BUFFER_MAIN          = 0,    /*!< 0, main buffer */
	STREAM_BUFFER_2ND           = 1,    /*!< 1, 2nd buffer */
	STREAM_BUFFER_3RD           = 2,    /*!< 2, 3rd buffer */
	STREAM_BUFFER_4TH           = 3,    /*!< 3, 4th buffer */
	STREAM_BUFFER_5TH           = 4,    /*!< 4, 5th buffer */
	STREAM_BUFFER_6TH           = 5,    /*!< 5, 6th buffer */
}STREAM_BUFFER_ID;

typedef enum trans_method_s {
	TRANS_METHOD_NONE = 0,
	TRANS_METHOD_NFS,
	TRANS_METHOD_TCP,
	TRANS_METHOD_USB,
	TRANS_METHOD_STDOUT,
	TRANS_METHOD_UNDEFINED,
} trans_method_t;

typedef struct _VIDEO_OSD_OVERLAY{
    unsigned int    org_x;
    unsigned int    org_y;
    char            overlay_str[128];
}VIDEO_OSD_OVERLAY;

 //比特率控制方式，0 VBR, 1 CBR, 2 CVBR …
typedef enum
{
     VIDEOENCODE_TYPE_VBR,
     VIDEOENCODE_TYPE_CBR,
     VIDEOENCODE_TYPE_CVBR,
}VIDEO_BITCTR_MODE;

typedef struct _VIDEO_ISP_PARAM{
    int brightness;         //亮度
    int sharpness;          //锐度
    int auto_exposure;      //自动曝光
    int manual_exposure;    //手动曝光
    int iso;                //感光度
    int shutter;            //快门
    int contrast;           //对比度
    int shutter_prority;    //快门优先
    int iso_prority;        //感光度优先
}VIDEO_ISP_PARAM;

typedef enum {
    ENCODE_CHANNEL_MAIN_STREAM,
    ENCODE_CHANNEL_SUB_STREAM,
    ENCODE_CHANNEL_THREE_STREAM,
    ENCODE_CHANNEL_FOURTH_STREAM,
}VIDEO_ENCODE_CHANNEL;

 typedef enum{
    FRAME_MJPEG_FRAME        = 0, /*!< 0 */
 	FRAME_IDR_FRAME          = 1, /*!< 1 */
  	FRAME_I_FRAME            = 2, /*!< 2 */
 	FRAME_P_FRAME            = 3, /*!< 3 */
	FRAME_B_FRAME            = 4, /*!< 4 */
 	FRAME_P_FAST_SEEK_FRAME  = 5, /*!< 5 */
 /* Value 6 is reseved for furture extension */
 	FRAME_END_FRAME          = 7, /*!< 7 */
}VIDEO_FRAME_TYPE;

//编码类型
 typedef enum
 {
    VIDEOENCODE_TYPE_H264,
    VIDEOENCODE_TYPE_H265,
    VIDEOENCODE_TYPE_RGB565,
    VIDEOENCODE_TYPE_RGB555,
    VIDEOENCODE_TYPE_MJPEG,
    VIDEOENCODE_TYPE_YUV422,
    VIDEOENCODE_TYPE_YUV420,
}VIDEO_ENCODE_TYPE;

 typedef enum
 {
    FRAME_BASELINE_PROFILE, //提供I/P帧，仅支持progressive(逐行扫描)和CAVLC.
    FRAME_MAIN_PROFILE,     //提供I/P/B帧，支持progressive(逐行扫描)和interlaced(隔行扫描)，提供CAVLC或CABAC.
    FRAME_EXTENDED_CFRAME,  //提供I/P/B/SP/SI帧，仅支持progressive(逐行扫描)和CAVLC.
    FRAME_HIGH_PROFILE,     //在Main Profile基础上新增：8x8 intra prediction(8x8 帧内预测), custom quant(自定义量化), lossless video coding(无损视频编码), 更多的yuv格式（4:4:4...）；
}VIDEO_FRAME_PROFILE;

typedef struct _VIDEO_BITRATE_CTL{
    VIDEO_BITCTR_MODE   bitctl;
    int                 min_bitrate;   //cbr min=max
    int                 max_bitrate;   //cbr min=max
}VIDEO_BRATE_CTL;

typedef struct _VIDEO_PARAM{
    unsigned int        width;            //video width
    unsigned int        height;           //video height
    VIDEO_FRAME_PROFILE frametype;        //Frame type,    I frame, P frame, B frame ... AMBA_FRAME_TYPE
    VIDEO_ENCODE_TYPE   encodetype;       //Encoding type,   0 H264, 1 H265, 2 MJPEG ... AMBA_VIDENCODE_TYPE
    VIDEO_BITCTR_MODE   bitctlmode;       //Bit rate control method, 0 VBR, 1 CBR, 2 CVBR ... AMBA_BITCTR_MODE
    unsigned char       framerate;        //Frame rate
    VIDEO_BRATE_CTL     bitrate;          //Bit rate, bps
    unsigned int        rotation;         //rotation 90°,180°,270°
    unsigned int        gop;              //GOP
    unsigned int        iframe_freq;      //I Frame Frequency
    unsigned int        iframe_max_size;  //Maximum I Frame Size Limit
    VIDEO_ENCODE_CHANNEL channel;          //stream channel
    VIDEO_OSD_OVERLAY   osd_info[4];      //osd overlay info
}VIDEO_PARAM;


typedef struct _AMBA_VIDEO_CAPTURE_BUFFER{
    void *              buffer;
    unsigned int        size;
    VIDEO_ENCODE_CHANNEL channel;
    unsigned int        frametype;
    unsigned long       timestamp;
    unsigned int        width;
    unsigned int        height;
    VIDEO_ENCODE_TYPE   encodetype;
    VIDEO_BRATE_CTL     bitrate;
    unsigned int 		framerate;
    unsigned int        gop;
}VIDEO_CAPTURE_BUFFER;

typedef enum   _VIDEO_ENCODE_ErrorNo{
	VIDEO_ENCODE_OPEN_ERROR,
	VIDEO_ENCODE_INIT_ERROR,
	VIDEO_ENCODE_START_ERROR,
}VIDEO_ENCODE_ErrorNo;

typedef struct _VIDEO_ENCODE_CONTEXT{
	void *this_ctx;
    char dev_name[64];
    int  dev_fd;
    VIDEO_ENCODE_ErrorNo curr_err_state;
}VIDENC_CXT;

typedef int (*GET_VIDEO_FRAME)(VIDENC_CXT *ctx, VIDEO_CAPTURE_BUFFER *capture_buffer);


#ifdef __cplusplus
}
#endif

#endif
