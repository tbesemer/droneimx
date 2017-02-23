export ENV_ROOT := $(shell cd ../../../;pwd)

CFLAGS := -I ${ENV_ROOT}/app/util_app -I ${ENV_ROOT}/include
		
libmpu9250_hal.a: mpu9250_hal.o 
	${AR} crv libmpu9250_hal.a mpu9250_hal.o
	${RANLIB} libmpu9250_hal.a
	cp -p libmpu9250_hal.a ${ENV_ROOT}/lib/

mpu9250_hal.o: mpu9250_hal.c
	${CC} ${CFLAGS} -c -o mpu9250_hal.o mpu9250_hal.c
clean:
	rm -f *.o *.a ${ENV_ROOT}/lib/libmpu9250_hal.a
