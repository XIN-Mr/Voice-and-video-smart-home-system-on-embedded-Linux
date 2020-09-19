#ifndef __MUSIC_H
#define __MUSIC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>

int play_music(char *music_path);                        		    //1、开始音乐
int stop_music(void);                                        		//2、暂停音乐
int cont_music(void);                                        		//3、继续音乐
int quit_music(void);                                        		//4、退出音乐
int volume_adjust_func(char *music_path, int volume_adjust);        //5、音量调节
int circulation_music(void);                                 		//6、循环音乐
int main_music(int ts_x, int ts_y);                                 //7、音乐功能使用



#endif