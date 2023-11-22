#include <osdev/arch/x86/multiboot.h>

.section .multiboot
	.long MB_MAGIC
	.long MB_ALIGNED_4K_MEM_MAP
	.long CHECKSUM

.section .bss
	/*惯例：必须16bytes对齐*/
	.align 16
	stack_bottom:
		.skip 16318, 0
	stack_top:
	/* 栈从高地址往地地址增长 */	

.section .text
	.global start_
	/*.type start_, @function*/
	start_:
		movl $stack_top, %esp  /* esp寄存器 指向 栈顶 */
		/*
			todo:kernel init
				1.load GDT
				2.load IDT
				3.enable paging
		*/
		call _kernel_init

		subl $0x6, %esp
		movl $_gdt, 2(%esp)
		movw _gdt_limit, %ax
		movw %ax, (%esp)
		lgdt (%esp)
		addl $0x6, %esp
		/*初始化段寄存器*/
		movw $0x10, %cx
		movw %cx, %es
		movw %cx, %ds
		movw %cx, %fs
		movw %cx, %gs
		movw %cx, %ss

		pushw $0x08
		pushl $_after_gdt
		retf
		
_after_gdt:
		pushl %ebx 
		call _kernel_main
		
		/*进制中断发生    sti 允许中断发生*/
		cli

		/*操作系统退出，系统hold循环*/
	j_:
		hlt
		jmp j_
