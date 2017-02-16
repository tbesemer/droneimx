
export ENV_ROOT := $(shell cd ../;pwd)
export CROSS_COMPILE=arm-poky-linux-gnueabi-
export ARCH=arm


CFILES := util_driver.c

KDIR=${ENV_ROOT}/kernel
CFLAGS_MODULE += -I ${ENV_ROOT}/util_app 

obj-m := util_driver.o

ssc-objs := $(CFILES:.c=.o)
all:
		make V=1 -C $(KDIR) M=$(PWD) modules
		cp  util_driver.ko ${ENV_ROOT}/images/util_driver.ko
		cp  util_driver.ko ~/drone

clean:
		make -C $(KDIR) M=$(PWD) clean
