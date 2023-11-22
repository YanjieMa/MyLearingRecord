/**************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 mian.c
作者	   : 左忠凯
版本	   : V1.0
描述	   : I.MX6U开发板裸机实验13 串口实验
其他	   : 本实验我们学习如何使用I.MX6的串口，实现串口收发数据，了解
		 I.MX6的串口工作原理。
论坛 	   : www.wtmembed.com
日志	   : 初版V1.0 2019/1/15 左忠凯创建
**************************************************************/
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_uart.h"
#include "bsp_exit.h"
#include "stdio.h"
#include "bsp_lcd.h"
#include "bsp_lcdapi.h"
#include "bsp_rtc.h"
#include "bsp_ap3216c.h"


unsigned int backcolor[10] = {
LCD_BLUE, LCD_GREEN, LCD_RED, LCD_CYAN, LCD_YELLOW,
LCD_LIGHTBLUE, LCD_DARKBLUE, LCD_WHITE, LCD_BLACK, LCD_ORANGE};



/*
 * @description	: main函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	unsigned char state = OFF;
	unsigned char index = 0;
#if 0
	int a,b;
#endif
	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 			*/
	delay_init();				/* 初始化延时 高精度延时GPT			*/
	clk_enable();				/* 使能所有的时钟 			*/
	led_init();					/* 初始化led 			*/
	beep_init();				/* 初始化beep	 		*/
	uart_init();				/* 初始化串口，波特率115200 */
	exit_init();				/* 初始化key按键为中断，切换beep */
	lcd_init();					/* 初始化LCD */
	rtc_init();					/* 初始化RTC */

	tftlcd_dev.forecolor = LCD_RED;	

	lcd_show_string(10, 40, 260, 32, 32,(char*)"IMX6ULL");	

	tftlcd_dev.forecolor = LCD_BLUE;

	char buf[128];
	memset(buf,0,sizeof(buf));

	struct rtc_datetime rtcdate;
	

	while(ap3216c_init()){
		lcd_show_string(30, 130, 200, 16, 16, (char*)"AP3216C Check Failed!");
		delayms(1000);
		lcd_show_string(30, 130, 200, 16, 16, (char*)"Please Check! ");		
		delayms(1000);
	}	

	unsigned short ir,als,ps;


	tftlcd_dev.forecolor = LCD_BLUE;
	lcd_show_string(70, 100, 200, 16, 16, (char*)"ir:");
	lcd_show_string(70, 120, 200, 16, 16, (char*)"ps:");
	lcd_show_string(70, 140, 200, 16, 16, (char*)"als:");



	while(1)				
	{	
		printf("输入两个整数，使用空格隔开：");	
		state = !state;
		led_switch(LED0,state);

		rtc_getdatetime(&rtcdate);
		sprintf(buf,"%d/%d/%d %d:%d:%d",rtcdate.year, rtcdate.month,
			rtcdate.day, rtcdate.hour, rtcdate.minute, rtcdate.second);
		lcd_fill(50,70, 300,94, tftlcd_dev.backcolor);
		lcd_show_string(50,70,200,24,24,(char*)buf);
		
		ap3216c_readdata(&ir, &ps, &als); /* 读取数据 */
		tftlcd_dev.forecolor = LCD_BLUE;
		lcd_shownum(70+32,100,ir,5,16);	
		lcd_shownum(70+32,120,ps,5,16);	
		lcd_shownum(70+32,140,als,5,16);	

	
		delayms(1000);

		


	}
	return 0;
}
