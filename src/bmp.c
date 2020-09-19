#include "bmp.h"

static int lcd_fd;
static unsigned int *p;
static unsigned int *flag_p;

//1、打开lcd屏幕文件，并映射空间到lcd屏幕文件
int open_bmp_lcd(void)
{
	//第三阶段：将1.bmp图片数据写到开发板屏幕上
	//1、打开lcd屏幕文件
	lcd_fd = open("/dev/fb0", O_RDWR);
	if (lcd_fd == -1)
	{
		printf("open lcd fail!\n");
		return -2;
	}
	//2、第2、3相当于write操作
	p = mmap(NULL,     				//映射的首地址
		   800*480*4, 				//映射空间的大小，也就是开发板的显存
           PROT_READ|PROT_WRITE,    //允许对此空间读写操作
           MAP_SHARED,              //允许内存共享
           lcd_fd,                  //文件描述符
           0                        //偏移的大小
           );


	if (p == MAP_FAILED)
	{
		printf("mmap fail!\n");
		return -3;
	}	

	flag_p = p;
}


//2、显示bmp图片，相当于read和write的操作
int show_bmp_ReadWrite(const char *bmp_path, int lcd_location_x, int lcd_location_y, int bmp_x, int bmp_y){
	/**第一阶段：读取bmp图片的数据**/
	//1、打开1.bmp图片文件
	int bmp_fd = open(bmp_path, O_RDONLY);
	if (bmp_fd == -1)
	{
		printf("open 1.bmp fail!\n");
		return -1;
	}
	//2、跳过bmp图片的头信息数据，lseek跳过文件的前54个字节
	char bmp_buf[bmp_x*bmp_y*3];
	lseek(bmp_fd, 54, SEEK_SET);

	//3、读取1.bmp图片数据
	read(bmp_fd, bmp_buf, bmp_x*bmp_y*3);
	//4、关闭1.bmp图片文件
	close(bmp_fd);

	/**第二阶段：3个字节转4个字节的操作**/
	int lcd_buf[bmp_x*bmp_y];
	int temp_buf[bmp_x*bmp_y];
	int i,x,y;
	for(i=0; i<bmp_x*bmp_y; i++)
	{
		lcd_buf[i] = (bmp_buf[3*i]<<0) + (bmp_buf[3*i+1]<<8) + (bmp_buf[3*i+2]<<16) + (0x00<<24);
	}                //     B         +         G           +          R           +      A

	//将图片数据上下颠倒
	for (x = 0; x < bmp_x; x++)
	{
		for (y = 0; y < bmp_y; y++)
		{
			temp_buf[(bmp_y-1-y)*bmp_x+x] = lcd_buf[y*bmp_x+x];
		}
	}
 

	//调节图片显示的位置
	p = p + lcd_location_x;      //x轴
	p = p + lcd_location_y*800;  //y轴


	//3、将temp_buf里面的数据，填充到映射内存
	int lcd_x, lcd_y;
	for (lcd_x = 0; lcd_x < bmp_x; lcd_x++)
	{
		for (lcd_y = 0; lcd_y < bmp_y; lcd_y++)
		{
			*(p+lcd_y*800+lcd_x) = temp_buf[lcd_y*bmp_x+lcd_x];
		}
	}
	p = flag_p;
	return 0;
}


//3、关闭lcd屏幕文件，关闭映射空间
int close_bmp_lcd(void)
{
	//解除映射，关闭lcd屏幕文件
	munmap(p, 800*480*4);
	close(lcd_fd);
}
