#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <alsa/asoundlib.h>

#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/resource.h>

#include "liblds_hal_audio_speaker_base.h"

static snd_pcm_uframes_t buffer_size;
static snd_pcm_uframes_t period_size;
static LDS_AD_STR *ptAudio = NULL;
/* define and enums - Andy */
static int bEnable = 0 ;

/********************************************************************************
*	Description		: stop PCM device after PB finished.
*	Argurments		: none
*	Return value	:
*	Modify			: 
*	warning			:
********************************************************************************/
void lds_audio_speaker_output_play_sync( void )
{
	int ret = 0;;

	if(ptAudio->phandle != NULL)
	{
		ret = snd_pcm_drain( ptAudio->phandle );
	}

}

/*******************************************************************************
*	Description		: stop PCM device after PB finished.
*	Argurments		: none
*	Return value	:
*	Modify			: 2012-07-19(thr)
*	warning			:
*******************************************************************************/
void lds_auido_speaker_output_play_stop( void )
{
	int ret = 0;

	if(ptAudio->phandle != NULL)
	{
		ret = snd_pcm_drop( ptAudio->phandle );
	}
}
/******************************************************************************
* @desc
* set alas sw param
*
* @func
* __set_sw_params()
*
*******************************************************************************/
static int __set_sw_params( void )
{
	int	err;

	if (!buffer_size)   buffer_size = 8192;
	if (!period_size)   period_size = buffer_size>>2;

#if 0 // test
	period_size = 4096;
	buffer_size = 0;
#endif
	
	// allocate an invalid snd_pcm_sw_params_t using standard alloca.
	snd_pcm_sw_params_alloca(&(ptAudio->sw_params));
	
	// Fill params with a full configuration space for a PCM.
	if ((err = snd_pcm_sw_params_current(ptAudio->phandle, ptAudio->sw_params) < 0)) 
	{
		fprintf(stderr, "Unable to determine current swparams\n");
		return err;
	}

	// Set avail min inside a software configuration container.
	if ((err = snd_pcm_sw_params_set_avail_min(ptAudio->phandle, ptAudio->sw_params, period_size) < 0)) 
	{
		fprintf(stderr, "Unable to set start threshold mode\n");
		return err;
	}
	
	// Set start threshold inside a software configuration container.
	if ((err = snd_pcm_sw_params_set_start_threshold(ptAudio->phandle, ptAudio->sw_params, buffer_size) < 0)) 
	{
		fprintf(stderr, "Unable to set start threshold mode\n");
		return err;
	}

#if 0 // test
	// Set avail min inside a software configuration container.
	if ((err = snd_pcm_sw_params_set_avail_min(ptAudio->phandle, ptAudio->sw_params, period_size) < 0)) 
	{
		fprintf(stderr, "Unable to set start threshold mode\n");
		return err;
	}
	
	// Set start threshold inside a software configuration container.
	if ((err = snd_pcm_sw_params_set_start_threshold(ptAudio->phandle, ptAudio->sw_params, (buffer_size/period_size) * period_size) < 0)) 
	{
		fprintf(stderr, "Unable to set start threshold mode\n");
		return err;
	}
	
	// Set start threshold inside a software configuration container.
	if ((err = snd_pcm_sw_params_set_stop_threshold(ptAudio->phandle, ptAudio->sw_params, buffer_size) < 0)) 
	{
		fprintf(stderr, "Unable to set start threshold mode\n");
		return err;
	}
#endif

	// Install one PCM hardware configuration chosen from a configuration space and snd_pcm_prepare it.
	if ((err = snd_pcm_sw_params(ptAudio->phandle, ptAudio->sw_params)) < 0) 
	{
		fprintf(stderr, "Unable to set sw params\n");
		return err;
	}	
	
	return err;
}

