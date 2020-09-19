#ifndef __BEEP_LED_H
#define __BEEP_LED_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/ioctl.h>
#include <stdlib.h>

//定义应用程序与驱动程序的规约
#define GZ1901_BEEP_ON _IO('B',1)
#define GZ1901_BEEP_OFF _IO('B',2)

#define GZ1901_LED_ON _IOW('L',1,unsigned int)
#define GZ1901_LED_OFF _IOW('L',2,unsigned int) 



int beep_led_insert(); 		//1、删除原有的led和beep驱动，重新插入自己的
int open_beep_led();  		//2、初始化beep、led驱动

int beep_on();         		//3、蜂鸣器响
int beep_off();       		//4、蜂鸣器不响

int led_on();          		//5、全灯亮
int led_off();         		//6、全灯灭

int close_beep_led(void); 	//7、关闭beep和led的驱动文件

#endif