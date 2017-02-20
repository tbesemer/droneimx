export ENV_ROOT := $(shell cd ../;pwd)

CFLAGS := -I ${ENV_ROOT}/dw1000/decadriver
DECA_ROOT := ${ENV_ROOT}/dw1000/decadriver
DECA_OBJS := ${DECA_ROOT}/deca_device.o ${DECA_ROOT}/deca_params_init.o
		
spi_tool: spi_tool.o 
	${CC} ${CFLAGS} -o spi_tool spi_tool.o ${DECA_OBJS}
	cp spi_tool ~/drone/

spi_tool.o: spi_tool.c util_driver.h
	${CC} ${CFLAGS} -c -o spi_tool.o spi_tool.c
clean:
	rm -f spi_tool *.o
