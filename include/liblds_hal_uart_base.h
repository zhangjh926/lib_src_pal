#ifndef __LDS_RS232_H__
#define __LDS_RS232_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif
/* Header file include --------------------------------------------------*/

/* Define  --------------------------------------------------------------*/
enum LDS_RS232_BAUD
{
	LDS_RS232_BAUD_300,
	LDS_RS232_BAUD_2400,
	LDS_RS232_BAUD_4800,
	LDS_RS232_BAUD_9600,
	LDS_RS232_BAUD_19200,
	LDS_RS232_BAUD_38400,
	LDS_RS232_BAUD_57600,
	LDS_RS232_BAUD_115200,
	LDS_RS232_BAUD_460800,
	LDS_RS232_BAUD_MAX
};

typedef enum tagRS232_CTRL
{
	LDS_CTRL_RS232_END,
	LDS_CTRL_RS232_BAUD,
	LDS_CTRL_RS232_READ_TIMEOUT,
	LDS_CTRL_RS232_WRITE_TIMEOUT,
	LDS_CTRL_RS232_DEBUG,
	LDS_CTRL_RS232_TCSBRKP,
	LDS_CTRL_RS232_MAX
}LDS_CTRL_RS232;

struct LDS_RS232_OPERATION
{
    struct LDS_HAL_COMMON comm;
	const char		*name;
	int				ctxsize;
	int				maxctrl;

	/* common function */
	unsigned int	(*read)		(unsigned char *data, unsigned int size);
	unsigned int	(*write)	(unsigned char *data, unsigned int size);
	int				(*ioctl)	(LDS_CTRL_RS232 type, ...);

	/* component dependent fuction */
	unsigned short	(*crc)		(unsigned char *data, int size);

};


/* Define variable  -----------------------------------------------------*/
extern struct LDS_RS232_OPERATION lds_hal_rs232;

#ifdef __cplusplus
}
#endif

#endif /* __NCL_RS232_H__ */
