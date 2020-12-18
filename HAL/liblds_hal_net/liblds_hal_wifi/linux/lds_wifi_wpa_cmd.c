/*
 * libwpa_test - Test program for libwpa_client.* library linking
 * Copyright (c) 2015, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */
#include <sys/ioctl.h>
#include <unistd.h>
#include <net/if.h>
#include <pthread.h>
//#include "includes.h"

//#include "wpa_ctrl.h"
#include "liblds_hal_wifi_base.h"
#include "lds_wifi_wpa_cmd.h"
#define _NEW_WIFI_SETUP_

static const char *ctrl_iface_dir = CONFIG_CTRL_IFACE_DIR;
static struct wpa_ctrl *ctrl_conn = NULL;
WIFI_PARAM g_wifi_param;
int g_threadFirst = 0;

char * os_strncpy(char *dest, const char *src, size_t n)
{
	char *d = dest;

	while (n--) {
		*d = *src;
		if (*src == '\0')
			break;
		d++;
		src++;
	}

	return dest;
}


void os_free(void *ptr)
{
	free(ptr);
}

static inline int os_snprintf_error(size_t size, int res)
{
	return res < 0 || (unsigned int) res >= size;
}

size_t os_strlen(const char *s)
{
	const char *p = s;
	while (*p)
		p++;
	return p - s;
}

int os_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return 0;
		printf("enter os_strncmp=> s1:%s, s2:%s, n=%d \r\n", s1, s2, n);
	while (*s1 == *s2) {
		if (*s1 == '\0')
			break;
		s1++;
		s2++;
		n--;
		printf("os_strncmp=> n=%d \r\n", n);
		if (n == 0)
			return 0;
	}

	return *s1 - *s2;
}

char * os_strstr(const char *haystack, const char *needle)
{
	size_t len = os_strlen(needle);
	while (*haystack) {
		if (os_strncmp(haystack, needle, len) == 0)
			return (char *) haystack;
		haystack++;
	}

	return NULL;
}


int os_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list ap;
	int ret;

	/* See http://www.ijs.si/software/snprintf/ for portable
	 * implementation of snprintf.
	 */

	va_start(ap, format);
	ret = vsnprintf(str, size, format, ap);
	va_end(ap);
	if (size > 0)
		str[size - 1] = '\0';
	return ret;
}

int write_cmd(char *buf, size_t buflen, const char *cmd, int argc, char *argv[])
{
	int i, res;
	char *pos, *end;

	pos = buf;
	end = buf + buflen;

	res = os_snprintf(pos, end - pos, "%s", cmd);
	if (os_snprintf_error(end - pos, res))
		goto fail;
	pos += res;

	for (i = 0; i < argc; i++) {
		res = os_snprintf(pos, end - pos, " %s", argv[i]);
		if (os_snprintf_error(end - pos, res))
			goto fail;
		pos += res;
	}

	buf[buflen - 1] = '\0';
	return 0;

fail:
	printf("Too long command\n");
	return -1;
}

static void wpa_cli_msg_cb(char *msg, size_t len)
{
	printf("%s\n", msg);
}

static int _wpa_ctrl_command(struct wpa_ctrl *ctrl, char *buf1, size_t *lens, const char *cmd, int print)
{
	char buf[4096];
	size_t len ;//= lens;
	int ret = -1;
	
	printf("_wpa_ctrl_command\r\n");
	if (ctrl_conn == NULL) {
		printf("Not connected to wpa_supplicant - command dropped.\n");
		return -1;
	}
	 printf("_wpa_ctrl_command1\r\n");
	 /*
	if (ifname_prefix) {
		 printf("_wpa_ctrl_command1111\r\n");
		os_snprintf(buf, sizeof(buf), "IFNAME=%s %s",
			    ifname_prefix, cmd);
		buf[sizeof(buf) - 1] = '\0';
		cmd = buf;
	}
	*/
	 printf("_wpa_ctrl_command2, print:%d\r\n", print);
	len = sizeof(buf) - 1;
	memset(buf, 0, 4096);
	printf("_wpa_ctrl_command3111, ctrl_conn:%d,cmd:%s,lenscmd:%d,len:%d\r\n", ctrl_conn, cmd, os_strlen(cmd),len);
	//int wpa_ctrl_request(struct wpa_ctrl *ctrl, const char *cmd, size_t cmd_len,
	//	     char *reply, size_t *reply_len,
	//	     void (*msg_cb)(char *msg, size_t len))
	ret = wpa_ctrl_request(ctrl_conn, cmd, os_strlen(cmd), buf, &len,
			       wpa_cli_msg_cb);
				
			
	printf("wpa_ctrl_request11, buf:%s,len:%d,ret:%d\r\n", buf, len, ret);
	*lens = len;	
	if (ret == -2) {
		printf("'%s' command timed out.\n", cmd);
		return -2;
	} else if (ret < 0) {
		printf("'%s' command failed.\n", cmd);
		return -1;
	}
	memcpy(buf1, buf, 4096);
	//memcpy(*lens, len, sizeof(len));
	//*lens = len;
	 printf("_wpa_ctrl_command33\r\n");
	 
	 /*
	if (print) {
		buf[len] = '\0';
		printf("%s", buf);
		if (interactive && len > 0 && buf[len - 1] != '\n')
			printf("\n");
	}
	*/
	 printf("_wpa_ctrl_command34444\r\n");
	return 0;
}

/*
static int _wpa_ctrl_command(struct wpa_ctrl *ctrl, char *buf1, size_t *lens, const char *cmd, int print)
{
	char buf[4096];
	size_t len ;
	int ret = -1;
 printf("_wpa_ctrl_command\r\n");
	if (ctrl_conn == NULL) {
		printf("Not connected to wpa_supplicant - command dropped.\n");
		return -1;
	}
	 printf("_wpa_ctrl_command1\r\n");
	 
	if (ifname_prefix) {
		 printf("_wpa_ctrl_command1111\r\n");
		os_snprintf(buf, sizeof(buf), "IFNAME=%s %s",
			    ifname_prefix, cmd);
		buf[sizeof(buf) - 1] = '\0';
		cmd = buf;
	}
	
	 printf("_wpa_ctrl_command2, print:%d\r\n", print);
	len = sizeof(buf) - 1;
	//memset(buf, 0, 4096);
	printf("_wpa_ctrl_command3, ctrl_conn:%d,cmd:%s,lenscmd:%d,len:%d\r\n", ctrl_conn, cmd, os_strlen(cmd),len);

	ret = wpa_ctrl_request(ctrl_conn, cmd, os_strlen(cmd), buf, len,
			       wpa_cli_msg_cb);
				
				
	printf("wpa_ctrl_request, buf:%s,len:%d,ret:%d\r\n", buf, len, ret);
	if (ret == -2) {
		printf("'%s' command timed out.\n", cmd);
		return -2;
	} else if (ret < 0) {
		printf("'%s' command failed.\n", cmd);
		return -1;
	}
	//memcpy(buf1, buf, sizeof(buf));
	//memcpy(lens, len, sizeof(len));
	//*lens = len;
	 printf("_wpa_ctrl_command33\r\n");
	if (print) {
		buf[len] = '\0';
		printf("%s", buf);
		if (interactive && len > 0 && buf[len - 1] != '\n')
			printf("\n");
	}
	 printf("_wpa_ctrl_command34444\r\n");
	return 0;
}
*/
static int wpa_ctrl_command(struct wpa_ctrl *ctrl, const char *cmd, char *buf, size_t *lens)
{
	return _wpa_ctrl_command(ctrl, buf, lens, cmd, 0);
}

