
kernel:
	cd kernel; make ARCH=arm

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

