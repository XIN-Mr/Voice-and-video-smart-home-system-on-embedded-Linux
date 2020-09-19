#include "ts.h"

static int ts_fd;

//1、打开触摸屏文件
int open_ts(void)
{
	//1、打开触摸屏
	ts_fd = open("/dev/input/event0", O_RDONLY);
	if (ts_fd == -1)
	{
		printf("open /dev/input/event0 fail!\n");
		return -1;
	}
	return 0;
}


//2、获取触摸屏数据x和y的坐标
int get_ts_xy(int *ts_x, int *ts_y)
{
	//2、读取触摸屏的数据
	struct input_event ts_buf;
	int count = 0;

	while(1)
	{
		read(ts_fd, &ts_buf, sizeof(ts_buf)); //相当于scanf

		//获取x轴的坐标
		if(ts_buf.type == EV_ABS && ts_buf.code == ABS_X)
		{
			count++;
			*ts_x = ts_buf.value;
			//printf("x = %d\n", ts_buf.value);
		}

		//获取y轴的坐标
		if(ts_buf.type == EV_ABS && ts_buf.code == ABS_Y)
		{
			count++;
			*ts_y = ts_buf.value;
			//printf("y = %d\n", ts_buf.value);
		}

		if (count == 2)
		{
			printf("(%d, %d)\n", *ts_x, *ts_y);
			count = 0;
			break;
		}

	}
	
	return 0;

}

//3、关闭触摸屏文件
int close_ts(void)
{
	//3、关闭触摸屏
	close(ts_fd);
	return 0;
}