static int wpa_cli_open_connection(struct wpa_ctrl *ctrl, const char *ifname, int attach)
{
	char *cfile = NULL;
	struct wpa_ctrl *ctr = ctrl;
	int flen, res;

	if (ifname == NULL)
		return -1;

	if (cfile == NULL) {
		flen = strlen(ctrl_iface_dir) + os_strlen(ifname) + 2;
		cfile = malloc(flen);
		if (cfile == NULL)
			return -1;
		res = os_snprintf(cfile, flen, "%s/%s", ctrl_iface_dir,
				  ifname);
		if (os_snprintf_error(flen, res)) {
			os_free(cfile);
			return -1;
		}
	}

	ctrl_conn = wpa_ctrl_open2(cfile, NULL);
	if (ctrl_conn == NULL) {
		printf("wpa_cli_open_connection  ctr is NULL!\r\n");
		os_free(cfile);
		return -1;
	}

	os_free(cfile);
	printf("wpa_cli_open_connection  end!\r\n");
	return 0;
}

void wpa_cli_close_connection(struct wpa_ctrl *ctrl)
{
	if (ctrl == NULL)
		return;

	/*
	if (wpa_cli_attached) {
		wpa_ctrl_detach(ctrl);
		wpa_cli_attached = 0;
	}
	*/
	wpa_ctrl_close(ctrl);
	ctrl = NULL;
	/*
	if (mon_conn) {
		eloop_unregister_read_sock(wpa_ctrl_get_fd(mon_conn));
		wpa_ctrl_close(mon_conn);
		mon_conn = NULL;
	}
	*/
}

static void wpa_cli_cleanup(struct wpa_ctrl **ctrl)
{
	wpa_cli_close_connection(ctrl);
	//if (pid_file)
	//	os_daemonize_terminate(pid_file);

	os_program_deinit();
}


int lds_wpa_cmd_scan(struct wpa_ctrl *ctrl, char *buf, size_t *bufsize)
{
    return wpa_ctrl_command(ctrl, "SCAN", buf, bufsize);
}

int lds_hal_wpa_scan(struct wpa_ctrl *ctrl, const char *ifname)
{
    int ret = -1;
    char reply[4096] = {0};
	size_t reply_size ={0};

    if (!ifname)
        return -1;
	
	//*ctrl = (struct wpa_ctrl*)os_malloc(sizeof(struct wpa_ctrl));
	
	 printf("lds_hal_wpa_scan ffname:%s 2\r\n", ifname);
	if (wpa_cli_open_connection(ctrl, ifname, 0) < 0)
    {
		 printf("lds_hal_wpa_scan3\r\n");   
		return -1;
	}
	
	//if(ctrl == NULL)
	//	printf("lds_hal_wpa_scan ctrl is 11111111111 NULL\r\n");   
	
	//printf("lds_hal_wpa_scan4 reply:%s, sizeof(reply):%d\r\n", reply, sizeof(reply));
	
    ret = lds_wpa_cmd_scan(ctrl, reply, &reply_size);
	
	printf("lds_hal_wpa_add_network,reply:%s,sizeof(reply):%d, ret:%d\r\n", reply, sizeof(reply), ret);
    if (os_strncmp(reply, "OK", 2) != 0) 
    {
		 printf("lds_hal_wpa_scan6\r\n");

        ret = -1;
        if (os_strncmp(reply, "FAIL-BUSY", os_strlen("FAIL-BUSY")) == 0) 
        {
            ret = -2;
        }
	}
    printf("lds_hal_wpa_scan7\r\n");

    wpa_cli_cleanup(ctrl);
    
	return ret;
}


int lds_wpa_cmd_scan_result(struct wpa_ctrl *ctrl, char *buf, size_t *bufsize)
{
    return wpa_ctrl_command(ctrl, "SCAN_RESULTS", buf, bufsize);
}

int lds_hal_wpa_scan_result(struct wpa_ctrl *ctrl, const char *ifname, char *reply, size_t *reply_size)
{
    int ret = -1;
   // char reply[4096] = {0};
	//size_t reply_size ={0};

    if (!ifname)
        return -1;
	
	//*ctrl = (struct wpa_ctrl*)os_malloc(sizeof(struct wpa_ctrl));
	
	 printf("lds_hal_wpa_scan_result ffname:%s 2\r\n", ifname);
	if (wpa_cli_open_connection(ctrl, ifname, 0) < 0)
    {
		 printf("lds_hal_wpa_scan_result\r\n");   
		return -1;
	} 
	
	printf("lds_hal_wpa_scan_result reply:%s, sizeof(reply):%d\r\n", reply, sizeof(reply));
	
    ret = lds_wpa_cmd_scan_result(ctrl, reply, reply_size);
	//	 printf("lds_hal_wpa_add_network,reply:%s,sizeof(reply):%d, ret:%d\r\n", reply, sizeof(reply), ret);
	//if()
	// printf("lds_hal_wpa_scan_result,reply:%s,sizeof(reply):%d\r\n", reply, sizeof(reply));
    if (ret == 0) 
    {
		 printf("lds_hal_wpa_scan_result success\r\n");

	}else{
		ret = -1;
		if (os_strncmp(reply, "FAIL-BUSY", os_strlen("FAIL-BUSY")) == 0) 
		{
			ret = -2;
		}
	}
    printf("lds_hal_wpa_scan_result\r\n");

    wpa_cli_cleanup(ctrl);
    
	return ret;
}

int lds_wpa_cmd_add_network(struct wpa_ctrl *ctrl, char *buf, size_t *bufsize)
{
    return wpa_ctrl_command(ctrl, "ADD_NETWORK", buf, bufsize);
}

int lds_hal_wpa_add_network(struct wpa_ctrl *ctrl, const char *ifname, char *networkId)
{
    int ret = 0;
    char reply[4096] = {0};
	size_t reply_size ={0};

    if (!ifname)
        return -1;
	
	//*ctrl = (struct wpa_ctrl*)os_malloc(sizeof(struct wpa_ctrl));
	
	 printf("lds_hal_wpa_add_network ffname:%s 2\r\n", ifname);
	if (wpa_cli_open_connection(ctrl, ifname, 0) < 0)
    {
		 printf("lds_hal_wpa_add_network->wpa_cli_open_connection failed\r\n");   
		return -1;
	}
	
    ret = lds_wpa_cmd_add_network(ctrl, reply, &reply_size);
	
	printf("lds_hal_wpa_add_network,reply:%s,reply_size:%d, ret:%d\r\n", reply, reply_size, ret);
    if (ret == 0) 
    {
		os_strncpy(networkId, reply, reply_size-1);
		printf("lds_hal_wpa_add_network success\r\n");

	}else{
		ret = -1;
		if (os_strncmp(reply, "FAIL-BUSY", os_strlen("FAIL-BUSY")) == 0) 
		{
			ret = -2;
		}
	}
    printf("lds_hal_wpa_add_network7\r\n");

    wpa_cli_cleanup(ctrl);
    
	return ret;
}


