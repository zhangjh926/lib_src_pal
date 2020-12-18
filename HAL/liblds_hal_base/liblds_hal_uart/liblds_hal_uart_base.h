#ifndef __LDS_RS232_H__
#define __LDS_RS232_H__

#include "lds_hal_common.h"
#ifdef __cplusplus
extern "C"{
#endif

typedef enum   _LDS_UART_ErrorNo{
	LDS_UART_OPEN_ERROR,
	LDS_UART_INIT_ERROR,
	LDS_UART_START_ERROR,
}LDS_UART_ErrorNo;

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


typedef struct _LDS_RS232_CTX
{
	struct rs232_port_t	*p;
	char				dev_name[64];
	int					read_timeout;	// ms
	int					write_timeout;	// ms
	int					debug_msg;
	LDS_UART_ErrorNo	curr_err_state;
}LDS_RS232_CTX;

struct LDS_RS232_OPERATION
{
    struct LDS_HAL_COMMON  base;
	const char			  *name;

	/* common function */
	unsigned int	(*read)		(LDS_RS232_CTX *ctx, unsigned char *data, unsigned int size);
	unsigned int	(*write)	(LDS_RS232_CTX *ctx, unsigned char *data, unsigned int size);
	int				(*ioctl)	(LDS_RS232_CTX *ctx, LDS_CTRL_RS232 type, ...);

	/* component dependent fuction */
	unsigned short	(*crc)		(unsigned char *data, int size);

};


/* Define variable  -----------------------------------------------------*/
extern struct LDS_RS232_OPERATION lds_hal_rs232;

#ifdef __cplusplus
}
#endif

#endif /* __NCL_RS232_H__ */
