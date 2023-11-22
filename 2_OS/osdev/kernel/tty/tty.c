#include "osdev/tty/tty.h"

#define TTY_WIDTH	80  // 屏幕高度 字符为单位
#define TTY_HEIGHT	25	// 屏幕宽度 

/* CGA:
 * 15  14     11	     7             0
 *      背景色   前景色    字符ASCII码
 *				L R G B 
 * */

unsigned short *buffer = (unsigned short *)0xB8000; //文本缓冲区（显存）起始点 物理地址
unsigned short theme_color = VGA_COLOR_BLACK;
unsigned int TTY_COLUMN = 0;
unsigned short TTY_ROW = 0;

void tty_set_theme(unsigned short fg, unsigned short bg)
{
	theme_color = ( bg << 4 | fg ) << 8;

}

 void tty_put_char(char chr)
{
	if(chr == '\n'){
		TTY_COLUMN = 0;
		TTY_ROW++;
	}else if(chr == '\r'){
		TTY_COLUMN = 0;
	}else{
		*(buffer + TTY_COLUMN + TTY_ROW * TTY_WIDTH) = theme_color | chr;
		TTY_COLUMN++;
		
		if(TTY_COLUMN >= TTY_WIDTH){
			TTY_COLUMN = 0;
			TTY_ROW++;
		}
	}
	if(TTY_ROW >= TTY_HEIGHT){
		tty_scroll_up();
		TTY_ROW--;
	}
}

void tty_put_str(char *str)
{
	while(*str != '\0'){
		tty_put_char(*str);
		str++;
	}
}

void tty_scroll_up()
{
	//TODO use memcpy
}

void tty_clear()
{
	for(unsigned int x = 0; x < TTY_WIDTH; x++){
		for(unsigned int y = 0; y < TTY_HEIGHT; y++){
			*(buffer + x + y * TTY_WIDTH) = theme_color;
		}
	}
}
