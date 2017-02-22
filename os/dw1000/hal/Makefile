export ENV_ROOT := $(shell cd ../../;pwd)

CFLAGS := -I ${ENV_ROOT}/dw1000/decadriver -I ${ENV_ROOT}/util_app
DECA_ROOT := ${ENV_ROOT}/dw1000/decadriver
		
libdw1000_hal.a: dw1000_hal.o 
	${AR} crv libdw1000_hal.a dw1000_hal.o
	${RANLIB} libdw1000_hal.a
	cp -p libdw1000_hal.a ${ENV_ROOT}/lib/

dw1000_hal.o: dw1000_hal.c
	${CC} ${CFLAGS} -c -o dw1000_hal.o dw1000_hal.c
clean:
	rm -f *.o *.a ${ENV_ROOT}/lib/libdw1000_hal.a
