
#include	<fcntl.h>
#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include 	<fcntl.h>
#include	<sys/mman.h>
#include	<sys/ioctl.h>
#include	<unistd.h>

#include	<sys_types.h>
#include	<util_driver.h>
#include	<dw1000_hal.h>
#include	<mpu9250_hal.h>


static void spiToolHelp();
static void dw1000_deviceId();
static int mpu9250_test();

static int	verboseFlag;
static int	data = 0;
static int	cnt = 1;
static int	width = 4;


int main (int argc, char *argv[])
{
int	c;
int	status;

    while( (c = getopt( argc, argv, "c:d:slhv:12" )) != EOF ) {
	switch (c) {
	    case 'c':
		sscanf(optarg, "0x%x", &cnt );
		break;
	    case 'd':
		sscanf(optarg, "0x%x", &data );
		break;
	    case 's':
                width = 2;
		break;
	    case 'l':
                width = 4;
		break;
	    case 'v':
		sscanf(optarg, "%d", &verboseFlag );
		break;
	    case '1':
    		dw1000_deviceId();
		break;
	    case '2':
    		mpu9250_test();
		break;
	    case 'h':
	    default:
		spiToolHelp();
		exit( 1 );
		break;

	}
    }

    exit( 0 );

}

static char *spiToolHelpStrings[] = {
    " ",
    "usage: spi_tool -b|w|l -w -a -c cnt -d data -h -v level",
    " ",
    "       -s|l         Width, default long",
    "       -c cnt       Number of writes to set",
    "       -d data      Data to use in set operations, default 0x0",
    "       -v level     Operate Verbose",
    "       -h           Dump help menu and exit",
    " ",
    ""
};

static void spiToolHelp()
{
int i;

    i = 0;

    while( *spiToolHelpStrings[i] ) {
	printf("%s\n", spiToolHelpStrings[i++] );
    }

}

static void dw1000_deviceId()
{
    decaHalOpen();
    decaHalClose();
}

static int mpu9250_test()
{
uint8_t regVal;

    mpu9250HalOpen();
    mpu9250HalReadReg( 0x87, &regVal );
    mpu9250HalClose();
    
    return( 0 );
}