int lds_wpa_cmd_set_network(struct wpa_ctrl *ctrl, const char *cmd, char *buf, size_t *bufsize)
{
    return wpa_ctrl_command(ctrl, cmd, buf, bufsize);
}
// wpa_cli_cmd(ctrl, "SET_NETWORK", 3, argc, argv);
int lds_hal_wpa_set_network(struct wpa_ctrl *ctrl, const char *ifname, char *cmd)
{
    int ret = -1;
    char reply[4096] = {0};
	size_t reply_size ={0};

    if (!ifname)
        return -1;
	
	//*ctrl = (struct wpa_ctrl*)os_malloc(sizeof(struct wpa_ctrl));
	
	 printf("lds_hal_wpa_set_network ffname:%s 2\r\n", ifname);
	if (wpa_cli_open_connection(ctrl, ifname, 0) < 0)
    {
		 printf("lds_hal_wpa_set_network->wpa_cli_open_connection failed\r\n");   
		return -1;
	}
	
	
	
    ret = lds_wpa_cmd_set_network(ctrl, cmd, reply, &reply_size);
	
	printf("lds_hal_wpa_set_network,reply:%s,reply_size:%d, ret:%d\r\n", reply, reply_size, ret);

	if (os_strncmp(reply, "OK", 2) != 0) 
    {
		 printf("lds_hal_wpa_set_network failed\r\n");

        ret = -1;
        if (os_strncmp(reply, "FAIL-BUSY", os_strlen("FAIL-BUSY")) == 0) 
        {
            ret = -2;
        }
	}
	
    printf("lds_hal_wpa_set_network\r\n");

    wpa_cli_cleanup(ctrl);
    
	return ret;
}

int lds_wpa_cmd_enable_network(struct wpa_ctrl *ctrl, const char *cmd, char *buf, size_t *bufsize)
{
    return wpa_ctrl_command(ctrl, cmd, buf, bufsize);
}
// wpa_cli_cmd(ctrl, "SET_NETWORK", 3, argc, argv);
int lds_hal_wpa_enable_network(struct wpa_ctrl *ctrl, const char *ifname, char *cmd)
{
    int ret = -1;
    char reply[4096] = {0};
	size_t reply_size ={0};

    if (!ifname)
        return -1;
	
	//*ctrl = (struct wpa_ctrl*)os_malloc(sizeof(struct wpa_ctrl));
	
	 printf("lds_hal_wpa_set_network ffname:%s 2\r\n", ifname);
	if (wpa_cli_open_connection(ctrl, ifname, 0) < 0)
    {
		 printf("lds_hal_wpa_set_network->wpa_cli_open_connection failed\r\n");   
		return -1;
	}
	
	
	
    ret = lds_wpa_cmd_set_network(ctrl, cmd, reply, &reply_size);
	
	printf("lds_hal_wpa_set_network,reply:%s,reply_size:%d, ret:%d\r\n", reply, reply_size, ret);

	if (os_strncmp(reply, "OK", 2) != 0) 
    {
		 printf("lds_hal_wpa_set_network failed\r\n");

        ret = -1;
        if (os_strncmp(reply, "FAIL-BUSY", os_strlen("FAIL-BUSY")) == 0) 
        {
            ret = -2;
        }
	}
	
    printf("lds_hal_wpa_set_network\r\n");

    wpa_cli_cleanup(ctrl);
    
	return ret;
}

// wpa_cli_cmd(ctrl, "SET_NETWORK", 3, argc, argv);
int lds_wpa_cmd_select_network(struct wpa_ctrl *ctrl, const char *cmd, char *buf, size_t *bufsize)
{
    return wpa_ctrl_command(ctrl, cmd, buf, bufsize);
}
// wpa_cli_cmd(ctrl, "SET_NETWORK", 3, argc, argv);
int lds_hal_wpa_select_network(struct wpa_ctrl *ctrl, const char *ifname, char *cmd)
{
    int ret = -1;
    char reply[4096] = {0};
	size_t reply_size ={0};

    if (!ifname)
        return -1;
	
	//*ctrl = (struct wpa_ctrl*)os_malloc(sizeof(struct wpa_ctrl));
	
	 printf("lds_hal_wpa_select_network ffname:%s 2\r\n", ifname);
	if (wpa_cli_open_connection(ctrl, ifname, 0) < 0)
    {
		 printf("lds_hal_wpa_select_network->wpa_cli_open_connection failed\r\n");   
		return -1;
	}
	
	
	
    ret = lds_wpa_cmd_select_network(ctrl, cmd, reply, &reply_size);
	
	printf("lds_hal_wpa_select_network,reply:%s,reply_size:%d, ret:%d\r\n", reply, reply_size, ret);

	if (os_strncmp(reply, "OK", 2) != 0) 
    {
		 printf("lds_hal_wpa_select_network failed\r\n");

        ret = -1;
        if (os_strncmp(reply, "FAIL-BUSY", os_strlen("FAIL-BUSY")) == 0) 
        {
            ret = -2;
        }
	}
	
    printf("lds_hal_wpa_select_network\r\n");

    wpa_cli_cleanup(ctrl);
    
	return ret;
}

int lds_wpa_cli_cmd_save_config(struct wpa_ctrl *ctrl, const char *cmd, char *buf, size_t *bufsize)
{
    return wpa_ctrl_command(ctrl, cmd, buf, bufsize);
}

//cmd:SAVE_CONFIG
int lds_hal_wpa_cli_cmd_save_config(struct wpa_ctrl *ctrl, const char *ifname, char *cmd)
{
//	return wpa_ctrl_command(ctrl, "SAVE_CONFIG");
	int ret = -1;
    char reply[4096] = {0};
	size_t reply_size ={0};

    if (!ifname)
        return -1;
	
	//*ctrl = (struct wpa_ctrl*)os_malloc(sizeof(struct wpa_ctrl));
	
	 printf("lds_wpa_cli_cmd_save_config ffname:%s 2\r\n", ifname);
	if (wpa_cli_open_connection(ctrl, ifname, 0) < 0)
    {
		 printf("lds_wpa_cli_cmd_save_config->wpa_cli_open_connection failed\r\n");   
		return -1;
	}
	
	
	
    ret = lds_wpa_cli_cmd_save_config(ctrl, cmd, reply, &reply_size);
	
	printf("lds_wpa_cli_cmd_save_config,reply:%s,reply_size:%d, ret:%d\r\n", reply, reply_size, ret);

	if (os_strncmp(reply, "OK", 2) != 0) 
    {
		 printf("lds_wpa_cli_cmd_save_config failed\r\n");

        ret = -1;
        if (os_strncmp(reply, "FAIL-BUSY", os_strlen("FAIL-BUSY")) == 0) 
        {
            ret = -2;
        }
	}
	
    printf("lds_wpa_cli_cmd_save_config\r\n");

    wpa_cli_cleanup(ctrl);
    
	return ret;
	
}

