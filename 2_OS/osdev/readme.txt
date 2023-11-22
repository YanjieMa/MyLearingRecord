
虚拟机 Virtual Box   No
QEMU x86模拟器		 No
Bochs x86模拟器		 Yes


安装 i686-elf-gcc


INST  SRC, DEST
寄存器 %eax, %ebp, ...
立即数 $123
内存引用 0x7c0, (%esp)
movw $12, %ax
b 8bit
w 16bit
l 32bit
q 64bit

file.s 表示文件是汇编文件 不需要预处理
file.S 表示文件是会变文件 需要预处理

文本缓冲区现存地址 0xB8000 (物理地址)






<<安装 GDT>>
	指令 lgdt 加载GDT的地址到GDTR寄存器
	GDTR的大小是48bits, 而x86的操作数宽度和所有通用寄存器为32bits, 所以GDTR的值只能放在内存, 而后由cpu直接从内存读出
	lgdt (*reg)		%reg 的值 是 GDTR的值的地址
