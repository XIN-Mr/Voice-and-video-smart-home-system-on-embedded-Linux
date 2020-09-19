#ifndef __BMP_H
#define __BMP_H

#include <stdio.h>
//open函数
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//close、read、write函数
#include <unistd.h>
//strlen函数
#include <string.h>
//mmap函数
#include <sys/mman.h>

int open_bmp_lcd(void);	    //1、打开lcd屏幕文件，并映射空间到lcd屏幕文件
int show_bmp_ReadWrite(const char *bmp_path, int lcd_location_x, 
                       int lcd_location_y, int bmp_x, int bmp_y);
						    //2、显示bmp图片，相当于read和write的操作
int close_bmp_lcd(void);    //3、关闭lcd屏幕文件，关闭映射空间


#endif