#ifndef _MOVIE_H
#define _MOVIE_H

#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int open_mplayer_fifo(void);                                //0、打开管道文件，让命令得以从此管道输入 
int close_mplayer_fifo(void);                               //1、关闭管道文件
int start_movie(int movie_x, int movie_y, int movie_wide, 
	                   int movie_high, char * movie_path);  //2、播放视频
int adjust_movie_volume(int movie_volume_num);              //3、视频音量
int movie_forward_behind(int movie_fw_bh_num);              //4、视频快进、快退
int stop_movie();                                           //5、视频暂停/继续
int quit_movie();                                           //6、视频退出
int mute_movie(int mute_num);                               //7、视频静音设置1为静音开启，0为关闭
int main_movie(int ts_x, int ts_y);                         //8、视频播放功能

#endif