/******************************************************************************
* @desc
* set alas hw param
*
* @func
* __set_hw_params()
*
*******************************************************************************/
static int __set_hw_params( void )
{
	int err;
	
	buffer_size = 0;
	period_size = 0;
	
	// allocate an invalid snd_pcm_hw_params_t using standard malloc.
	snd_pcm_hw_params_alloca(&(ptAudio->hw_params));

	// Fill params with a full configuration space for a PCM.
	if ((err = snd_pcm_hw_params_any(ptAudio->phandle, ptAudio->hw_params) < 0)) 
	{
		fprintf(stderr, "cannot initialize hardware parameter structure\n");
		return err;
	}

	// Restrict a configuration space to contain only real hardware rates.(0 = disable, 1 = enable)
	if ((err = snd_pcm_hw_params_set_rate_resample(ptAudio->phandle, ptAudio->hw_params, 1) < 0)) 
	{
		fprintf(stderr, "Resampling setup failed\n");
		return err;
	}

	// Restrict a configuration space to contain only one access type.
	if ((err = snd_pcm_hw_params_set_access(ptAudio->phandle, ptAudio->hw_params, ptAudio->acccess)) < 0) 
	{
		fprintf(stderr, "cannot set access type\n");
		return err;
	}

	// Restrict a configuration space to contain only one format.
	if ((err = snd_pcm_hw_params_set_format(ptAudio->phandle, ptAudio->hw_params, ptAudio->pcm_format) < 0)) 
	{
		fprintf(stderr, "cannot set sample format\n");
		return err;
	}

	// Restrict a configuration space to contain only one channels count.
	if ((err = snd_pcm_hw_params_set_channels(ptAudio->phandle, ptAudio->hw_params, ptAudio->channel_num)) < 0) 
	{
		fprintf(stderr, "cannot set channel count\n");
		return err;
	}

	// Restrict a configuration space to have rate nearest to a target.
	if ((err = snd_pcm_hw_params_set_rate_near(ptAudio->phandle, ptAudio->hw_params, &(ptAudio->sampling_rate), 0)) < 0) 
	{
		fprintf(stderr, "cannot set sample rate\n");
		return err;
	}

	// default buffer setting 
	if (!ptAudio->buffer_time)   ptAudio->buffer_time = 500000;	// ring buffer length in us
	if (!ptAudio->period_time)   ptAudio->period_time = 100000; // period time in us

	if( ptAudio->buffer_time )
	{
		// Restrict a configuration space to have buffer time nearest to a target.
		if ((err = snd_pcm_hw_params_set_buffer_time_near(ptAudio->phandle, ptAudio->hw_params, &(ptAudio->buffer_time), 0)) < 0) 
		{
			fprintf(stderr, "cannot set buffer time\n");
			return err;
		}

		if ((err = snd_pcm_hw_params_get_buffer_size(ptAudio->hw_params, &buffer_size)) < 0) 
		{
			fprintf(stderr, "cannot to get buffer size\n");
			return err;
		}
		//fprintf(stderr, ">>>>> [%s:%d]: buffer_size(%d)\n", __FILE__, __LINE__, buffer_size);
	}	

	if( ptAudio->period_time )
	{
		// Restrict a configuration space to have period time nearest to a target.
		if ((err = snd_pcm_hw_params_set_period_time_near(ptAudio->phandle, ptAudio->hw_params, &(ptAudio->period_time), 0)) < 0) 
		{
			fprintf(stderr, "cannot set period times\n");
			return err;
		} 
		
		if ((err = snd_pcm_hw_params_get_period_size(ptAudio->hw_params, &period_size, 0)) < 0) 
		{
			fprintf(stderr, "cannot to get period size\n");
			return err;
		}
		//fprintf(stderr, ">>>>> [%s:%d]: period_size(%d)\n", __FILE__, __LINE__, period_size);
	}

	// Install one PCM hardware configuration chosen from a configuration space and snd_pcm_prepare it.
	if ((err = snd_pcm_hw_params(ptAudio->phandle, ptAudio->hw_params)) < 0) 
	{
		fprintf(stderr, "cannot set parameters\n");
		return err;
	}	

	return err;
}

