#include "movie.h"
#include "bmp.h" 		//bmp图片显示功能
#include "ts.h"  		//触摸屏功能

static int fifo_fd;
static char movie_cmd_buf[256] = {0};

static int movie_count=1;

static char movie_hub[4][32] = {
	"./zi_liao/mp4/0.mp4",
	"./zi_liao/mp4/1.mp4",
	"./zi_liao/mp4/2.mp4",
	"./zi_liao/mp4/3.mp4",
};

//0、打开管道文件，让命令得以从此管道输入 
int open_mplayer_fifo(void)
{
	//0.判断文件是否存在
	//存在   -->  0  --> 假  -->if的内容不执行
	//不存在 --> -1  --> 真  -->if的内容执行
	if(access("/tmp/fifo",F_OK))  
	{
		//1.创建管道文件c
		int ret = mkfifo("/tmp/fifo",0777);
		if(ret == -1)
		{
			printf("mkfifo error!\n");
			return 0;
		}	
	}

	//2.访问管道文件
	fifo_fd = open("/tmp/fifo",O_RDWR);
	if(fifo_fd < 0)
	{
		printf("open fifo error!\n");
		return 0;
	}

	return 0;
}

//1、关闭管道
int close_mplayer_fifo(void)
{
	close(fifo_fd);
	return 0;
}

//2、播放视频
int start_movie(int movie_x, int movie_y, int movie_wide, int movie_high, char * movie_path)
{
	bzero(movie_cmd_buf, sizeof(movie_cmd_buf));
	sprintf(movie_cmd_buf, "mplayer -slave -quiet -input file=/tmp/fifo -geometry %d:%d -zoom -x %d -y %d %s &", 
		movie_x, movie_y, movie_wide, movie_high, movie_path);
	system(movie_cmd_buf);
	return 0;
}

//3、视频音量
int adjust_movie_volume(int movie_volume_num)
{
	bzero(movie_cmd_buf, sizeof(movie_cmd_buf));
	sprintf(movie_cmd_buf, "volume %d\n", movie_volume_num);
	write(fifo_fd,movie_cmd_buf,strlen(movie_cmd_buf));
	return 0;
}

//4、视频快进、快退
int movie_forward_behind(int movie_fw_bh_num)
{
	bzero(movie_cmd_buf, sizeof(movie_cmd_buf));
	sprintf(movie_cmd_buf, "seek %d\n", movie_fw_bh_num);
	write(fifo_fd,movie_cmd_buf,strlen(movie_cmd_buf));
	return 0;
}


//5、视频暂停/继续
int stop_movie()
{
	bzero(movie_cmd_buf, sizeof(movie_cmd_buf));
	strcpy(movie_cmd_buf, "pause\n");
	write(fifo_fd,movie_cmd_buf,strlen(movie_cmd_buf));
	return 0;
}

//6、视频退出
int quit_movie()
{
	bzero(movie_cmd_buf, sizeof(movie_cmd_buf));
	strcpy(movie_cmd_buf, "quit 0\n");
	write(fifo_fd,movie_cmd_buf,strlen(movie_cmd_buf));
	return 0;
}

//7、视频静音设置1为静音开启，0为关闭
int mute_movie(int mute_num)
{
	bzero(movie_cmd_buf, sizeof(movie_cmd_buf));
	sprintf(movie_cmd_buf, "mute %d\n", mute_num);
	write(fifo_fd,movie_cmd_buf,strlen(movie_cmd_buf));
	return 0;
}


//8、视频功能使用
int main_movie(int ts_x, int ts_y)
{
	int temp_movie_count=movie_count;
	while(1)
	{

		//获取x和y轴的坐标
		get_ts_xy(&ts_x, &ts_y); 

		if(ts_x > 260 && ts_x < 329 && ts_y > 416 && ts_y < 468) //开始播放
		{
			start_movie(127,73, 524, 316, movie_hub[temp_movie_count]);
		}

		if(ts_x > 94 && ts_x < 456 && ts_y > 413 && ts_y < 467) //暂停/继续播放
		{
			stop_movie();  
		}

		if(ts_x > 556 && ts_x < 624 && ts_y > 422 && ts_y < 469) //静音
		{
			mute_movie(1);
		}

		if(ts_x > 447 && ts_x < 519 && ts_y > 420 && ts_y < 469) //开音
		{
			mute_movie(0);
		}

		if(ts_x > 12 && ts_x < 75 && ts_y > 412 && ts_y < 473) //结束播放
		{
			quit_movie();
		}

		if(ts_x > 357 && ts_x < 415 && ts_y > 416 && ts_y < 469) //快进
		{
			movie_forward_behind(10);
		}

		if(ts_x > 178 && ts_x < 239 && ts_y > 412 && ts_y < 469) //快退
		{
			movie_forward_behind(-10);
		}

		if(ts_x > 11 && ts_x < 83 && ts_y > 168 && ts_y < 229) //音量加
		{
			adjust_movie_volume(10);
		}
		if(ts_x > 10 && ts_x < 81 && ts_y > 261 && ts_y < 329) //音量减
		{
			adjust_movie_volume(-10);
		}

		if(ts_x > 664 && ts_x < 731 && ts_y > 404 && ts_y < 478) //上一首
		{
			printf("上一个影片\n");
			
			if(temp_movie_count >=1 && temp_movie_count <4)
			{
				temp_movie_count--;

				start_movie(127,73, 524, 316, movie_hub[temp_movie_count]);
			}
			else{
				temp_movie_count=0;
				
				start_movie(127,73, 524, 316, movie_hub[temp_movie_count]); //回到主movie
			}
		}
		if(ts_x > 731 && ts_x < 779 && ts_y > 404 && ts_y < 478) //下一首
		{
			printf("下一个影片\n");
			if(temp_movie_count <=2 && temp_movie_count >=0)
			{
				temp_movie_count++;
				
				start_movie(127,73, 524, 316, movie_hub[temp_movie_count]);
			}
			else{
				temp_movie_count=0;
				
				start_movie(127,73, 524, 316, movie_hub[temp_movie_count]); //回到主movie
			}
			
		}
		if(ts_x > 10 && ts_x < 62 && ts_y > 16 && ts_y < 68)
		{
			show_bmp_ReadWrite("./zi_liao/bmp/main_ui.bmp", 0, 0, 800, 480);
			ts_x = 0;
			ts_y = 0;
			break;
		}
	}
	return 0;
}