int lds_wpa_cli_cmd_reconnect(struct wpa_ctrl *ctrl, const char *cmd, char *buf, size_t *bufsize)
{
    return wpa_ctrl_command(ctrl, cmd, buf, bufsize);
}
//	return wpa_ctrl_command(ctrl, "RECONNECT");
int lds_hal_wpa_cli_cmd_reconnect(struct wpa_ctrl *ctrl, const char *ifname, char *cmd)
{

	int ret = -1;
    char reply[4096] = {0};
	size_t reply_size ={0};

    if (!ifname)
        return -1;
	
	//*ctrl = (struct wpa_ctrl*)os_malloc(sizeof(struct wpa_ctrl));
	
	 printf("lds_wpa_cli_cmd_reconnect ffname:%s 2\r\n", ifname);
	if (wpa_cli_open_connection(ctrl, ifname, 0) < 0)
    {
		 printf("lds_wpa_cli_cmd_reconnect->wpa_cli_open_connection failed\r\n");   
		return -1;
	}
	
	
	
    ret = lds_wpa_cli_cmd_reconnect(ctrl, cmd, reply, &reply_size);
	
	printf("lds_wpa_cli_cmd_reconnect,reply:%s,reply_size:%d, ret:%d\r\n", reply, reply_size, ret);

	if (os_strncmp(reply, "OK", 2) != 0) 
    {
		 printf("lds_wpa_cli_cmd_reconnect failed\r\n");

        ret = -1;
        if (os_strncmp(reply, "FAIL-BUSY", os_strlen("FAIL-BUSY")) == 0) 
        {
            ret = -2;
        }
	}
	
    printf("lds_wpa_cli_cmd_reconnect\r\n");

    wpa_cli_cleanup(ctrl);
    
	return ret;
}

static int lds_wpa_cli_cmd_disconnect(struct wpa_ctrl *ctrl, const char *cmd, char *buf, size_t *bufsize)
{
	return wpa_ctrl_command(ctrl, cmd, buf, bufsize);
}

//	cmd: DISCONNECT
int lds_hal_wpa_cli_cmd_disconnect(struct wpa_ctrl *ctrl, const char *ifname, char *cmd)
{

	int ret = -1;
    char reply[4096] = {0};
	size_t reply_size ={0};

    if (!ifname)
        return -1;
	
	//*ctrl = (struct wpa_ctrl*)os_malloc(sizeof(struct wpa_ctrl));
	
	 printf("lds_wpa_cli_cmd_disconnect ffname:%s 2\r\n", ifname);
	if (wpa_cli_open_connection(ctrl, ifname, 0) < 0)
    {
		 printf("lds_wpa_cli_cmd_disconnect->wpa_cli_open_connection failed\r\n");   
		return -1;
	}
	
	
	
    ret = lds_wpa_cli_cmd_disconnect(ctrl, cmd, reply, &reply_size);
	
	printf("lds_wpa_cli_cmd_disconnect,reply:%s,reply_size:%d, ret:%d\r\n", reply, reply_size, ret);

	if (os_strncmp(reply, "OK", 2) != 0) 
    {
		 printf("lds_wpa_cli_cmd_disconnect failed\r\n");

        ret = -1;
        if (os_strncmp(reply, "FAIL-BUSY", os_strlen("FAIL-BUSY")) == 0) 
        {
            ret = -2;
        }
	}
	
    printf("lds_wpa_cli_cmd_disconnect\r\n");

    wpa_cli_cleanup(ctrl);
    
	return ret;
}


int lds_wpa_cmd_status(struct wpa_ctrl *ctrl, char *buf, size_t *bufsize)
{
    return wpa_ctrl_command(ctrl, "STATUS", buf, bufsize);
}

int lds_hal_wpa_status(struct wpa_ctrl *ctrl, const char *ifname, char *reply, size_t *reply_size)
{
    int ret = -1;
   // char reply[4096] = {0};
	//size_t reply_size ={0};

    if (!ifname)
        return -1;
	
	//*ctrl = (struct wpa_ctrl*)os_malloc(sizeof(struct wpa_ctrl));
	
	 printf("lds_wpa_cmd_status ffname:%s 2\r\n", ifname);
	if (wpa_cli_open_connection(ctrl, ifname, 0) < 0)
    {
		 printf("lds_wpa_cmd_status\r\n");   
		return -1;
	} 
	
	printf("lds_wpa_cmd_status reply:%s, sizeof(reply):%d\r\n", reply, sizeof(reply));
	
    ret = lds_wpa_cmd_status(ctrl, reply, reply_size);
	//	 printf("lds_hal_wpa_add_network,reply:%s,sizeof(reply):%d, ret:%d\r\n", reply, sizeof(reply), ret);
	//if()
	// printf("lds_wpa_cmd_status,reply:%s,sizeof(reply):%d\r\n", reply, sizeof(reply));
    if (ret == 0) 
    {
		 printf("lds_wpa_cmd_status success\r\n");

	}else{
		ret = -1;
		if (os_strncmp(reply, "FAIL-BUSY", os_strlen("FAIL-BUSY")) == 0) 
		{
			ret = -2;
		}
	}
    printf("lds_wpa_cmd_status\r\n");

    wpa_cli_cleanup(ctrl);
    
	return ret;
}


static int get_last_mac(char *mac)
{
	struct ifreq tmp;
	int sock_mac;
	sock_mac = socket(AF_INET, SOCK_STREAM, 0);
	if( sock_mac == -1){
		perror("create socket fail\n");
		return -1;
	}
	memset(&tmp,0,sizeof(tmp));
	strncpy(tmp.ifr_name,"wlan1",sizeof(tmp.ifr_name)-1 );
	
	if( (ioctl( sock_mac, SIOCGIFHWADDR, &tmp)) < 0 ){
		//printf("mac ioctl error\n");
		return -1;
	}
	sprintf(mac, "%02x%02x",
	//(unsigned char)tmp.ifr_hwaddr.sa_data[0],
	//(unsigned char)tmp.ifr_hwaddr.sa_data[1],
	//(unsigned char)tmp.ifr_hwaddr.sa_data[2],
	//(unsigned char)tmp.ifr_hwaddr.sa_data[3],
	(unsigned char)tmp.ifr_hwaddr.sa_data[4],
	(unsigned char)tmp.ifr_hwaddr.sa_data[5]
	);
//	printf("local mac:%s\n", mac_addr);
	close(sock_mac);

	return 0;
}