/******************************************************************************
* @desc
* alsa playback init
*
* @parm_in
* ptAudio	: struct _LDS_AD_STR
*
* @return   
* alsa error code.
*
* @func
* lds_audio_speaker_Init()
*
*******************************************************************************/
int lds_audio_speaker_init( void)
{
	int err = 0;

      if( bEnable == 1 )
     {
    	fprintf( stdout, "[%s:%d] NCL_AD_Init have already initialize!\n", __FILE__, __LINE__ );
    	return err;
     }

	// opens a PCM (Playback)
	if ((err = snd_pcm_open(&(ptAudio->phandle), ptAudio->device, SND_PCM_STREAM_PLAYBACK, 0)) < 0) 
	{
		fprintf(stderr, ">>>>> [%s:%d]: cannot open audio device(%s)\n", __FILE__, __LINE__, snd_strerror(err));
		return err;
	}

	// set hw parameter
	if ((err = __set_hw_params()) < 0) 
	{
		fprintf(stderr, ">>>>> [%s:%d]: Setting of hw params failed(%s)\n", __FILE__, __LINE__, snd_strerror(err));
		return err;
	}	

	// set sw parameter
	if ( ptAudio->sw_param_enable )
	{
		if ((err = __set_sw_params()) < 0) 
		{
			fprintf(stderr, ">>>>> [%s:%d]: Setting of sw params failed(%s)\n", __FILE__, __LINE__, snd_strerror(err));
			return err;
		}
	}

	snd_pcm_drop(ptAudio->phandle);
	

	/* Andy */
	bEnable = 1;

	return err;
}

/******************************************************************************
* @desc
* alsa playback deinit
*
* @parm_in
* ptAudio	: struct _LDS_AD_STR
*
* @return   
* void
*
* @func
* lds_audio_speaker_deinit()
*
*******************************************************************************/
int lds_audio_speaker_deinit( void )
{
    if( bEnable == 0 )
    {
    	fprintf( stdout, "[%s:%d] you have to call NCL_AD_DeInit first time!\n", __FILE__, __LINE__ );
    	return -1;
    }

#if 0 // Not used.
	/*
	* There are two ways of allocating such structures:
	* 1) Use snd_xxx_malloc() and snd_xxx_free() to allocate memory from the heap, or
	* 2) use snd_xxx_alloca() to allocate memory from the stack.
	*
	* The snd_xxx_alloca() functions behave just like alloca(): their memory
	* is automatically freed when the function returns.	
	*/
	if(ptAudio->hw_params != NULL)
		snd_pcm_hw_params_free(ptAudio->hw_params);

	if(ptAudio->sw_params != NULL)
		snd_pcm_sw_params_free(ptAudio->sw_params);
#endif
	
	if(ptAudio->phandle != NULL)
	{
		snd_pcm_drain(ptAudio->phandle);
		snd_pcm_close(ptAudio->phandle);
	}
    return 0;
}

