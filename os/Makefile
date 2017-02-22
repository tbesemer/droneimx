all: test_code

clean: test_code_clean

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

.PHONY: test_code
test_code:
	make -C dw1000/decadriver
	make -C dw1000/hal
	make -C util_app

.PHONY: test_code_clean
test_code_clean:
	make -C dw1000/decadriver clean
	make -C dw1000/hal clean
	make -C util_app clean
