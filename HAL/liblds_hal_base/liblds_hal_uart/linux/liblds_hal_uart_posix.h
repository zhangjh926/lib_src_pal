#ifndef __LIBRS232_POSIX_H__
#define __LIBRS232_POSIX_H__

#include <termios.h>

#ifndef B460800
#define B460800 460800
#endif

struct rs232_posix_t {
	int fd;
	struct termios oldterm;
};

#define GET_PORT_STATE(fd, state) \
	if (tcgetattr(fd, state) < 0) { \
		DBG("tcgetattr() %d %s\n", errno, strerror(errno)) \
		return RS232_ERR_CONFIG; \
	}

#define SET_PORT_STATE(fd, state) \
	if (tcsetattr(fd, TCSANOW, state) < 0) { \
		DBG("tcsetattr() %d %s\n", errno, strerror(errno)) \
		return RS232_ERR_CONFIG; \
	} \

#endif