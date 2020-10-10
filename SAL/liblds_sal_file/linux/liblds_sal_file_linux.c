#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#define _GNU_SOURCE
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>


#include "../liblds_sal_file_base.h"

static int				lds_sal_file_open(const char *pathname, int flags)
{
	return open(pathname, flags);
}

static int				lds_sal_file_close(int fd)
{
	return close(fd);
}
static long			lds_sal_file_read(int fd, void *buf, 	    unsigned long  count)
{
	return read(fd, buf, count);
}

static long 			lds_sal_file_write(int fd, const void *buf, unsigned long count)
{
	return write(fd, buf, count);
}

static long  			lds_sal_file_lseek(int fd, off_t offset, int whence)
{
	return lseek(fd, offset, whence);
}

static void*  			lds_sal_file_fopen(const char *pathname,  const char *mode)
{
	return (void *)fopen(pathname, mode);
}

static int 			lds_sal_file_fclose(void *stream)
{
	return fclose((FILE*)stream);
}

static long 			lds_sal_file_fread(void *ptr, long size, long nmemb, void *stream)
{
	return fread(ptr, size, nmemb, (FILE*)stream);
}

static long 			lds_sal_file_fwrite(const void *ptr, long size, long nmemb, void *stream)
{
	return fwrite(ptr, size, nmemb, (FILE*)stream);
}

static int	 			lds_sal_file_fallocate(int fd, int mode, off_t offset, off_t len)
{
	//return fallocate(fd, mode, offset, len);
	return 0;
}

static int 			lds_sal_file_fseek(void *stream, long offset, int whence)
{
	return fseek((FILE*)stream, offset , whence);
}

static long 			lds_sal_file_ftell(void *stream)
{
	return ftell((FILE*)stream);
}


struct LDS_SAL_FILE_OPERATION lds_sal_file = {
	.name = "lds_sal_file",
	
	.lds_file_open 	=  lds_sal_file_open,
	.lds_file_close 	=  lds_sal_file_close,
	.lds_file_read 		=  lds_sal_file_read,
	.lds_file_write		=  lds_sal_file_write,
	.lds_file_lseek 	=  lds_sal_file_lseek,

	.lds_file_fopen	=  lds_sal_file_fopen,
	.lds_file_fclose  	=  lds_sal_file_fclose,
	.lds_file_fread		=  lds_sal_file_fread,
	.lds_file_fwrite	=  lds_sal_file_fwrite,
	.lds_file_fseek	=  lds_sal_file_fseek,
	.lds_file_ftell		=  lds_sal_file_ftell,

	.lds_file_fallocate  =  lds_sal_file_fallocate,
};





