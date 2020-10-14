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

struct LDS_SDCARD_OPERATION
{
    struct  LDS_HAL_COMMON comm;    
	const   char		*name;

    int         (*lds_hal_sdcard_get_total_space)(void);
    int         (*lds_hal_sdcard_get_free_space)(void);
    SDCardState (*lds_hal_sdcard_get_state)(void);
    SDCardFsType(*lds_hal_sdcard_get_filesystem_type)(void);
    int         (*lds_hal_sdcard_set_format)(SDCardFsType fs_type);
    int         (*lds_hal_sdcard_fallocate)(int fd, int mode, unsigned long offset, unsigned long len);
};

extern struct LDS_SDCARD_OPERATION lds_hal_sdcard;

#ifdef __cplusplus
}
#endif

#endif

