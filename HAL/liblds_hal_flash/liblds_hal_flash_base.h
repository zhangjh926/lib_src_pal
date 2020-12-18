#ifndef _LDS_FLASH_OPERATION_H
#define _LDS_FLASH_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_FLASH_ErrorNo{
	LDS_FLASH_OPEN_ERROR,
	LDS_FLASH_INIT_ERROR,
	LDS_FLASH_START_ERROR,
}LDS_FLASH_ErrorNo;

typedef struct _LDS_FLASH_CTX{
	char dev_name[128];
	char dev_fd;
    LDS_FLASH_ErrorNo curr_err_state;
}LDS_FLASH_CTX;

struct LDS_FLASH_OPERATION
{
    struct  LDS_HAL_COMMON base;    
	const   char		  *name;

    // int     (*ioctl)(LDS_CTRL_FLASH, ...);
	int 	(*lds_hal_flash_copy)(LDS_FLASH_CTX *ctx, char *filename, char *dev_name);
	int		(*lds_hal_flash_erase)(LDS_FLASH_CTX *ctx, char *dev_name, unsigned long start_addr, unsigned int erase_block_count, int lock);
	int		(*lds_hal_flash_eraseall)(LDS_FLASH_CTX *ctx, char *dev_name, int is_formated_jffs2);
	int		(*lds_hal_flash_read)(LDS_FLASH_CTX *ctx, char *dev_name, unsigned int offset, char *out_data);
	int		(*lds_hal_flash_write)(LDS_FLASH_CTX *ctx, char *dev_name, unsigned int offset, char *in_data);
	int		(*lds_hal_flash_dump)(LDS_FLASH_CTX *ctx, char *filename, char *output_data);
	int		(*lds_hal_flash_compare)(LDS_FLASH_CTX *ctx, char *source_file_name, char *new_file_name);

};

extern struct LDS_FLASH_OPERATION lds_hal_flash;


#ifdef __cplusplus
}
#endif

#endif