//start ap mode for wlan1
int lds_wifi_ap_mode(int dev_fd, char *devName)
{
	char json_body[1024];
	char device_mac4[128];
	char source[10];
//	char *g_device_name = g_wifi_param.ap_ssid;
	system("killall wpa_supplicant");
	sleep(1);
	
	memset(json_body, 0, 1024);
	memset(device_mac4, 0, 128);
	memset(source, 0, 10);
	
	get_last_mac(device_mac4);

#ifndef _NEW_WIFI_SETUP_	
	if(strlen(g_wifi_param.ap_pwd)>0)
		sprintf(json_body,"wifi_setup.sh ap nl80211 %s%s %s %s", g_wifi_param.ap_ssid, device_mac4, g_wifi_param.ap_pwd, g_wifi_param.ap_encrypt_type);
	else
		sprintf(json_body,"wifi_setup.sh ap nl80211 %s%s 0  open", g_wifi_param.ap_ssid, device_mac4);
#else
	if(strlen(g_wifi_param.ap_pwd)>0)
		sprintf(json_body,"/usr/lds/script/lds_wifi_setup.sh ap nl80211 %s %s%s %s %s", devName, g_wifi_param.ap_ssid, device_mac4, g_wifi_param.ap_pwd, g_wifi_param.ap_encrypt_type);
	else
		sprintf(json_body,"/usr/lds/script/lds_wifi_setup.sh ap nl80211 %s %s%s 0  open", devName, g_wifi_param.ap_ssid, device_mac4);
	
#endif // #ifndef _NEW_WIFI_SETUP_	end
	
	if(g_wifi_param.ap_channel!=0)
	{
		sprintf(source," %d", g_wifi_param.ap_channel);
		strcat(json_body, source);
	}
	
	system(json_body);   //setup wifi ap
	
	if(g_wifi_param.wifi_mode != LDS_CTRL_WIFI_APSTA_MODE)
		g_wifi_param.wifi_mode = LDS_CTRL_WIFI_AP_MODE;
	
	return 0;
}

void lds_wifi_ap_stop(int fddev)
{
	char port[128]={0};
	//printf("******** amba_stop_wifi_ap wlan1 down************");
	sprintf(port, "ifconfig %s down", g_wifi_param.ap_port);
	printf("******** %s************\r\n", port);

	system(port);
	
	if(g_wifi_param.wifi_mode == LDS_CTRL_WIFI_AP_MODE)
		g_wifi_param.wifi_mode = -1;
	else if(g_wifi_param.wifi_mode == LDS_CTRL_WIFI_APSTA_MODE)
		g_wifi_param.wifi_mode = LDS_CTRL_WIFI_STA_MODE;


	return 0;
}

int lds_wifi_sta_mode(int dev_fd, char* pdevName)
{
	int ret = -1;
	char networkID[10]={0};
	char cmd[1024];
	//char *buf = "wlan0";
	char reply[1024] = {0};
	size_t *reply_size = 0;
	int check_count = 0;
	
	memset(cmd, 0, 1024);
	
	//if(ret == 0)
	sprintf(cmd,"SET_NETWORK %s ssid \"%s\"", networkID, g_wifi_param.sta_ssid);
	ret = lds_hal_wpa_set_network(ctrl_conn, g_wifi_param.sta_port, cmd);
	if(ret != 0)
	{
		printf("lds_wifi_sta_mode set ssid failed!\r\n");
	}
	
	memset(cmd, 0, 1024);
	if(g_wifi_param.sta_encrypt_type!=LDS_WIFI_ENCRYPT_TYPE_WEP)
	{
		//memset(cmd, 0, 1024);
		sprintf(cmd,"SET_NETWORK %s psk \"%s\"", networkID, g_wifi_param.sta_pwd);
		ret = lds_hal_wpa_set_network(ctrl_conn, g_wifi_param.sta_port, cmd);
	}else{
		sprintf(cmd,"SET_NETWORK %s key_mgmt \"%s\"", networkID, g_wifi_param.sta_pwd);
		ret = lds_hal_wpa_set_network(ctrl_conn, g_wifi_param.sta_port, cmd);
	}
	

	if(!ret)
	{
		memset(cmd, 0, 1024);
		sprintf(cmd,"ENABLE_NETWORK %s", networkID);
		ret = lds_hal_wpa_enable_network(ctrl_conn, g_wifi_param.sta_port, cmd);
	}
	
	if(!ret)
	{
		memset(cmd, 0, 1024);
		sprintf(cmd,"SELECT_NETWORK %s", networkID);
		ret = lds_hal_wpa_select_network(ctrl_conn, g_wifi_param.sta_port, cmd);
	}
	
	if(ret == 0)
		system("udhcpc -b -i wlan0 -q");
	sleep(1);
		
	ret = lds_hal_wpa_status(ctrl_conn, g_wifi_param.sta_port, reply, reply_size);
	while((ret != 0)||(strstr(reply, "wpa_state=COMPLETED") == NULL)||check_count < 10)
	{
		memset(reply, 0, 1024);
		*reply_size = 0;
		ret = lds_hal_wpa_status(ctrl_conn, g_wifi_param.sta_port, reply, reply_size);
		
		if(strstr(reply, "wpa_state=4WAY_HANDSHAKE") != NULL)
			return 2; //secret error
		
		check_count ++;
		sleep(2);
	}
	
	/*
	if((g_wifi_param.wifi_mode == LDS_CTRL_WIFI_AP_MODE)
		g_wifi_param.wifi_mode = LDS_CTRL_WIFI_STA_MODE;
	else
	*/	
	if(g_wifi_param.wifi_mode != LDS_CTRL_WIFI_APSTA_MODE)
		g_wifi_param.wifi_mode = LDS_CTRL_WIFI_STA_MODE;
	
	startWifiThread();  //start wifi sta mode status
	
	return ret;	
}

int lds_wifi_sta_stop(int fddev)
{
	int ret = -1;
	//if((wifi_param.wifi_mode == LDS_CTRL_WIFI_STA_MODE)||(wifi_param.wifi_mode == LDS_CTRL_WIFI_APSTA_MODE))
		/*
	switch(fddev)
	{
		case 0:
			ret = lds_hal_wpa_cli_cmd_disconnect(ctrl_conn, g_wifi_param.sta_port, "DISCONNECT")
			//system("ifconfig wlan0 down");
		break;
	
		case 1:
			ret = lds_hal_wpa_cli_cmd_disconnect(ctrl_conn, g_wifi_param.sta_port, "DISCONNECT")
			//system("ifconfig wlan1 down");
		break;
		
		case 2:
			ret = lds_hal_wpa_cli_cmd_disconnect(ctrl_conn, g_wifi_param.sta_port, "DISCONNECT")
			//system("ifconfig wlan2 down");
		break;
		
		default:
			printf("******** lds_wifi_sta_stop default************");
		break;
	
	}
	*/
	
	ret = lds_hal_wpa_cli_cmd_disconnect(ctrl_conn, g_wifi_param.sta_port, "DISCONNECT");
	if(g_wifi_param.wifi_mode == LDS_CTRL_WIFI_STA_MODE)
		g_wifi_param.wifi_mode = -1;
	else if(g_wifi_param.wifi_mode == LDS_CTRL_WIFI_APSTA_MODE)
		g_wifi_param.wifi_mode = LDS_CTRL_WIFI_AP_MODE;

	return ret;
}

