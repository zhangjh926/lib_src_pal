/* Header file include -------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

/* Define  -------------------------------------------------------------------*/

/* Define variable  ----------------------------------------------------------*/

/* Define extern variable & function  ----------------------------------------*/

/* Function prototype  -------------------------------------------------------*/

/* Function implementation  --------------------------------------------------*/

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int i2c_write(int fd, uint8_t addr, void *buf, unsigned int nb, unsigned int ds)
{
	struct i2c_rdwr_ioctl_data msgset;
	struct i2c_msg msg;

	msgset.nmsgs = 1;
	msgset.msgs = &msg;

	msg.addr = addr;
	msg.flags = 0;
	msg.buf = (unsigned char *)buf;
	msg.len = nb*ds;

#if 0
	int ret = write( fd, buf, msg.len);
	if( ret != msg.len )
		return -1;
	else
		return 0;
#else
	return ioctl(fd, I2C_RDWR, &msgset);
#endif
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int i2c_read(int fd, uint8_t addr, uint8_t reg, void *buf, unsigned int nb, unsigned int ds)
{
	struct i2c_rdwr_ioctl_data msgset;
	struct i2c_msg msgs[2];

	unsigned char packet[25];
	int packet_size = strlen((char*)buf);
	memcpy( (void*)packet, buf, 2 );

	if (nb < 1)
		return 0;

	msgset.nmsgs = 2;
	msgset.msgs = msgs;

	msgs[0].addr = addr;
	msgs[0].flags = 0;
	msgs[0].buf = packet;
	msgs[0].len = 2;

	msgs[1].addr = addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].buf = (unsigned char *)buf;
	msgs[1].len = nb*ds;

	return ioctl(fd, I2C_RDWR, &msgset);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int i2c_read2(int fd, uint8_t addr, char *reg, int reg_len, char *buf, int buf_len )
{
	struct i2c_rdwr_ioctl_data msgset;
	struct i2c_msg msgs[2];
	
	if (buf_len < 1)
		return 0;

	msgset.nmsgs = 2;
	msgset.msgs = msgs;

	msgs[0].addr = addr;
	msgs[0].flags = 0;
	msgs[0].buf = (unsigned char*)reg;
	msgs[0].len = reg_len;

	msgs[1].addr = addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].buf = (unsigned char*)buf;
	msgs[1].len = buf_len;

	return ioctl(fd, I2C_RDWR, &msgset);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int i2c_write2(int fd, char *buf, int buf_len )
{
	int ret = write( fd, buf, buf_len);
	if( ret != buf_len )
		return -1;
	else
		return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int i2c_smbus_read(int fd, uint8_t addr, uint8_t *buf, unsigned int nb)
{
	unsigned int i;

	for (i = 0; i < nb; i++)
		if (read(fd, &buf[i], 1) != 1)
			return -1;
	return 0;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
int i2c_open(char *adapter, uint8_t addr)
{
	int fd = -1;
	unsigned long funcs;

	fd = open(adapter, O_RDWR);
	if (fd < 0) {
		perror("open");
		return -ENODEV;
	}

	if (ioctl(fd, I2C_SLAVE_FORCE/*I2C_SLAVE*/, addr) < 0) {
		perror("set slave address");
		return -ENODEV;
	}

	/* sanity check */
	if (ioctl(fd, I2C_FUNCS, &funcs) < 0) {
		perror("get functions");
		return -EINVAL;
	}

	/* make sure this is an i2c device */
	if (!(funcs & I2C_FUNC_I2C))
		return -EINVAL;

	return fd;
}

