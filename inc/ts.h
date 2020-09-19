#ifndef __TS_H
#define __TS_H

#include <stdio.h>
//open函数
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//close、read、write函数
#include <unistd.h>
//ts的头文件
#include <linux/input.h>

int open_ts(void); 					 //1、打开触摸屏文件
int get_ts_xy(int *ts_x, int *ts_y); //2、获取触摸屏数据x和y的坐标
int close_ts(void); 				 //3、关闭触摸屏文件

#endif