
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 200000;
static uint16_t delay = 0;

static int spiFd;

int rpiSpiXfer( int fd, char *txBuff, char *rxBuff, int cnt )
{
int ret;

    struct spi_ioc_transfer tr = {
	.tx_buf = (unsigned long)txBuff,
	.rx_buf = (unsigned long)rxBuff,
	.len = cnt,
	.delay_usecs = delay,
	.speed_hz = speed,
	.bits_per_word = bits,
    };

    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if( ret < 0 ) {
	printf( "rpiSpiXfer(): ioctl() failed\n" );
	perror( "rpiSpiXfer(): ioctl(): " );
	return( -1 );
    }

    return( 0 );
}


int rpSpiOpen( char *spiDev )
{

int ret = 0;

    spiFd = open( spiDev, O_RDWR );
    if( spiFd < 0 ) {
        printf( "rpSpiOpen(): open() failed on %s\n", spiDev );
        perror( "open error" );
        return( -1 );
    }

    ret += ioctl( spiFd, SPI_IOC_WR_MODE, &mode );
    ret += ioctl( spiFd, SPI_IOC_RD_MODE, &mode );
    ret += ioctl( spiFd, SPI_IOC_WR_BITS_PER_WORD, &bits );
    ret += ioctl( spiFd, SPI_IOC_RD_BITS_PER_WORD, &bits );
    ret += ioctl( spiFd, SPI_IOC_WR_MAX_SPEED_HZ, &speed );
    ret += ioctl( spiFd, SPI_IOC_RD_MAX_SPEED_HZ, &speed );
    if( ret < 0 ) {
        printf( "rpSpiOpen(): ioctl() failed on %s\n", spiDev );
        perror( "ioctl error" );
        return( -1 );
    }

    return( spiFd );
}

char txBuff[ 255 ];
char rxBuff[ 255 ];

main()
{
int fd;

    txBuff[ 0 ] = 0x80 | 0x75;

    fd = rpSpiOpen( "/dev/spidev0.0" ); 
    rpiSpiXfer( fd, txBuff, rxBuff, 2 );

    printf( "0x%02X, 0x%02X\n", rxBuff[ 0 ], rxBuff[ 1 ] );

}
