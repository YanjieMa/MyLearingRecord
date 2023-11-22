1. Preprocessing
	gcc -E main.c -o main.i
2. Generating Assembly Language
	gcc -S main.c -o main.s
3. Source File to Object File
	gcc -c main1.c main2.c
	gcc -c main.c -o main.o

4. Creating a Static Library
	编译成.o文件
		gcc -c main.c -o mian.o
	编静态库
		ar -r libmain.a main.o file.o
	连接成可执行文件
		gcc main.c -o mian -llibmain -L./
5. Creating a Shared Library
	编译二进制.o文件
		gcc -c -fpic main.c
	编动态库
		gcc -shared file1.c file2.c -o libmymath.so
	连接动态库
		gcc main.c -o exec -lmymath -L.

6. makefile 的基本规则
	target : 依赖
		方法

	.PHONY : 伪目标

7. Makefile 预定义变量
	$@ 目标的完整名称
	$< 第一个依赖文件的名称
	$^ 所有依赖文件的名称 以空格分开 不包含重复的依赖文件

8. 赋值符号
	=	简单赋值
	:=	立即赋值
	？= 默认赋值，如果已经定义,不再进行操作
	+=	累加
	\	续行符


9. Makefile 基础函数
	$(func, arguments)	or ${func, arguments}
	$(shell cmd arguments)
	$(subst, src/, objs/, $(apps))	
	$(patsubst, src/%.c, objs/%.o, $(apps))
	$(foreach item,list,text) --> $(list:%=-I%)
	$(dir names) 取出目录部分
	$(notdir name) 删除路径部分
	$(filter %.o,$(libs)) 格式过滤
	$(basename $(names)) 去掉后缀
	$(strip string) 去掉开头结尾空格
	$(call <express>, <para1>, <para2>) 类似于函数
	$(error <text>)


10. have try
	见实战

11. 编译选项
	-m64 指定编译为64位应用程序
	-std= 指定编译标准 -std=c++11
	-g 包含调试信息
	-w 不显示警告
	-O 优化等级
	-I 加在头文件路径前面
	-fpic 使用相对地址，没有绝对地址，共享库使用
	连接选项
	-l 加在库名前
	-L 加在库路径前面 编译时找的路径
	-Wl,-rpath= 运行时，找.so的路径

12. Makefile condition
	ifeq else endif
	ifneq else endif
	ifdef else endif
	ifndef else endif
	
