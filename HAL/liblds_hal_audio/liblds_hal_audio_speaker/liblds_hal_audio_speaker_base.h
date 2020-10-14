#ifndef __LDS_AD_H__
#define __LDS_AD_H__

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

#define LINUX 1

#ifdef LINUX
#include <stdint.h>
#include <alsa/asoundlib.h>
#endif

/********************************************************************************
*                              DEFINE
*********************************************************************************/


/********************************************************************************
*                              ENUMERATION
*********************************************************************************/
typedef enum   _LDS_AD_ErrorNo{
	LDS_AUDIO_DECODE_OPEN_ERROR,
	LDS_AUDIO_DECODE_INIT_ERROR,
	LDS_AUDIO_DECODE_START_ERROR,
	LDS_AUDIO_DECODE_SET_HW_ERROR,
	LDS_AUDIO_DECODE_SET_SW_ERROR,
}LDS_AUDIO_DECODE_ErrorNo;

/********************************************************************************
*                              STRUCTURE-external
*********************************************************************************/

typedef struct _LDS_AD_STR
{
	const char*			device;
	const char*			vol_selem;
	const char*			vol_mute_selem;
	
	unsigned int		pcm_format;
	unsigned int 		sampling_rate;
	unsigned int		bit_per_sample;
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
} LDS_AD_STR;

/********************************************************************************
*                             EXTERN FUNCTIONS
*********************************************************************************/

struct LDS_AUDIO_SPEAKER_OPERATION{

    struct LDS_HAL_COMMON comm;
    const char *name;
    
    int		(*lds_audio_spk_write)(char* pbuf,  unsigned int size );
    int		(*lds_audio_spk_get_volume)(void );
    void	(*lds_audio_spk_set_volume)(int volume );
    void 	(*lds_audio_spk_mute)(int mute );
    
};

/********************************************************************************
*                             EXTERN FUNCTIONS
*********************************************************************************/

extern struct LDS_AUDIO_SPEAKER_OPERATION lds_hal_audio_spk;

#ifdef __cplusplus
}
#endif

#endif