int lds_get_wifi_status(void)
{
	int ret = -1;
	//char *buf = "wlan0";
	char reply[1024] = {0};
	size_t *reply_size = 0;
	
	ret = lds_hal_wpa_status(ctrl_conn, g_wifi_param.sta_port, reply, reply_size);
	if(ret == 0)
	{
		if(strstr(reply, "wpa_state=COMPLETED") != NULL)
		{
			return ret;
		}else if(strstr(reply, "wpa_state=4WAY_HANDSHAKE") != NULL){
			return 2;
		}
		else if(strstr(reply, "wpa_state=DISCONNECTED") != NULL)
			return 1;
	}else{
		return ret;
	}
	
	return ret;
}

int str_enctype_trans(char *penctype)
{
	char buffer[256];
	char *encry = penctype;
	int encry_type = -1;
	if(encry == NULL)
		return -1;
	int lens = strlen(encry);
	
	char *pstr_begin = NULL;
	char *pstr_end   = NULL;
	
	pstr_begin = strstr(encry, "[");
	pstr_end   = strstr(pstr_begin, "]");
	if((pstr_begin == NULL)||(pstr_end == NULL))
		return -1;
	int i = 0;
	while((pstr_begin != NULL)&&(pstr_end != NULL)&&(encry_type == -1))
	{
		memset(buffer, 0, 256);
		memcpy(buffer, pstr_begin+1, pstr_end-pstr_begin-1);
		if ((pstr_end - pstr_begin + 2) > 0)
		{
			if ((strcmp(buffer, "WPA2-SAE-CCMP") == 0) || (strcmp(buffer, "WPA2-SAE-CCMP") == 0) || (strcmp(buffer, "WPA2_AES") == 0))
				encry_type = 6;
			else if ((strcmp(buffer, "WPA2-PSK-CCMP") == 0) || (strcmp(buffer, "WPA2_PSK_AES") == 0))
				encry_type = 10;
			else if ((strcmp(buffer, "WPA2-PSK-CCMP+TKIP") == 0) || (strcmp(buffer, "WPA2_PSK_TKIP") == 0))
				encry_type = 9;
			else if ((strcmp(buffer, "WPA_TKIP") == 0) || (strcmp(buffer, "WPA-PSK-CCMP+TKIP") == 0))
				encry_type = 3;
			else if ((strcmp(buffer, "WPA_AES") == 0) || (strcmp(buffer, "WPA-PSK-CCMP") == 0) || (strcmp(buffer, "WPA_PSK_AES") == 0))
				encry_type = 4;
			else if ((strcmp(buffer, "WPA-PSK-CCMP+TKIP") == 0) || (strcmp(buffer, "WPA_PSK_TKIP") == 0))
				encry_type = 7;
			else if ((strcmp(buffer, "WEP") == 0))
				encry_type = 2;
			else if ((strcmp(buffer, "WPA3") == 0))
				encry_type = 12;
			else if ((strcmp(buffer, "WPA2_TKIP") == 0))
				encry_type = 5;
			else if ((strcmp(buffer, "WPA_WPA2_WPA3") == 0))
				encry_type = 13;
			else if ((strcmp(buffer, "W802_1X") == 0))
				encry_type = 14;
			else if ((strcmp(buffer, "ESS") == 0))
				encry_type = 1;
		}
		
	//	printf("get_wifi_encrypt->i:%d, encry_type:%d\r\n", i, encry_type);
	//	printf("pstr_begin:%s\r\n", pstr_begin);
	//	printf("buffer:%s\r\n", buffer);
		i++;
		pstr_begin = strstr(pstr_end, "[");
		if(pstr_begin == NULL)
			break;
		pstr_end   = strstr(pstr_begin, "]");
		
	}
	return encry_type;
}

/*
* 1, transform Chinese UTF8 "\xe5\x88\x98" to "e58898"
* 2, transform "\\", "\"" to "\", """
*/
static void Chinese_UTF8_format_and_extra_escape_conversion(char *strbuf)
{
	char buf[512]={0};
	char *ptmp=NULL, *pmalloc=NULL;
	int i=0, j=0, k=0, len=0;
	
	if(strbuf==NULL || (len=strlen(strbuf))<=1)
		return;

	if(len >= sizeof(buf))
	{
		pmalloc=calloc(len+1, 1);
		if(pmalloc==NULL)
			return;
		ptmp=pmalloc;
	}
	else
		ptmp=buf;

	for(i=0; i<len; i++)
	{
		if(strbuf[i]=='\\')
		{
			if(i<len-1)
			{
				if(strbuf[i+1] == 'x')	//Chinese_UTF8_format transform
				{
					if(i<len-3)
					{
						char tmpbuf[2]={0};
						tmpbuf[0]=strbuf[i+2];
						tmpbuf[1]=strbuf[i+3];
						for(k=0; k<2; k++)
						{
							if(tmpbuf[k]<='9' && tmpbuf[k]>='0')
								tmpbuf[k]-='0';
							else if(tmpbuf[k]<='z' && tmpbuf[k]>='a')
								tmpbuf[k]=tmpbuf[k]-'a'+10;
							else if(tmpbuf[k]<='Z' && tmpbuf[k]>='A')
								tmpbuf[k]=tmpbuf[k]-'A'+10;
						}
						ptmp[j++]=tmpbuf[0]*16+tmpbuf[1];
						//printf("[%s:%d] data:%d,tmpbuf%d%d,source:%c%c\n",__func__, __LINE__, ptmp[j],tmpbuf[0],tmpbuf[1],strbuf[i+2],strbuf[i+3]);
						i=i+3; //escape '\xe5'	
					}
				}
				else	//extra_escape transform
				{
					ptmp[j++]=strbuf[i+1];
					i++; //escape next char	
				}
			}
		}
		else
		{
			ptmp[j++]=strbuf[i];
		}
	}
	//printf("%s source:%d,%s target:%d,%s\n",__func__, len, strbuf, j, buf);
	if(j!=len)
	{
		strncpy(strbuf, ptmp, j+1);
	}
	if(pmalloc)
		free(pmalloc);
}

