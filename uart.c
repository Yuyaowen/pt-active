#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

/* 8n1 */
int init_uart(char *device, int baud)
{
    int fd, ret;
    struct  termios uart_args;
    speed_t baudrate;

    fd = open(device, O_RDWR);
    if (fd < 0) {
        perror("Open UART Port");
        ret = fd;
        goto err_open;
    }

    ret = tcgetattr(fd, &uart_args);
    if (ret < 0) {
        perror("Get UART Attribute");
        goto err_getattr;
    }

    switch (baud) {
        case 50 : baudrate = B50; break;
        case 75 : baudrate = B75; break;
        case 110 : baudrate = B110; break;
        case 134 : baudrate = B134; break;
        case 150 : baudrate = B150; break;
        case 200 : baudrate = B200; break;
        case 300 : baudrate = B300; break;
        case 600 : baudrate = B600; break;
        case 1200 : baudrate = B1200; break;
        case 1800 : baudrate = B1800; break;
        case 2400 : baudrate = B2400; break;
        case 4800 : baudrate = B4800; break;
        case 9600 : baudrate = B9600; break;
        case 19200 : baudrate = B19200; break;
        case 38400 : baudrate = B38400; break;
        case 57600 : baudrate = B57600; break;
        case 115200 : baudrate = B115200; break;
        case 230400 : baudrate = B230400; break;
        default: ret = -1; fprintf(stderr, "Invalid Baudrate.\n"); goto err_inv;
    }

    ret = cfsetispeed(&uart_args, baudrate);
    if (ret < 0) {
        perror("Set ispeed");
        goto err_setispeed;
    }
    ret = cfsetospeed(&uart_args, baudrate);
    if (ret < 0) {
        perror("Set ospeed");
        goto err_setospeed;
    }

    uart_args.c_cflag |= CS8;
    uart_args.c_cflag &= ~PARENB;
    uart_args.c_cflag &= ~CSTOPB;
    uart_args.c_cflag &= ~CSTOPB;
    uart_args.c_iflag |= INPCK;
    uart_args.c_cc[VTIME] = 150;
    uart_args.c_cc[VMIN] = 0;

    ret = tcsetattr(fd, TCSANOW, &uart_args);
    if (ret < 0) {
        perror("Set UART Attribute");
        goto err_setattr;
    }

    return fd;

err_setattr:
err_setospeed:
err_setispeed:
err_inv:
err_getattr:
    close(fd);
err_open:
    return ret;
}
