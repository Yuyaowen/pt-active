TARGET		:= pt-active
OBJS		:= main.o uart.o pelco_d.o
###############################################
#CROSS_COMPILE	:= mips-openwrt-linux-
CC		:= $(CROSS_COMPILE)gcc
CFLAGS		:= -Wall
###############################################
#export STAGING_DIR=/home/yt/work/chaos_calmer-chaos_calmer/staging_dir

all:$(TARGET)
	@file $^

$(TARGET):$(OBJS)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	@rm $(TARGET) $(OBJS)