int lds_wpa_wifi_list(WIFI_LIST *wifi_list)
{
	int ret = -1;
	char reply[4096]={0};
	size_t reply_size = 0;
	
	FILE *fp=NULL;
	char buf[256]={0};
	char bufdir[256];
	char ebuf[256];
	char ssidbuf[256];
	char signalbuf[256];	
	char ecybuf[256];

	char *pstr_begin = NULL;
	char *pstr_end   = NULL;
	char *sstr_begin = NULL;
	char *sstr_end = NULL;
	
	char *estr_begin = NULL;
	char *estr_end = NULL;
	int encrypt_type = -1;
	int i =0;
	
	
	lds_hal_wpa_scan(ctrl_conn, g_wifi_param.sta_port);
	usleep(100);
	ret = lds_hal_wpa_scan(ctrl_conn, g_wifi_param.sta_port);
	usleep(100);
	ret = lds_hal_wpa_scan_result(ctrl_conn, g_wifi_param.sta_port, reply, &reply_size);
	if(reply_size != 0)
	{
		fp = fopen("/tmp/scanlist", "w");
		if(fp == NULL)
		{
			printf("lds_wpa_wifi_list->cannot open the wifi list file\r\n");
			return -1;
		}
		for(i=0; fscanf(fp, "%c", reply+i)!=EOF; i++)
			;
		fclose(fp);
	}
	system("cat /tmp/scanlist | awk '{print \"ssid:\"$5 \";rssi:\"$3\";enctype:\"$4\";\"}' > /tmp/wifilist.txt");
	sync();
	
	i = 0;
	while(!feof(fp))
	{
		memset(buf, 0, 256);
		fgets(buf, sizeof(buf), fp);
		 
		memset(bufdir, 0, 256);
		memset(ebuf, 0, 256);
		strncpy(bufdir, buf, strlen(buf));
		strncpy(ebuf, buf, strlen(buf));

		pstr_begin = strstr(buf, "ssid:");
		sstr_begin = strstr(bufdir, "rssi:");
		estr_begin = strstr(ebuf, "enctype:");
		
		//check the str is error
		if((pstr_begin == NULL)||(sstr_begin == NULL)||(estr_begin == NULL))
			goto retry;
		
		pstr_end   = strstr(pstr_begin, ";");
		sstr_end   = strstr(sstr_begin, ";");
		estr_end   = strstr(estr_begin, ";");
		
		if((pstr_end == NULL)||(sstr_end == NULL)||(estr_end == NULL))
			goto retry;
		
		//check the value is empty
		if(((pstr_end-pstr_begin-5) <= 0)||((sstr_end-sstr_begin-5) <= 0)||((estr_end-estr_begin-8-1) <= 0)||(NULL != strstr(buf, "/")))
		{
			printf("error!\r\n");
			goto retry;
		}
		memset(ssidbuf, 0, 256);
		memset(signalbuf, 0, 256);
		memset(ecybuf, 0, 256);
		
		/*
		printf("wifi list i=%d\r\n");
		if(i != 0)
		{
			strcat(wifi_list, ",");
		}*/
		
		memcpy(ssidbuf, pstr_begin+5, pstr_end-pstr_begin-5);
		Chinese_UTF8_format_and_extra_escape_conversion(ssidbuf);
		memcpy((wifi_list+i)->ssid, ssidbuf, strlen(ssidbuf));


		memcpy(signalbuf, sstr_begin+5, sstr_end-sstr_begin-5);
		memcpy((wifi_list+i)->signal_dbm, signalbuf, strlen(signalbuf));

		
		memcpy(ecybuf, estr_begin+8, estr_end-estr_begin-8);
		encrypt_type = str_enctype_trans(ecybuf);
		if(encrypt_type == -1)
			encrypt_type = 0;
		(wifi_list+i)->encrypt_type = encrypt_type;
		

		i++;		
retry:
		if(i>=50)
			break;
	}
	
	return i;
}

void *wifi_sta_work_thread(void)
{
	int status = -1;
	while(g_wifi_param.sta_thread_running_flag)
	{
		status = lds_get_wifi_status();
		if(status != 0){
			printf("wifi_sta_work_thread sta mode status:%d \r\n", status);
			lds_wifi_sta_mode(0, "wlan0");
			sleep(10);
		}
		sleep(20);
	}
	
}

void startWifiThread(void)
{
	if (g_threadFirst == 1) { //the first time
		g_threadFirst = 0;
		printf("start_wifi_thread pthread_create...");
		pthread_create(&g_wifi_param.sta_check_threadID, NULL, &wifi_sta_work_thread, NULL);
		printf("start_wifi_thread pthread_create finish %d.", g_wifi_param.sta_check_threadID);
	}
	
}

void StopWifiThread(void) 
{ 

	//m_exitEvent = true;
	if (g_threadFirst == 0)
	{
		g_wifi_param.sta_thread_running_flag = 0;
		void *pe = NULL;
		if (pthread_cancel(g_wifi_param.sta_check_threadID))
		{
			printf("Failed to cancel wifi_sta_work_thread");
		}

		printf("Joining wifi_sta_work_thread...");

		if (pthread_join(g_wifi_param.sta_check_threadID, &pe))
		{

			printf("Failed to join the wifi_sta_work_thread");
		}

		if (pe == PTHREAD_CANCELED)
		{
			printf("wifi_sta_work_thread is really Canceled");
		}

		g_threadFirst = 1;
	}

}

