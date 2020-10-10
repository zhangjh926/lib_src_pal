#ifndef _LDS_HAL_COMMON_H
#define _LDS_HAL_COMMON_H

#ifdef __cplusplus
extern "C"{
#endif


struct LDS_HAL_COMMON
{
       int            (*lds_hal_init)             (void);
       int            (*lds_hal_deinit)         (void);

	int            (*lds_hal_open)          (char *dev_name);                                                                                                                                                                                                                         
	int            (*lds_hal_close)          (int dev_fd);

	int 		   (*lds_hal_start)          (void); //resume
	int 		   (*lds_hal_stop) 	         (void); //pause

       int            (*lds_hal_get_error)   (void);
};

#ifdef __cplusplus
}
#endif

#endif
