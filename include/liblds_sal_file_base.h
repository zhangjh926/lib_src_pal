#ifndef __LIBLDS_SAL_FILE_BASE_H
#define __LIBLDS_SAL_FILE_BASE_H

#ifdef __cplusplus
extern "C"{
#endif

struct LDS_SAL_FILE_OPERATION
{
	const char		*name;
	
	int				(*lds_file_open)(const char *pathname, int flags);
	int				(*lds_file_close)(int fd);
	long				(*lds_file_read)(int fd, void *buf, 	    unsigned long  count);
	long 			(*lds_file_write)(int fd, const void *buf, unsigned long count);
	long  			(*lds_file_lseek)(int fd, off_t offset, int whence);

	void*  			(*lds_file_fopen)(const char *pathname,  const char *mode);
	int 				(*lds_file_fclose)(void *stream);
	long 			(*lds_file_fread)(void *ptr, long size, long nmemb, void *stream);
	long 			(*lds_file_fwrite)(const void *ptr, long size, long nmemb, void *stream);
	int 				(*lds_file_fseek)(void *stream, long offset, int whence);
	long 			(*lds_file_ftell)(void *stream);

	int 				(*lds_file_remove)(const char *pathname);
	int	 			(*lds_file_fallocate)(int fd, int mode, off_t offset, off_t len);
};

extern struct LDS_SAL_FILE_OPERATION lds_sal_file;

#ifdef __cplusplus
}
#endif


#endif