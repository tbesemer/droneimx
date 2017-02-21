
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

#include	"util_driver.h"

#include "deca_types.h"
#include "deca_param_types.h"
#include "deca_regs.h"
#include "deca_device_api.h"

static void spiToolHelp();
static void spiToolExecute();

static int	verboseFlag;
static int	data = 0;
static int	cnt = 1;
static int	width = 4;


int main (int argc, char *argv[])
{
int	c;
int	status;

    while( (c = getopt( argc, argv, "c:d:slhv:" )) != EOF ) {
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
	    case 'h':
	    default:
		spiToolHelp();
		exit( 1 );
		break;

	}
    }

    spiToolExecute();
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

static char bigBuff[ 1536 ];

static int  tmpData = 0x80018001;
static int fd;

static void spiToolExecute()
{

int err, i;

    fd = open( "/dev/spi_tool1", O_RDWR );
    if( fd < 0 ) {
	printf( "open() failed on /dev/spi_tool1\n" );
	perror( "open error" );
	exit( 1 );
    }

    err = ioctl( fd, DRONE_IOCTL_SET_RATE, 200000 );
    err = ioctl( fd, DRONE_IOCTL_SET_MODE_0 );
    err = ioctl( fd, DRONE_IOCTL_SET_8_BIT_WORDS );

    printf( "Device ID: 0x%08X\n", dwt_readdevid() );

#ifdef	DONT
    if( width == 4 ) {
        err = ioctl( fd, DRONE_IOCTL_SET_32_BIT_WORDS );
        if( err < 0 ) {
	    printf( "ioctl() 32 Bit Words failed on /dev/spi_tool1\n" );
	    exit( 1 );
        }
    } else {
        err = ioctl( fd, DRONE_IOCTL_SET_16_BIT_WORDS );
        if( err < 0 ) {
	    printf( "ioctl() 32 Bit Words failed on /dev/spi_tool1\n" );
	    exit( 1 );
        }
    }
#endif

#ifdef	DOING_MODE_CLOCK_TEST
        DRONE_IOCTL_SET_MODE_3,
        DRONE_IOCTL_SET_RATE,


    err = ioctl( fd, DRONE_IOCTL_SET_RATE, 50000 );
    if( err < 0 ) {
	printf( "ioctl() (Set Rate) failed on /dev/spi_tool1\n" );
	exit( 1 );
    }

    err = ioctl( fd, DRONE_IOCTL_SET_MODE_3 );
    if( err < 0 ) {
	printf( "ioctl() (Set Mode 3) failed on /dev/spi_tool1\n" );
	exit( 1 );
    }
#endif

#ifdef	DO_BIG_BUFF
    for( i = 0; i < 1536; i++ )
	bigBuff[ i ] = 0x55;

    err = write( fd, bigBuff, 1 );
    printf( "return count = %d\n", err );
#endif


#undef	CHECK_READ
#ifdef	CHECK_READ
    printf( "Before Read = 0x%08x\n", *(int *)bigBuff );
    err = read( fd, bigBuff, 4 );
    printf( "return count = %d\n", err );
    printf( "After Read = 0x%08x\n", *(int *)bigBuff );
#endif

    close( fd );

}

void decamutexoff( int mutexState )
{
    return;
}

int decamutexon( void )
{
    return( 0 );
}

void deca_sleep( unsigned int time_ms )
{
    usleep( time_ms * 1000 );
}

int readfromspi(uint16 headerLength, const uint8 *headerBuffer, uint32 readlength, uint8 *readBuffer)
{
int cnt;

    printf( "headerlength = %d, readlength = %d\n", headerLength, readlength );

    ioctl( fd,  DRONE_IOCTL_DW1000_CS_ASSERT );

    for( cnt = 0; cnt < headerLength; cnt++ ) {
	printf( "0x%02X ", headerBuffer[ cnt ] );
    }
    printf( "\n" );

    cnt = write( fd, headerBuffer, (int)headerLength );
    printf( "readfromspi(): Write of %d returned %d\n", headerLength, cnt );

    cnt = read( fd, readBuffer, readlength );
    printf( "readfromspi(): Read of %d returned %d\n", readlength, cnt );

    ioctl( fd, DRONE_IOCTL_DW1000_CS_CLEAR );
}

int writetospi(uint16 headerLength, const uint8 *headerBuffer, uint32 bodylength, const uint8 *bodyBuffer)
{

    ioctl( fd,  DRONE_IOCTL_DW1000_CS_ASSERT );

    cnt = write( fd, headerBuffer, (int)headerLength );
    printf( "writetospi(): Write Header of %d returned %d\n", headerLength, cnt );

    cnt = write( fd, bodyBuffer, (int)bodylength );
    printf( "writetospi(): Write Header of %d returned %d\n", headerLength, cnt );

    ioctl( fd, DRONE_IOCTL_DW1000_CS_CLEAR );
}
