/*// ENTRY 关键字用于定义应用程序的入口点
ld有多种方法设置进程入口地址, 按一下顺序: (编号越前, 优先级越高)
	1、ld命令行的-e选项
	2、链接脚本的ENTRY(SYMBOL)命令
	3、如果定义了start符号, 使用start符号值
	4、如果存在.text section, 使用.text section的第一字节的位置值
	5、使用值0

//OUTPUT_FORMAT(输出格式)  objdump -i 可以查看支持的输出格式

//STARTUP(Boot.o) 链接到可执行文件开头的文件

//SEARCH_DIR(Directory) 为库搜索目录提供路径  -nostdlib将导致在改路径中找到的任和库被有效忽略

//INPUT(file1.o file2.o)  用于将对象文件添加到命令行

//OUTPUT(kernel.bin)  指定要生成的文件作为链接过程的输出  这是最终创建二进制文件的名称，与 -o filename 命令行标志的效果相同 后者会覆盖前者

//MEMORY{  
//	ROM(rx) : ORIGIN=0, LENGTH=256K  //起始地址0x0，长度256K,可读可执行
//  RAM(wx) : org=0x00100000, len=1M //起始地址0x00100000,长度1M,可读可写可执行
//}
//生命一个或者多个内存区域 指定器属性 读写执行

//REGION 表示memory命令定义的位置信息

// SECTIONS 说明如何把文件的section映射到输出文件的各个section; 如何把输入section合为输出section,如何把输出section放入程序地址空间（VMA）和进程地址空间（LMA）

//Symbols 可以在连接器中定义任意符号 连接器中已赋值的符号 可以在程序代码代码中作为指针使用
*/

ENTRY(start_)

SECTIONS {
	. = 0x100000;
	/* . = ALIGN(4); //表示从该地址开始后面的存储进行4字节对齐 */
	.text BLOCK(4K) : {
		/* 设置TYPE NOLOAD 该section在运行时，不被载入内存 */
		KEEP(*(.multiboot))  /* KEEP() 强制让连接器保持一些特定的section 防止被优化 -gc-section连接器可能会将认为没用的section过滤掉*/
		*(.text)   /* *(.text)表示所有输入文件的 .text section */
		_etext = .; /* Symbol的使用举例*/
	}
	/* AT(ADDR(.text)+SIZEOF(.text)) //指定LMA（进程地址空间） */
	.bss BLOCK(4K) : {
		*(COMMON)
		*(.bss)
	}
	
	.data BLOCK(4K) : {
		*(.data)
	}

	.rodata BLOCK(0x4K) : {
		*(.rodata)
	}
}
