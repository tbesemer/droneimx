export ENV_ROOT := $(shell cd ../../;pwd)

CFLAGS := -I ${ENV_ROOT}/app/dw1000/hal
LIB_PATH := ${ENV_ROOT}/lib
LIBS := ${LIB_PATH}/libdw1000_hal.a ${LIB_PATH}/libdeca_driver.a
		
spi_tool: spi_tool.o 
	${CC} ${CFLAGS} -o spi_tool spi_tool.o ${DECA_OBJS} ${LIBS}
	cp spi_tool ${ENV_ROOT}/images/
	cp spi_tool ~/drone/

spi_tool.o: spi_tool.c util_driver.h
	${CC} ${CFLAGS} -c -o spi_tool.o spi_tool.c

clean:
	rm -f spi_tool *.o ${ENV_ROOT}/images/spi_tool
