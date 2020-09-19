#include "bmp.h" 		//bmp图片显示功能
#include "ts.h"  		//触摸屏功能
#include "music.h"		//音乐功能 
#include "movie.h"		//视频功能 
#include "beep_led.h"   //beep和led功能
#include "camera.h"     //摄像头的功能

int main(int argc, char const *argv[])
{
	//相关定义变量
	int ts_x;
	int ts_y;

	//1、打开相关文件
	open_bmp_lcd();	 			//打开lcd屏幕文件，并映射空间到lcd屏幕文件
	open_ts();       			//打开触摸屏文件
	open_mplayer_fifo();    	//打开视频管道文件
	beep_led_insert();          //出入beep和led的驱动文件
	open_beep_led();            //打开你的beep和led的驱动文件     

	
	show_bmp_ReadWrite("./zi_liao/bmp/main_ui.bmp", 0, 0, 800, 480);
	//2、使用相关文件
	while(1)
	{
		//获取x和y轴的坐标
		get_ts_xy(&ts_x, &ts_y); 
		//音乐
		if(ts_x>180&& ts_x<272 && ts_y>147 && ts_y<235) 
		{
			show_bmp_ReadWrite("./zi_liao/bmp/music.bmp", 0, 0, 800, 480);
			main_music(ts_x, ts_y); 
		} 
		//视频
		if(ts_x >388 && ts_x<482 && ts_y>154 && ts_y<235) 
		{
			show_bmp_ReadWrite("./zi_liao/bmp/movie.bmp", 0, 0, 800, 480);
			main_movie(ts_x, ts_y); 
		}  

		//照明
		//亮
		if(ts_x>187 && ts_x<259 && ts_y>322 && ts_y<399) 
		{
			led_on();          		//5、全灯亮
		}  
		//灭
		if(ts_x>390 && ts_x<468 && ts_y>322&& ts_y<400) 
		{
			led_off();         		//6、全灯灭	
		}  

		//门铃
		//响
		if(ts_x>609 && ts_x<685 && ts_y>322 && ts_y<387) 
		{
			int i;
			for(i = 0; i<5; i++)
			{
				beep_on();         		//3、蜂鸣器响
				usleep(250000);
				beep_off();
				usleep(250000);
			}
		}  
		//摄像头和语音通话
		if(ts_x>601 && ts_x<674 && ts_y>158 && ts_y<235) 
		{
			show_bmp_ReadWrite("./zi_liao/bmp/camera.bmp", 0, 0, 800, 480);
			while(1)
			{
				//获取x和y轴的坐标
				get_ts_xy(&ts_x, &ts_y);

				//开启摄像头
				if(ts_x>634 && ts_x<784 && ts_y>16 && ts_y<95)
				{
					system("./zi_liao/tools/show_video &");
				}

				//关闭摄像头
				if(ts_x>634 && ts_x<787 && ts_y>150 && ts_y<235)
				{
					//main_camera();
					system("killall  -9  show_video &");
				}

				//开启语音播放
				if(ts_x>634 && ts_x<785 && ts_y>298 && ts_y<373)
				{
					//录音
					system("./zi_liao/tools/arecord -d5 -c1 -r16000 -twav -fS16_LE example.wav &");
					sleep(6);

					//播放
					system("./zi_liao/tools/aplay example.wav &");


				}

				//返回
				if(ts_x>670 && ts_x<393 && ts_y>420 && ts_y<464)
				{
					show_bmp_ReadWrite("./zi_liao/bmp/main_ui.bmp", 0, 0, 800, 480);
					ts_x = 0;
					ts_y = 0;
					break;
				}
			}
		}
	}
	
	//3、关闭相关文件
	close_bmp_lcd(); 			//关闭lcd屏幕文件，释放映射空间
	close_ts();     			//关闭触摸屏文件
	close_mplayer_fifo();   	//关闭视频管道文件
	close_beep_led();           //关闭beep和led的驱动文件   
	return 0;
}