#include "beep_led.h"

//=======全局变量=======//
static int beep_fd;
static int led_fd;

//1、删除原有的led和beep驱动，重新插入自己的
int beep_led_insert()
{
	//beep驱动插入
	system("rmmod gec6818_beep");
	system("insmod  ./zi_liao/beep_led_drv/beep_drv.ko");

	//led驱动插入
	system("rmmod led");
	system("insmod  ./zi_liao/beep_led_drv/led_drv.ko");
	return 0;

}

//2、初始化beep、led驱动
int open_beep_led()
{
	//1、打开beep驱动文件
	beep_fd = open("/dev/gz1901_beep_drv", O_RDWR);
	if(beep_fd == -1)
	{
		printf("open beep error\n");
		return -1;
	}

	beep_off();  //一开始初始化时，就让其蜂鸣器不响
	
	//2、打开led设备文件
	led_fd= open("/dev/gz1901_led_drv", O_RDWR);
	if(led_fd < 0)
	{
		printf("open led error\n");
		return -1;
	}

	led_off();  //一开始初始化时，就让其灯全灭
	return 0;

}

//3、蜂鸣器响
int beep_on()
{
	ioctl(beep_fd,GZ1901_BEEP_ON);
	return 0;
}

//4、蜂鸣器不响
int beep_off()
{

	ioctl(beep_fd,GZ1901_BEEP_OFF);
	return 0;
}

//5、全灯亮
int led_on()
{
	ioctl(led_fd,GZ1901_LED_ON,7);
	ioctl(led_fd,GZ1901_LED_ON,8);
	ioctl(led_fd,GZ1901_LED_ON,9);
	ioctl(led_fd,GZ1901_LED_ON,10);
	return 0;
}

//6、全灯灭
int led_off()
{
	ioctl(led_fd,GZ1901_LED_OFF,7);
	ioctl(led_fd,GZ1901_LED_OFF,8);
	ioctl(led_fd,GZ1901_LED_OFF,9);
	ioctl(led_fd,GZ1901_LED_OFF,10);
	return 0;
}

//7、关闭beep和led的驱动文件
int close_beep_led(void)
{
	close(beep_fd);
	close(led_fd);
}


int main_beep(void)
{
	
}
int main_led(void)
{

}