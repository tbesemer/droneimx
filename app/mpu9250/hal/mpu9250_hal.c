
#include        <fcntl.h>
#include        <stdio.h>
#include        <string.h>
#include        <stdlib.h>
#include        <sys/types.h>
#include        <sys/stat.h>
#include        <fcntl.h>
#include        <sys/mman.h>
#include        <sys/ioctl.h>
#include        <unistd.h>

#include        <sys_types.h>
#include        <util_driver.h>
#include        "mpu9250_hal.h"

static int mpu9250_fd;

int mpu9250HalOpen()
{
int err = 0;

    mpu9250_fd = open( "/dev/spi_drone2", O_RDWR );
    if( mpu9250_fd < 0 ) {
        printf( "mpu9250(): open() failed on /dev/spi_drone2\n" );
        perror( "open error" );
        return( -1 );
    }

    err += ioctl( mpu9250_fd, DRONE_IOCTL_SET_RATE, 200000 );
    err += ioctl( mpu9250_fd, DRONE_IOCTL_SET_MODE_0 );
    err += ioctl( mpu9250_fd, DRONE_IOCTL_SET_8_BIT_WORDS );
    if( err ) {
        printf( "mpu9250(): ioctl() failed on /dev/spi_drone2\n" );
        return( -1 );
    }

    return( 0 );
}

int mpu9250HalClose()
{
    return( close( mpu9250_fd ) );
}

int mpu9250HalReadReg( int regId, uint8_t *regVal )
{
uint8_t buff[ 2 ];
int err, cnt;

    err = 0;

    err += ioctl( mpu9250_fd, DRONE_IOCTL_SS1_CS_ASSERT );
    buff[ 0 ] = (regId | 0x80);
    cnt = write( mpu9250_fd, buff, 1 );
    cnt = read( mpu9250_fd, buff, 1 );
    err += ioctl( mpu9250_fd, DRONE_IOCTL_SS1_CS_CLEAR );

    *regVal = buff[ 0 ];

    return( err );

}

int mpu9250HalReadRegMulti( int regId, uint8_t *regVals, int length )
{
uint8_t buff[ 2 ];
int err, cnt;

    err = 0;
    cnt = 0;

    err += ioctl( mpu9250_fd, DRONE_IOCTL_SS1_CS_ASSERT );
    buff[ 0 ] = (regId | 0x80);
    cnt += write( mpu9250_fd, buff, 1 );
    cnt += read( mpu9250_fd, regVals, length );
    err += ioctl( mpu9250_fd, DRONE_IOCTL_SS1_CS_CLEAR );

    if( cnt != (length + 1)) {
	printf( "mpu9250HalReadRegMulti(): write() failed\n" );
	return( -1 );
    }

    return( err );

}

int mpu9250HalReadMulti( uint8_t *regVals, int length )
{
int err, cnt;

    err = 0;
    cnt = 0;

    err += ioctl( mpu9250_fd, DRONE_IOCTL_SS1_CS_ASSERT );
    cnt += read( mpu9250_fd, regVals, length );
    err += ioctl( mpu9250_fd, DRONE_IOCTL_SS1_CS_CLEAR );

    if( cnt != length ) {
	printf( "mpu9250HalReadMulti(): read() failed\n" );
	return( -1 );
    }

    return( err );
}

int mpu9250HalWriteReg( int regId, uint8_t regVal )
{
uint8_t buff[ 2 ];
int err, cnt;

    err = 0;

    err += ioctl( mpu9250_fd, DRONE_IOCTL_SS1_CS_ASSERT );
    buff[ 0 ] = regId;
    buff[ 1 ] = regVal; 
    cnt = write( mpu9250_fd, buff, 2 );
    err += ioctl( mpu9250_fd, DRONE_IOCTL_SS1_CS_CLEAR );

    return( err );
}

int mpu9250HalWriteRegMulti( int regId, uint8_t *data, int length )
{
uint8_t buff[ 2 ];
int err, cnt;

    err = 0;
    cnt = 0;

    err += ioctl( mpu9250_fd, DRONE_IOCTL_SS1_CS_ASSERT );
    buff[ 0 ] = regId;
    cnt = write( mpu9250_fd, buff, 1 );
    if( length ) {
    	cnt += write( mpu9250_fd, data, cnt );
    }
    err += ioctl( mpu9250_fd, DRONE_IOCTL_SS1_CS_CLEAR );

    if( cnt != (length + 1)) {
	printf( "mpu9250HalWriteRegMulti(): write() failed\n" );
	return( -1 );
    }

    return( err );
}
