
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

#include "dw1000_hal.h"

#include "util_driver.h"

#include "deca_types.h"
#include "deca_param_types.h"
#include "deca_regs.h"
#include "deca_device_api.h"

#define	DUMP_DEVICE_ID

static int decaHalFd;

int decaHalOpen()
{

int err, i;

    err = 0;

    decaHalFd = open( "/dev/spi_drone1", O_RDWR );
    if( decaHalFd < 0 ) {
	printf( "decaHalOpen(): open() failed on /dev/spi_drone1\n" );
	perror( "open error" );
	return( -1 );
    }

    err += ioctl( decaHalFd, DRONE_IOCTL_SET_RATE, 200000 );
    err += ioctl( decaHalFd, DRONE_IOCTL_SET_MODE_0 );
    err += ioctl( decaHalFd, DRONE_IOCTL_SET_8_BIT_WORDS );
    if( err ) {
	printf( "decaHalOpen(): ioctl() failed on /dev/spi_drone1\n" );
	return( -1 );
    }

#ifdef	DUMP_DEVICE_ID
    printf( "Device ID: 0x%08X\n", dwt_readdevid() );
#endif

    return( 0 );

}

int decaHalClose()
{
    return( close( decaHalFd ) );
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


    ioctl( decaHalFd,  DRONE_IOCTL_DW1000_CS_ASSERT );
    cnt = write( decaHalFd, headerBuffer, (int)headerLength );
    cnt = read( decaHalFd, readBuffer, readlength );
    ioctl( decaHalFd, DRONE_IOCTL_DW1000_CS_CLEAR );

    return( 0 );
}

int writetospi(uint16 headerLength, const uint8 *headerBuffer, uint32 bodylength, const uint8 *bodyBuffer)
{
int cnt;

    ioctl( decaHalFd,  DRONE_IOCTL_DW1000_CS_ASSERT );
    cnt = write( decaHalFd, headerBuffer, (int)headerLength );
    cnt = write( decaHalFd, bodyBuffer, (int)bodylength );
    ioctl( decaHalFd, DRONE_IOCTL_DW1000_CS_CLEAR );

    return( 0 );
}
