initfs.img:
	cd initfs && find . -print0 | cpio -ov --null --format=newc > ../initfs.img

run_rootfs:
	sudo qemu-system-x86_64  -kernel bzImage -hda rootfs.img -m 1G  -nographic -append "root=/dev/sda  earlyprintk=serial,ttyS0 console=ttyS0"  -smp 1

run_initfs:
	sudo qemu-system-x86_64  -kernel bzImage -initrd initfs.img  -m 1G  -nographic -append "root=/dev/ram rdinit=/sbin/init  earlyprintk=serial,ttyS0 console=ttyS0"  -smp 1 -s -S

runqemu:
	qemu-system-x86_64  -kernel bzImage -drive format=raw,file=initramfs.img -m 1G -nographic -append "root=/dev/sda  console=ttyS0"  -smp 1

run:
	sudo qemu-system-x86_64  -kernel bzImage -hda rootfs.img -m 1G  -nographic -append "root=/dev/sda  earlyprintk=serial,ttyS0 console=ttyS0"  -smp 1 -netdev user,id=mynet0,hostfwd=tcp::8080-:80 -device e1000,netdev=mynet0
