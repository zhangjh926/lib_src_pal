#ifndef __LDS_AE_H__
#define __LDS_AE_H__

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

#define LINUX 1

#if LINUX
#include <alsa/asoundlib.h>
#endif

typedef enum   _LDS_AE_ErrorNo{
	LDS_AUDIO_ENCODE_OPEN_ERROR = 100,
	LDS_AUDIO_ENCODE_CLOSE_ERROR,
	LDS_AUDIO_ENCODE_INIT_ERROR,
	LDS_AUDIO_ENCODE_START_ERROR,
	LDS_AUDIO_ENCODE_SET_HW_ERROR,
	LDS_AUDIO_ENCODE_SET_SW_ERROR,
	LDS_AUDIO_ENCODE_STOP_ERROR,
	LDS_AUDIO_ENCODE_READ_ERROR,
	LDS_AUDIO_ENCODE_GET_VOLUME_ERROR,
	LDS_AUDIO_ENCODE_SET_VOLUME_ERROR,
	LDS_AUDIO_ENCODE_MUTE_ERROR
}LDS_AUDIO_ENCODE_ErrorNo;

typedef struct _LDS_AE_PARAM
{	
	char	device[128];
	
	unsigned int pcm_format;
	unsigned int sampling_rate;
	unsigned int byte_per_sample;
	unsigned int channel_num;
	unsigned int sampling_frames;
	unsigned int read_interval;
	
	unsigned int buffer_time;
	unsigned int period_time;

	unsigned int sw_param_enable ;
	snd_pcm_access_t acccess; 
	
}LDS_AE_PARAM, *pLDS_AE_PARAM;

typedef struct _LDS_AE_CTX
{
	char				device[128];         //audio device name
	int				dev_fd; 			 //audio device fd
	char				vol_selem[128];      //volume reserved
	char				vol_mute_selem[128]; //mute volume reserved

	unsigned int        bEnable;
	
	unsigned int 		pcm_format;
	unsigned int 		sampling_rate;
	unsigned int		byte_per_sample;
	unsigned int		channel_num;
	unsigned int 		sampling_frames;
	unsigned int 		read_interval;
	
	unsigned int		buffer_time;
	unsigned int		period_time;

	unsigned int		sw_param_enable;
	#if LINUX
	snd_pcm_access_t 	acccess;	
	snd_pcm_t 			*phandle;
	snd_pcm_hw_params_t *hw_params;
	snd_pcm_sw_params_t *sw_params;
	#else
	int 				 acccess;	
	void 				*phandle;
	void 				*hw_params;
	void 				*sw_params;
	#endif

	LDS_AUDIO_ENCODE_ErrorNo curr_err_state;
}LDS_AE_CTX, *pLDS_AE_CTX;

struct LDS_AUDIO_MIC_OPERATION
{
    struct  LDS_HAL_COMMON base;
    const   char *name;
    int 	(*lds_audio_mic_per_frame_bytes)(snd_pcm_format_t format);
    int	(*lds_audio_mic_read)( pLDS_AE_CTX ctx, char* pbuf,  int size );
    int	(*lds_audio_mic_get_volume)( pLDS_AE_CTX ctx, int* volume );
    int	(*lds_audio_mic_set_volume)(pLDS_AE_CTX ctx, int volume );
    int 	(*lds_audio_mic_mute)(pLDS_AE_CTX ctx,  int mute );
    //void 	(*lds_audio_mic_mute_ex)(pLDS_AE_CTX ctx, int mute);
};

/********************************************************************************
*                             EXTERN FUNCTIONS
*********************************************************************************/

extern struct LDS_AUDIO_MIC_OPERATION lds_hal_audio_mic;

#ifdef __cplusplus
}
#endif


#endif 

