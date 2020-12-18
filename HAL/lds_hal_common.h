#ifndef _LDS_HAL_COMMON_H
#define _LDS_HAL_COMMON_H

#ifdef __cplusplus
extern "C"{
#endif


struct LDS_HAL_COMMON
{
	int            (*lds_hal_open)      (void *ctx_t, void *param); 
	int            (*lds_hal_close)     (void *ctx_t);


    // int            (*lds_hal_init)      (void *param);
    // int            (*lds_hal_deinit)    (void *ctx_t);

    int 		   (*lds_hal_start)     (void *ctx_t); //resume
    int 		   (*lds_hal_stop) 	    (void *ctx_t); //pause

    int            (*lds_hal_get_error) (void *ctx_t);
};

#ifdef __cplusplus
}
#endif

#endif