/******************************************************************************
* @desc
* alsa playback data write
*
* @parm_in
* ptAudio	: struct _LDS_AD_STR
* pbuf		: write buff
* size		: wirte size
*
* @return   
* success(0), fail(-1)
*
* @func
* lds_audio_speaker_write()
*
*******************************************************************************/
int lds_audio_speaker_write( char* pbuf,  unsigned int size )
{
	int err; 
	snd_pcm_sframes_t avail;
 
   	if( bEnable == 0 )
    {
    	fprintf( stdout, "[%s:%d] you have to call NCL_AD_Init first time!\n", __FILE__, __LINE__ );
    	return 0;
    }

	if( ptAudio->phandle == NULL )
		return -1;

	if( (err = snd_pcm_state(ptAudio->phandle)) == SND_PCM_STATE_SETUP )
	{
		fprintf(stderr, ">>>>> [%s:%d]: stop state(%d)\n", __FILE__, __LINE__, err);
		return -1;
	}

	size = (size / ptAudio->channel_num / ptAudio->bit_per_sample); 
	while(size > 0)
	{
		avail = snd_pcm_avail_update(ptAudio->phandle);
		//fprintf(stderr, ">>>>> [%s:%d]: size(%d), avail(%d)\n", __FILE__, __LINE__, size, avail);		
		if( avail < 0 )
		{
			fprintf(stderr, ">>>>> [%s:%d]: avail error(%s)\n", __FILE__, __LINE__, snd_strerror(err));
			snd_pcm_recover( ptAudio->phandle, avail, 1 );
		}
		else if((unsigned int )avail < size)
		{
			snd_pcm_wait( ptAudio->phandle, 1000 );
		}
		else
		{
			// Write interleaved frames to a PCM.
			if( ptAudio->acccess == SND_PCM_ACCESS_RW_INTERLEAVED )
				err = snd_pcm_writei( ptAudio->phandle, pbuf, size );
			// Write interleaved frames to a PCM using direct buffer (mmap)
			else if( ptAudio->acccess == SND_PCM_ACCESS_MMAP_INTERLEAVED )
				err = snd_pcm_mmap_writei( ptAudio->phandle, pbuf, size );
			
			if( err == -EPIPE || err == -EBADFD)
			{
				//fprintf(stderr, ">>>>> [%s:%d]: %s, size(%d), avail(%ld)\n", __FILE__, __LINE__, snd_strerror(err), size, avail);
				snd_pcm_prepare(ptAudio->phandle);
			}
			else if( err < 0 )
			{
				fprintf(stderr, ">>>>> [%s:%d]: write error(%d:%s), size(%d), avail(%ld)\n", __FILE__, __LINE__, err, snd_strerror(err), size, avail);
				snd_pcm_recover( ptAudio->phandle, err, 1 );
			}else if( (uint32_t)err <= size ){ 
				size -= err;
				pbuf += (err * ptAudio->channel_num * ptAudio->bit_per_sample); 
			}
		}
	}

	return 0;
}

int lds_audio_speaker_open(char *dev_name)
{
    return 0;
}

int lds_audio_speaker_close(int dev_fd)
{
    return 0;
}

/******************************************************************************
* @desc
* alsa playback start
*
* @parm_in
* ptAudio	: struct _LDS_AD_STR
*
* @return
* void
*
* @func
* lds_audio_speaker_start()
*
*******************************************************************************/
int lds_audio_speaker_start( void )
{
	if( bEnable == 0 )
	{
	    fprintf( stdout, "[%s:%d] you have to call NCL_AD_Init first time!\n", __FILE__, __LINE__ );
	    return -1;
	}

	if(ptAudio->phandle == NULL)
	    return -1;

	snd_pcm_prepare(ptAudio->phandle);

    return 0;
}

/******************************************************************************
* @desc
* alsa playback stop
*
* @parm_in
* ptAudio	: struct _LDS_AD_STR
*
* @return   
* void
*
* @func
* lds_audio_speaker_stop()
*
*******************************************************************************/
int lds_audio_speaker_stop( void )
{
    if( bEnable == 0 )
    {
    	fprintf( stdout, "[%s:%d] you have to call NCL_AD_Init first time!\n", __FILE__, __LINE__ );
    	return -1;
    }

	if(ptAudio->phandle == NULL)
		return -1;

	snd_pcm_drop(ptAudio->phandle);

    return 0;
}

/******************************************************************************
* @desc
* Set value of playback volume control of a mixer simple element.
*
* @parm_in
* ptAudio	: struct _LDS_AD_STR
* value		: volume
*
* @return   
* void
*
* @func
* lds_audio_speaker_set_volume()
*
*******************************************************************************/
void lds_audio_speaker_set_volume( int volume )
{
	snd_mixer_t *handle;
	snd_mixer_selem_id_t *sid;
	const char* card = "default";

     if( bEnable == 0 )
     {
    	fprintf( stdout, "[%s:%d] you have to call LDS_AD_Init first time!\n", __FILE__, __LINE__ );
    	return;
     }

	if(ptAudio->vol_selem == NULL)
		return;

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, ptAudio->vol_selem);
	snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

	if(elem)
	{
		//snd_mixer_selem_set_playback_volume( elem, 0 , volume );
		snd_mixer_selem_set_playback_volume_all( elem, volume );
		//fprintf( stdout, ">>>>> [%s:%d] set volume(%d)\n", __FILE__, __LINE__, volume);
	}
	else
	{
		fprintf( stderr, ">>>>> [%s:%d] find elem fail\n", __FILE__, __LINE__);
	}
	
	snd_mixer_close(handle);
}

