
.PHONY:	kernel
kernel:
	cd kernel; make ARCH=arm
	cp -p kernel/arch/arm/boot/zImage images/

kernel_dtb:
	cd kernel; make ARCH=arm dtbs

kernel_clean:
	cd kernel; make ARCH=arm clean

kernel_mrproper:
	cd kernel; make ARCH=arm mrproper

kernel_defconfig:
	cp config/imx6_config kernel/.config
	cd kernel; make ARCH=arm oldconfig

kernel_xconfig:
	cd kernel; make ARCH=arm xconfig

kernel_saveconfig:
	cp kernel/.config config/imx6_config

