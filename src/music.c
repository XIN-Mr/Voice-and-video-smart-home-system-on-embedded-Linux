#include "music.h"
#include "bmp.h" 		//bmp图片显示功能
#include "ts.h"  		//触摸屏功能

static char music_volume[128] = {0};

static int music_count=5 , puase_count= 0;

static char music_hub[11][32] = {
	"./zi_liao/mp3/0.mp3",
	"./zi_liao/mp3/1.mp3",
	"./zi_liao/mp3/2.mp3",
	"./zi_liao/mp3/3.mp3",
	"./zi_liao/mp3/4.mp3",
	"./zi_liao/mp3/5.mp3",
	"./zi_liao/mp3/6.mp3",
	"./zi_liao/mp3/7.mp3",
	"./zi_liao/mp3/8.mp3",
	"./zi_liao/mp3/9.mp3",
	"./zi_liao/mp3/10.mp3"
};


//1、播放音乐
int play_music(char *music_path)  
{
    char music_buf[50];
	sprintf(music_buf, "madplay  %s  & \n", music_path); 
    system(music_buf); //自动帮我们执行函数里面shell命令
    return 0;
}

//2、暂停音乐
int stop_music(void)
{
	system("killall -STOP  madplay");
	return 0;
}

//3、继续音乐
int cont_music(void)
{
	system("killall -CONT  madplay");
	return 0;
}

//4、退出音乐
int quit_music(void)
{
	system("killall -KILL  madplay");
	return 0;
}

//5、音量
int volume_adjust_func(char *music_path, int volume_adjust)
{
	bzero(music_volume, sizeof(music_volume));
	quit_music();
	sprintf(music_volume, "madplay  %s -a %d &", music_path ,volume_adjust);
	system(music_volume);
	return 0;
}


//6、单曲循环
int circulation_music(void)
{
	system("killall -9 madplay"); 
	system("madplay ./zi_liao/mp3/5.mp3 -r &");     //单曲循环
	return 0;
}

//show_bmp("./zneed_data/bmp/music.bmp", 0, 0, 800, 480);
//7、音乐功能使用
int main_music(int ts_x, int ts_y)
{
	int temp_music_count = music_count, temp_puase_count = puase_count;
	while(1)
	{
		//获取x和y轴的坐标
		get_ts_xy(&ts_x, &ts_y); 

		//开始播放曲目
		if(ts_x > 340 && ts_x < 425 && ts_y > 380 && ts_y < 454)
		{
			play_music(music_hub[temp_music_count]); //默认播放第6首
		}

		//继续播放
		if(ts_x > 340 && ts_x < 425 && ts_y > 380 && ts_y < 454 && temp_puase_count == 1)
		{
			cont_music();
			temp_puase_count =0;
		}
		//暂停播放
		if(ts_x > 337 && ts_x < 425 && ts_y > 275 && ts_y < 351 && temp_puase_count == 0)
		{
			quit_music();
			temp_puase_count = 1;
		}
		//停止播放
		if(ts_x > 79 && ts_x < 143&& ts_y > 391 && ts_y < 448)
		{
			stop_music();
		}
		//上一曲
		if(ts_x > 204 && ts_x < 290 && ts_y > 386 && ts_y < 447)
		{
			printf("上一首\n");
			
			if(temp_music_count >=1 && temp_music_count <11)
			{
				temp_music_count--;
				system("killall -9 madplay"); 
				play_music(music_hub[temp_music_count]);
			}
			else{
				system("killall -9 madplay"); 
				temp_music_count = 0;
				play_music(music_hub[temp_music_count]); //回到主曲
			}
		}
		//下一曲
		if(ts_x > 479 && ts_x < 561 && ts_y > 383 && ts_y < 442)
		{

			printf("下一首\n");
			
			if(temp_music_count <=9 && temp_music_count >=0)
			{
				temp_music_count++;
				system("killall -9 madplay"); 
				play_music(music_hub[temp_music_count]);
			}
			else{
				system("killall -9 madplay"); 
				temp_music_count=0;
				play_music(music_hub[temp_music_count]); //回到主曲
			}
			
		}
		//音量调节
		if(ts_x > 603 && ts_x < 660 && ts_y > 398 && ts_y < 450)
		{
			volume_adjust_func(music_hub[temp_music_count], 18);
			
		}
		if(ts_x > 702 && ts_x < 760 && ts_y > 393 && ts_y < 450)
		{
			volume_adjust_func(music_hub[temp_music_count], 1);
		}

		//返回主页
		if(ts_x > 2 && ts_x < 97 && ts_y > 15 && ts_y < 107)
		{
			show_bmp_ReadWrite("./zi_liao/bmp/main_ui.bmp", 0, 0, 800, 480);
			ts_x = 0;
			ts_y = 0;
			music_count=5;
			break;
		}
	}
	return 0;
}