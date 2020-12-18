#ifndef __LDS_AD_H__
#define __LDS_AD_H__

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

#define LINUX 1

#ifdef LINUX
#include <alsa/asoundlib.h>
#endif

/********************************************************************************
*                              DEFINE
*********************************************************************************/


/********************************************************************************
*                              ENUMERATION
*********************************************************************************/
typedef enum   _LDS_AD_ErrorNo{
	LDS_AUDIO_DECODE_OPEN_ERROR = 200,
	LDS_AUDIO_DECODE_CLOSE_ERROR,
	LDS_AUDIO_DECODE_INIT_ERROR,
	LDS_AUDIO_DECODE_START_ERROR,
	LDS_AUDIO_DECODE_STOP_ERROR,
	LDS_AUDIO_DECODE_WRITE_ERROR,
	LDS_AUDIO_DECODE_SET_HW_ERROR,
	LDS_AUDIO_DECODE_SET_SW_ERROR,
	LDS_AUDIO_DECODE_GET_VOLUME_ERROR,
	LDS_AUDIO_DECODE_SET_VOLUME_ERROR,
	LDS_AUDIO_DECODE_MUTE_ERROR
}LDS_AUDIO_DECODE_ErrorNo;

typedef struct _LDS_AD_PARAM
{	
	char	device[128];
	
	unsigned int	pcm_format;
	unsigned int 	sampling_rate;
	unsigned int 	sampling_frames;
	unsigned int 	byte_per_sample;
	unsigned int 	channel_num;
	
	unsigned int 	buffer_time;
	unsigned int 	period_time;
	
}LDS_AD_PARAM, *pLDS_AD_PARAM;

/********************************************************************************
*                              STRUCTURE-external
*********************************************************************************/

typedef struct _LDS_AD_CTX
{
	char				device[128];
	int 				dev_fd;
	char				vol_selem[128]; 	 //reserved
	char				vol_mute_selem[128]; //reserved
	
	unsigned int        bEnable;

	unsigned int		pcm_format;
	unsigned int 		sampling_rate;
	unsigned int 		sampling_frames;
	unsigned int		byte_per_sample;
	unsigned int		buffer_time;
	unsigned int		period_time;
	unsigned int		channel_num;
	unsigned int		sw_param_enable;

	#if LINUX		
	snd_pcm_access_t 	acccess;
	snd_pcm_t 			*phandle;
	snd_pcm_hw_params_t *hw_params;
	snd_pcm_sw_params_t *sw_params;
	#else
	int 				acccess;
	void 				*phandle;
	void 				*hw_params;
	void 				*sw_params;
	#endif
	LDS_AUDIO_DECODE_ErrorNo curr_err_state;
} LDS_AD_CTX, *pLDS_AD_CTX;

/********************************************************************************
*                             EXTERN FUNCTIONS
*********************************************************************************/

struct LDS_AUDIO_SPEAKER_OPERATION{

    struct 	LDS_HAL_COMMON 	base;
    const 	char 		 	*name;
    int 	(*lds_audio_spk_per_frame_bytes)(snd_pcm_format_t format);
    int	(*lds_audio_spk_write)(pLDS_AD_CTX ctx, char* pbuf,  unsigned int size );
    int	(*lds_audio_spk_get_volume)(pLDS_AD_CTX ctx, int* volume );
    int	(*lds_audio_spk_set_volume)(pLDS_AD_CTX ctx, int volume );
    int 	(*lds_audio_spk_mute)(pLDS_AD_CTX ctx, int mute );
    
};

/********************************************************************************
*                             EXTERN FUNCTIONS
*********************************************************************************/

extern struct LDS_AUDIO_SPEAKER_OPERATION lds_hal_audio_spk;

#ifdef __cplusplus
}
#endif

#endif