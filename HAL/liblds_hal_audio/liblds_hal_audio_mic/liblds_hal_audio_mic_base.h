#ifndef __LDS_AE_H__
#define __LDS_AE_H__

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

#define LINUX 1

#if LINUX
#include <alsa/asoundlib.h>
#include <stdint.h>
#endif

typedef struct _LDS_AE_STR
{
	const char*			device;
	const char*			vol_selem;
	const char*			vol_mute_selem;
	
	unsigned int 		pcm_format;
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
	int 				 acccess;	
	void 				*phandle;
	void 				*hw_params;
	void 				*sw_params;
	#endif

}LDS_AE_STR;

struct LDS_AUDIO_MIC_OPERATION
{
    struct  LDS_HAL_COMMON comm;
    const   char *name;
    int	    (*lds_audio_mic_read)( char* pbuf,  int size );
    int	    (*lds_audio_mic_get_volume)( void );
    void	(*lds_audio_mic_set_volume)(int volume );
    void 	(*lds_audio_mic_mute)( int mute );
};

/********************************************************************************
*                             EXTERN FUNCTIONS
*********************************************************************************/

extern struct LDS_AUDIO_MIC_OPERATION lds_hal_audio_mic;

#ifdef __cplusplus
}
#endif


#endif 

