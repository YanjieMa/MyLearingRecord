
1.编译内核
	make mrproper	-> clean
	make menuconfig -> .config
	make			-> bzImage  /arch/x86/boot/

2.编译busybox
	make menuconfig  Build static binary (no shared libs)
	make install

3.制作initramfs
	cpio
4.启动qemu


计算机启动过程：
	按下电源，主板上电
	CPU Reset
	BIOS/UEFI
	Bootloader
		解压内核镜像 bzImage
		将内核加载进入内存
		将initramfs加载进入内存
	Kernel
		mount ramfs/tmpfs 内存上的文件系统
		查看注册的文件系统 cat /proc/filesystems| grep ramfs
		解压initramfs到rootfs
		找到init程序，-> init
	init
		deal
		挂载真实的rootfs
