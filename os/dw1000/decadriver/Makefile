
HEADER_FILES := deca_device_api.h deca_param_types.h deca_regs.h deca_types.h deca_version.h
deca_driver.o: deca_device.o deca_params_init.o
	${LD} -i -o deca_driver.o  deca_device.o deca_params_init.o


deca_device.o: deca_device.c ${HEADER_FILES}
		${CC} -c -o deca_device.o deca_device.c

deca_params_init.o: deca_params_init.c ${HEADER_FILES}
		${CC} -c -o deca_params_init.o deca_params_init.c

clean:
	rm -f *.o