/******************************************************************************
* @desc
* Return value of playback volume control of a mixer simple element.
*
* @parm_in
* ptAudio	: struct _LDS_AD_STR
*
* @return   
* playback volume
*
* @func
* lds_audio_speaker_get_volume()
*
*******************************************************************************/
int lds_audio_speaker_get_volume( void )
{
	int volume = 0;
	long value;
	snd_mixer_t *handle;
	snd_mixer_selem_id_t *sid;
	const char* card = "default";	

     if( bEnable == 0 )
     {
    	fprintf( stdout, "[%s:%d] you have to call NCL_AD_Init first time!\n", __FILE__, __LINE__ );
    	return 0;
     }

	if(ptAudio->vol_selem == NULL)
		return volume;

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, ptAudio->vol_selem);
	snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

	if(elem)
	{
		snd_mixer_selem_get_playback_volume(elem, 0, &value);
		volume = (unsigned int)value;
		//fprintf( stdout, ">>>>> [%s:%d] get volume(%d)\n", __FILE__, __LINE__, volume);
	}
	else
	{
		fprintf( stderr, ">>>>> [%s:%d] find elem fail\n", __FILE__, __LINE__);
	}
	
	snd_mixer_close(handle);

	return volume;
}

/******************************************************************************
* @desc
* Set value of playback mute control of a mixer simple element.
*
* @parm_in
* ptAudio	: struct _LDS_AD_STR
* mute	 	: on(1), off(0)
*
* @return   
* void
*
* @func
* lds_audio_speaker_mute()
*
*******************************************************************************/
void lds_audio_speaker_mute( int mute )
{
	snd_mixer_t *handle;
	snd_mixer_selem_id_t *sid;
	const char* card = "default";	

     if( bEnable == 0 )
     {
    	fprintf( stdout, "[%s:%d] you have to call NCL_AD_Init first time!\n", __FILE__, __LINE__ );
    	return;
     }

	if(ptAudio->vol_mute_selem == NULL)
		return;
		
	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, ptAudio->vol_mute_selem);
	snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

	if(elem)
	{
		snd_mixer_selem_set_playback_switch( elem, 0 , mute );
		//fprintf( stdout, ">>>>> [%s:%d] Mute (%s)\n", __FILE__, __LINE__, mute?"ON":"OFF");
	}
	else
	{
		fprintf( stderr, ">>>>> [%s:%d] find elem fail\n", __FILE__, __LINE__);
	}
	
	snd_mixer_close(handle);
}


/******************************************************************************
* @desc
* Set value of playback control of a mixer simple element.
*
* @parm_in
* selem_name : mixer simple element name
* value		 : control value
*
* @return   
* void
*
* @func
* lds_audio_speaker_set_mixer_selem_value()
*
*******************************************************************************/
void lds_audio_speaker_set_mixer_selem_value( const char* selem_name, long value )
{
	snd_mixer_t *handle;
	snd_mixer_selem_id_t *sid;
	const char* card = "default";

     if( bEnable == 0 )
     {
    	fprintf( stdout, "[%s:%d] you have to call LDS_AD_Init first time!\n", __FILE__, __LINE__ );
    	return;
     }

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, selem_name);
	snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

	if(elem)
	{
		//snd_mixer_selem_set_playback_volume( elem, 0 , value );
		snd_mixer_selem_set_playback_volume_all( elem, value );
		//fprintf( stdout, ">>>>> [%s:%d] set value(%d)\n", __FILE__, __LINE__, value);
	}
	else
	{
		fprintf( stderr, ">>>>> [%s:%d] find elem fail\n", __FILE__, __LINE__);
	}
	
	snd_mixer_close(handle);
}