int lds_hal_init(void *param)
{

	//char *buf = "wlan0";
//	char networkID[10]={0};
	char wpa_cmd[1024] = {0};
//	int ret = -1;
	WIFI_PARAM *pWifiParam = (WIFI_PARAM*)param;
	printf("this is test wpa\r\n");
	
	//g_wifi_param
	//memcpy(g_wifi_param, (WIFI_PARAM*)param, sizeof(WIFI_PARAM));
	memset(&g_wifi_param, 0, sizeof(WIFI_PARAM));
	
	g_wifi_param.wifi_mode            = pWifiParam->wifi_mode;
	g_wifi_param.wifi_status          = pWifiParam->wifi_status;
	g_wifi_param.ap_encrypt_type      = pWifiParam->ap_encrypt_type;
	g_wifi_param.sta_encrypt_type     = pWifiParam->sta_encrypt_type;
	g_wifi_param.sta_thread_running_flag = 0;  //the flag of the sta running
	
	g_threadFirst = 1;    //the first will start sta thread status
	
	memcpy(g_wifi_param.ap_ssid, pWifiParam->ap_ssid, sizeof(pWifiParam->ap_ssid));
	memcpy(g_wifi_param.ap_pwd, pWifiParam->ap_pwd, sizeof(pWifiParam->ap_pwd));
	memcpy(g_wifi_param.sta_ssid, pWifiParam->sta_ssid, sizeof(pWifiParam->sta_ssid));
	memcpy(g_wifi_param.sta_pwd, pWifiParam->sta_pwd, sizeof(pWifiParam->sta_pwd));
	memcpy(g_wifi_param.ap_port, pWifiParam->ap_port, sizeof(pWifiParam->ap_port));
	memcpy(g_wifi_param.sta_port, pWifiParam->sta_port, sizeof(pWifiParam->sta_port));
	
	memset(wpa_cmd, 0, 1024);
	
	sprintf(wpa_cmd, "wpa_supplicant -Dnl80211 -i%s -c /etc/wpa_supplicant/wpa_supplicant.conf -B", g_wifi_param.sta_port);
	system(wpa_cmd);
	
//	pthread_create(&g_wifi_param.sta_check_threadID, NULL, &wifi_sta_work_thread, NULL);

/*
	
	g_lds_hal_wifi_mode               = -1;
	g_lds_hal_wifi_encrypt_mode       = -1;
	g_lds_hal_wifi_channel_numb       = 0;
	g_lds_hal_wifi_start_or_stop      = -1;
	
	memset(g_lds_hal_wifi_ssid, 0, 256);
	memset(g_lds_hal_wifi_pwd, 0, 256);
	memset(g_device_name, 0, 256);
*/

	//enter the wifi mode check;
	/*
	switch(g_wifi_param.wifi_mode)
	{
		case LDS_CTRL_WIFI_AP_MODE:
			lds_wifi_ap_mode();
		break;
		
		case LDS_CTRL_WIFI_STA_MODE:
			lds_wifi_sta_mode();
		break;
		
		case LDS_CTRL_WIFI_APSTA_MODE:
			lds_wifi_sta_ap_mode();
		break;
		
		case LDS_CTRL_WIFI_WPS_MODE:
			printf("lds_hal_init-> no support LDS_CTRL_WIFI_WPS_MODE wifi mode\r\n");
		break;
		
		default:
			printf("lds_hal_init-> no support wifi mode\r\n");
		break;
	}
	*/
	/*
	lds_hal_wpa_scan(ctrl_conn, buf);
	usleep(100);
	char reply[4096]={0};
	size_t reply_size = 0;
	ret = lds_hal_wpa_scan_result(ctrl_conn, buf, reply, &reply_size);
	if(ret == 0)
	{
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
		printf("****************************************************\r\n");
		printf("%s",reply);
		printf("****************************************************\r\n");
		printf("the reply_size:%d\r\n", reply_size);
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
		char *str_find = NULL;
		char *str_end = NULL;
		char line_des[1024]={0};
		char ssidbuf[256] = {0};
		char desssid[256] = {0};
		
		char *pstr_begin = NULL;
		char *pstr_end = NULL;
		
		str_find = strtok_r(reply, "\n", &str_end);
		
	}
	
	sleep(1);
	ret = lds_hal_wpa_add_network(ctrl_conn, buf, networkID);
	printf("networkID:%s,\r\n", networkID);
	
	char *ssid = "tengx";
	char *secret = "tx19930323";
	if(ret == 0)
	{
		sprintf(cmd,"SET_NETWORK %s ssid \"%s\"", networkID, ssid);
		ret = lds_hal_wpa_set_network(ctrl_conn, buf, cmd);
		memset(cmd, 0, 1024);
		sprintf(cmd,"SET_NETWORK %s psk \"%s\"", networkID, secret);
		ret = lds_hal_wpa_set_network(ctrl_conn, buf, cmd);
		memset(cmd, 0, 1024);
	}
	if(!ret)
	{
		sprintf(cmd,"ENABLE_NETWORK %s", networkID);
		ret = lds_hal_wpa_enable_network(ctrl_conn, buf, cmd);
	}
	
	if(!ret)
	{
		sprintf(cmd,"SELECT_NETWORK %s", networkID);
		ret = lds_hal_wpa_select_network(ctrl_conn, buf, cmd);
	}
	if(ret == 0)
		system("udhcpc -b -i wlan0 -q");
	*/
	
/*	if(status>=0)
	{
		printf("this is test status1111:%d\r\n", status);
		wpa_cli_close_connection();
	}
	*/
	
	printf(" lds_hal_init end \r\n");
	return 0;
}


#if 0
int main(int argc, char *argv[])
{
	//struct wpa_ctrl *ctrl=NULL;
	char *buf = "wlan0";
	char networkID[10]={0};
	char cmd[1024] = {0};
	int ret = -1;
	printf("this is test wpa\r\n");

	lds_hal_wpa_scan(ctrl_conn, buf);
	usleep(100);
	char reply[4096]={0};
	size_t reply_size = 0;
	ret = lds_hal_wpa_scan_result(ctrl_conn, buf, reply, &reply_size);
	if(ret == 0)
	{
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
		printf("****************************************************\r\n");
		printf("%s",reply);
		printf("****************************************************\r\n");
		printf("the reply_size:%d\r\n", reply_size);
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
		printf("\r\n");
		char *str_find = NULL;
		char *str_end = NULL;
		char line_des[1024]={0};
		char ssidbuf[256] = {0};
		char desssid[256] = {0};
		
		char *pstr_begin = NULL;
		char *pstr_end = NULL;
		
		str_find = strtok_r(reply, "\n", &str_end);
		
#if 0 //
		
		while(str_find != NULL){
			sprintf(line_des, "line:%s;\r\n", str_find);
			pstr_begin = strstr(line_des, "[");
			printf("line_des:%s;\r\n", line_des);
			if(pstr_begin!=NULL)
			{
				pstr_end   = strstr(pstr_begin, "[ESS]");//[ESS]
				if(pstr_end != NULL)
				{
					if((pstr_end - pstr_begin) > 0)
					{
						memset(ssidbuf, 0, 256);
						memcpy(ssidbuf, pstr_begin+1, pstr_end-pstr_begin-1);
						printf("ssidbuf:%s;\r\n", ssidbuf);
						pstr_begin = NULL;
						pstr_end = NULL;
						pstr_begin = strstr(ssidbuf, "[");
						if((pstr_begin==NULL)&&(strlen(ssidbuf)>0))
						{
							pstr_end = strstr(ssidbuf, "]");
							if(pstr_end != NULL)
							{
								memset(desssid, 0, 256);
								memcpy(desssid, ssidbuf, pstr_end-ssidbuf);
								printf("desssid:%s;\r\n", desssid);
							}
							
						}else{
							pstr_end = strstr(pstr_begin, "]");
							if(pstr_end != NULL)
							{
								memset(desssid, 0, 256);
								memcpy(desssid, pstr_begin+1, pstr_end-pstr_begin-1);
								printf("desssid2:%s;\r\n", desssid);
							}
							
						}
					}else{
						
						printf("secret is OPEN\r\n");
						
					}
					
					
				}
			}
				
			str_find = strtok_r(NULL, "\n", &str_end);
		}
#endif
		
	}
	
	sleep(1);
	ret = lds_hal_wpa_add_network(ctrl_conn, buf, networkID);
	printf("networkID:%s,\r\n", networkID);
	
	char *ssid = "tengx";
	char *secret = "tx19930323";
	if(ret == 0)
	{
		sprintf(cmd,"SET_NETWORK %s ssid \"%s\"", networkID, ssid);
		ret = lds_hal_wpa_set_network(ctrl_conn, buf, cmd);
		memset(cmd, 0, 1024);
		sprintf(cmd,"SET_NETWORK %s psk \"%s\"", networkID, secret);
		ret = lds_hal_wpa_set_network(ctrl_conn, buf, cmd);
		memset(cmd, 0, 1024);
	}
	if(!ret)
	{
		sprintf(cmd,"ENABLE_NETWORK %s", networkID);
		ret = lds_hal_wpa_enable_network(ctrl_conn, buf, cmd);
	}
	
	if(!ret)
	{
		sprintf(cmd,"SELECT_NETWORK %s", networkID);
		ret = lds_hal_wpa_select_network(ctrl_conn, buf, cmd);
	}
	if(ret == 0)
		system("udhcpc -b -i wlan0 -q");
	

	
	
/*	if(status>=0)
	{
		printf("this is test status1111:%d\r\n", status);
		wpa_cli_close_connection();
	}
	*/
	
	printf("end \r\n");
	return 0;
}
#endif