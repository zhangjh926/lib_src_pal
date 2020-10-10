#ifndef __I2C_LIB_H__
#define __I2C_LIB_H__
#include <stdint.h>

int i2c_write(int fd, uint8_t addr, void *buf, unsigned int nb,
		unsigned int ds);

int i2c_read(int fd, uint8_t addr, uint8_t reg, void *buf, unsigned int nb,
		unsigned int ds);

int i2c_write2(int fd, char *buf, int buf_len );
int i2c_read2(int fd, uint8_t addr, char *reg, int reg_len, char *buf, int buf_len );
int i2c_smbus_read(int fd, uint8_t addr, uint8_t *buf, unsigned int nb);
int i2c_open(char *adapter, uint8_t addr);

#endif /* __I2C_LIB_H__ */

