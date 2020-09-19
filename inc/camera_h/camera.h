#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <stdio.h>   	
#include <fcntl.h>			 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <strings.h>
#include <linux/input.h>
#include <pthread.h> //多线程头文件

#include "jpeglib.h"

#define LCD_WIDTH  			800
#define LCD_HEIGHT 			480
#define FB_SIZE				(LCD_WIDTH * LCD_HEIGHT * 4)	//帧缓存区大小

extern int camera_flag;

typedef struct VideoBuffer
{
    void   *start;  //映射到用户空间的地址
    size_t  length; //采集到数据的长度
} VideoBuffer1; 	//存放采集数据的位置

#define BUFFER_COUNT 4
VideoBuffer1 framebuf[BUFFER_COUNT]; 

struct jpg_data
{
	unsigned char jpg_data[614400];   //用于存放摄像头数据
	int jpg_size; 					  //用于存放摄像头数据大小
};

//函数声明
unsigned long file_size_get(const char *pfile_path); //获取文件大小
int lcd_draw_jpg(unsigned int x,unsigned int y,const char *pjpg_path);  //显示jpg图片
void lcd_draw_point(unsigned int x,unsigned int y, unsigned int color); //画一个点


int lcd_open(void); 										//1、打开lcd屏幕
int mmap_lcd(void); 										//2、打开映射
int linux_v4l2_yuyv_init(char *dev_name); 					//3、初始化摄像头
int linux_v4l2_start_yuyv_capturing();						//4、开始摄像头头捕捉画面

                                                    		//5、获取摄像头捕捉的画面
int linux_v4l2_get_yuyv_data (struct jpg_data * jpg_buf);
int show_video_data(unsigned int x,unsigned int y,char *pjpg_buf,unsigned int jpg_buf_size); 
															//6、读取一帧的内容  获取摄像头采集数据                                                    //

int linux_v4l2_yuyv_quit();									//7、关闭摄像头
void lcd_close(void);                                       //8、关闭lcd

int main_camera();                                          //9、摄像头主功能函数
void *main_camera_pt();    

#endif