/******************************************************************************
* @desc
* Return value of playback control of a mixer simple element.
*
* @parm_in
* selem_name : mixer simple element name
*
* @return   
* playback control value
*
* @func
* lds_audio_speaker_get_mixer_selem_value()
*
*******************************************************************************/
long lds_audio_speaker_get_mixer_selem_value( const char* selem_name )
{
	long value = 0;
	snd_mixer_t *handle;
	snd_mixer_selem_id_t *sid;
	const char* card = "default";	

     if( bEnable == 0 )
     {
    	fprintf( stdout, "[%s:%d] you have to call NCL_AD_Init first time!\n", __FILE__, __LINE__ );
    	return -1;
     }

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, selem_name);
	snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

	if(elem)
	{
		snd_mixer_selem_get_playback_volume(elem, 0, &value);
		//fprintf( stdout, ">>>>> [%s:%d] get value(%d)\n", __FILE__, __LINE__, value);
	}
	else
	{
		fprintf( stderr, ">>>>> [%s:%d] find elem fail\n", __FILE__, __LINE__);
	}
	
	snd_mixer_close(handle);

	return value;
}

/******************************************************************************
* @desc
* Get range for playback of a mixer simple element.
*
* @parm_in
* selem_name : mixer simple element name
* min		 : Pointer to returned minimum
* max		 : Pointer to returned maximum
*
* @return   
* void
*
* @func
* lds_audio_speaker_get_mixer_selem_range()
*
*******************************************************************************/
void lds_audio_speaker_get_mixer_selem_range( const char* selem_name, long* min, long* max )
{
	snd_mixer_t *handle;
	snd_mixer_selem_id_t *sid;
	const char* card = "default";	

     if( bEnable == 0 )
     {
    	fprintf( stdout, "[%s:%d] you have to call NCL_AD_Init first time!\n", __FILE__, __LINE__ );
    	return;
     }

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, selem_name);
	snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

	if(elem)
	{
		snd_mixer_selem_get_playback_volume_range(elem, min, max);
		//fprintf( stdout, ">>>>> [%s:%d] get min(%d), max(%d)\n", __FILE__, __LINE__, *min, *max );
	}
	else
	{
		fprintf( stderr, ">>>>> [%s:%d] find elem fail\n", __FILE__, __LINE__);
	}
	
	snd_mixer_close(handle);
}

/******************************************************************************
* @desc
* Set value of playback switch control of a mixer simple element
*
* @parm_in
* selem_name : mixer simple element name
* value 	 : on(1), off(0)
*
* @return   
* void
*
* @func
* lds_audio_speaker_set_mixer_selem_switch()
*
*******************************************************************************/
void lds_audio_speaker_set_mixer_selem_switch( const char* selem_name, int value )
{
	snd_mixer_t *handle;
	snd_mixer_selem_id_t *sid;
	const char* card = "default";
	
     if( bEnable == 0 )
     {
    	fprintf( stdout, "[%s:%d] you have to call LDS_AD_Init first time!\n", __FILE__, __LINE__ );
    	return;
     }

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, selem_name);
	snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

	if(elem)
	{
		snd_mixer_selem_set_playback_switch( elem, 0 , value );
		//fprintf( stdout, ">>>>> [%s:%d] switch (%s)\n", __FILE__, __LINE__, value?"ON":"OFF");
	}
	else
	{
		fprintf( stderr, ">>>>> [%s:%d] find elem fail\n", __FILE__, __LINE__);
	}
	
	snd_mixer_close(handle);
}

struct LDS_AUDIO_SPEAKER_OPERATION lds_hal_audio_spk = {
    .name               = "lds_hal_audio_spk",
    .comm.lds_hal_open  = lds_audio_speaker_open,
    .comm.lds_hal_close = lds_audio_speaker_close,
    .comm.lds_hal_init  = lds_audio_speaker_init,
    .comm.lds_hal_deinit= lds_audio_speaker_deinit,
    .comm.lds_hal_start = lds_audio_speaker_start,
    .comm.lds_hal_stop  = lds_audio_speaker_stop,

    .lds_audio_spk_write        = lds_audio_speaker_write,
    .lds_audio_spk_get_volume   = lds_audio_speaker_get_volume,
    .lds_audio_spk_set_volume   = lds_audio_speaker_set_volume,
    .lds_audio_spk_mute         = lds_audio_speaker_mute,
};
