export ENV_ROOT := $(shell cd ../../;pwd)

HEADER_FILES := deca_device_api.h deca_param_types.h deca_regs.h deca_types.h deca_version.h

libdeca_driver.a: deca_device.o deca_params_init.o Makefile
	${AR} crv libdeca_driver.a  deca_device.o deca_params_init.o
	${RANLIB} libdeca_driver.a 
	cp -p libdeca_driver.a ${ENV_ROOT}/lib/

deca_device.o: deca_device.c ${HEADER_FILES} Makefile
		${CC} -c -o deca_device.o deca_device.c

deca_params_init.o: deca_params_init.c ${HEADER_FILES} Makefile
		${CC} -c -o deca_params_init.o deca_params_init.c

clean:
	rm -f *.o *.a ${ENV_ROOT}/lib/libdeca_driver.a
