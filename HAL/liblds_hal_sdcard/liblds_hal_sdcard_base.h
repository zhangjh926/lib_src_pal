#ifndef _LDS_SDCARD_OPERATION_H
#define _LDS_SDCARD_OPERATION_H

#include "lds_hal_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_SDCARD_ErrorNo{
	LDS_SDCARD_OPEN_ERROR,
	LDS_SDCARD_INIT_ERROR,
	LDS_SDCARD_START_ERROR,
}LDS_SDCARD_ErrorNo;

typedef enum _SDCardState{
    SDCARD_FULL,
    SDCARD_INSERT,
    SDCARD_REMOVE,
    SDCARD_WRITE_PROJECT,
    SDCARD_NOT_FORMAT,
    SDCARD_ERROR,
}SDCardState;

typedef enum _SDCardFsType
{
    SDCARD_FS_TYPE_FAT16,
    SDCARD_FS_TYPE_FAT32,
    SDCARD_FS_TYPE_EXFAT,
    SDCARD_FS_TYPE_NTFS,
    SDCARD_FS_TYPE_EXT3,
    SDCARD_FS_TYPE_EXT4,
}SDCardFsType;

typedef struct _LDS_SDCARD_CTX{
    char dev_name[128];
    int  dev_fd;
    LDS_SDCARD_ErrorNo curr_err_state;
}LDS_SDCARD_CTX;


typedef int (*LDS_SDCARD_STATE_CALLBACK)(SDCardState state);

struct LDS_SDCARD_OPERATION
{
    struct      LDS_HAL_COMMON base;
	const       char		  *name;

    int         (*lds_hal_sdcard_get_total_space)(LDS_SDCARD_CTX *ctx, char *mount_path);
    int         (*lds_hal_sdcard_get_free_space)(LDS_SDCARD_CTX *ctx, char *mount_path);
    SDCardState (*lds_hal_sdcard_get_state)(LDS_SDCARD_CTX *ctx, LDS_SDCARD_STATE_CALLBACK state_callback);
    SDCardFsType(*lds_hal_sdcard_get_filesystem_type)(LDS_SDCARD_CTX *ctx);
    int         (*lds_hal_sdcard_set_format)(LDS_SDCARD_CTX *ctx, SDCardFsType fs_type);
    int         (*lds_hal_sdcard_fallocate)(LDS_SDCARD_CTX *ctx, int fd, int mode, unsigned long offset, unsigned long len);
};

extern struct LDS_SDCARD_OPERATION lds_hal_sdcard;

#ifdef __cplusplus
}
#endif

#endif

