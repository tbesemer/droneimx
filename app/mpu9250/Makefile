all:	fetch_imu hal

.PHONY: hal
hal:
	make -C hal

.PHONY: fetch_imu
fetch_imu:
	tools/do_get_rtimulib2.sh
