#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "pelco_d.h"
#include "uart.h"

#define CAM_ADDR    1

void help(char *proc)
{
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "# %s [dir] [speed]\n", proc);
    fprintf(stderr, "\tdir:\tup/down/left/right/stop\n");
    fprintf(stderr, "\tspeed:\tlow/mid/high\n");
    fprintf(stderr, "\tIf the \"dir\" is stop, the \"speed\" can be ignored.\n");
    fprintf(stderr, "eg:\n");
    fprintf(stderr, "# %s left low\n", proc);
}

int main(int argc, char **argv)
{
    int fd, ret, is_stop = 0;
    struct pelco_d *dir_cmd, *speed_cmd;

    if (argc < 2) {
        help(argv[0]);
        return -1;
    } else {
        if (strncmp(argv[1], "stop", 4) != 0) {
            if (argc < 3) {
                help(argv[0]);
                return -1;
            }
        }
    }

    if (strncmp(argv[1], "up", 2) == 0) {
        dir_cmd = protocol_up(CAM_ADDR, 0xff);
    } else if (strncmp(argv[1], "down", 4) == 0) {
        dir_cmd = protocol_down(CAM_ADDR, 0xff);
    } else if (strncmp(argv[1], "left", 4) == 0) {
        dir_cmd = protocol_left(CAM_ADDR, 0xff);
    } else if (strncmp(argv[1], "right", 5) == 0) {
        dir_cmd = protocol_right(CAM_ADDR, 0xff);
    } else if (strncmp(argv[1], "stop", 4) == 0) {
        dir_cmd = protocol_stop(CAM_ADDR);
        is_stop = 1;
    } else {
        help(argv[0]);
        return -1;
    }

    if (!is_stop) {
        if (strncmp(argv[2], "low", 3) == 0) {
            speed_cmd = set_low_speed(CAM_ADDR);
        } else if (strncmp(argv[2], "mid", 3) == 0) {
            speed_cmd = set_mid_speed(CAM_ADDR);
        } else if (strncmp(argv[2], "high", 4) == 0) {
            speed_cmd = set_high_speed(CAM_ADDR);
        } else {
            help(argv[0]);
            return -1;
        }
    }

    fd = init_uart("/dev/ttyUSB0", 9600);
    if (fd < 0) {
        goto err_init;
    }

    if (!is_stop) {
        ret = write(fd, (const void *) speed_cmd, PELCO_D_LEN);
        if (ret <= 0) {
            perror("Send data to uart");
            goto err_send;
        }
    }

    ret = write(fd, (const void *)dir_cmd, PELCO_D_LEN);
    if (ret <= 0) {
        perror("Send data to uart");
        goto err_send;
    }

err_send:
    close(fd);
err_init:
    free_pack(speed_cmd);
    free_pack(dir_cmd);

    return ret;
}