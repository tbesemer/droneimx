
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/ioport.h>
#include <linux/fcntl.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/spinlock.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/semaphore.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/initval.h>
#include <sound/soc.h>

#include <linux/spi/spi.h>

#include <util_driver.h>

#define	DEBUG_MSGS

/*  External References.
 */
extern void spi_imx_csFlagEnable( struct spi_device *spi );
extern void spi_imx_csFlagDisable( struct spi_device *spi );


/*  SPI Usage.
 */
static int  util_spi_probe( struct spi_device *spi );

#define NUM_SPI_DEVICES	1
#define SPI_DEV_INVALID	0
#define SPI_DEV_VALID	1

struct DRONE_SPI_DEVICE_PRIVATE {

        int 			valid_flag;
        int 			minor_num;
        char    		modalias[ SPI_NAME_SIZE ];
	struct spi_driver 	util_spi_driver;
        struct spi_device       *spi;
};


static struct DRONE_SPI_DEVICE_PRIVATE spiDevices[ NUM_SPI_DEVICES ] = {

    {
        .valid_flag = SPI_DEV_VALID,
        .minor_num = 0,
	.modalias = "drone_spi1",
	.spi = NULL,
	.util_spi_driver.driver = {
	    .name = "drone_spi1",
	    .owner = THIS_MODULE,
	},
        .util_spi_driver.probe = util_spi_probe,
    },

};


static int  util_spi_init(void)
{
int spi_dev, rc;

    for( spi_dev = 0; spi_dev < NUM_SPI_DEVICES; spi_dev++ ) {
	if( spiDevices[ spi_dev ].valid_flag == SPI_DEV_VALID ) {
            rc = spi_register_driver( &spiDevices[ spi_dev ].util_spi_driver );
	    if( rc != 0 ) {
		printk( "util_spi_init(): Register of %s failed\n",
			spiDevices[ spi_dev ].util_spi_driver.driver.name );
	    }
	}
    }
    
    return( 0 );
}

static int  util_spi_probe( struct spi_device *spi )
{
int spi_dev;

    spi->max_speed_hz = 20000;
    spi->bits_per_word = 32;
    spi_setup( spi );

printk( "util_spi_probe(): spi->modalias == %s\n", spi->modalias );

    for( spi_dev = 0; spi_dev < NUM_SPI_DEVICES; spi_dev++ ) {
        if( !strcmp( spi->modalias, spiDevices[ spi_dev ].modalias) ) {
	    spiDevices[ spi_dev ].spi = spi;
	    break;
	}
    }

    return( 0 );
}

static void util_spi_remove( void )
{
int spi_dev;

    for( spi_dev = 0; spi_dev < NUM_SPI_DEVICES; spi_dev++ ) {
	if( spiDevices[ spi_dev ].spi ) {
	    printk( "util_spi_remove(): Removing %d\n", spi_dev );
	    spi_unregister_driver( &spiDevices[ spi_dev ].util_spi_driver );
	}
    }
}

static int util_spi_ioctl( int minor, int cmd, unsigned long arg )
{
struct spi_device  *spi;

    printk( "util_spi_ioctl(): Minor = %d, cmd = 0x%04X, arg = %d\n", minor, cmd, (int)arg );

    if( (minor < 0) || (minor >= NUM_SPI_DEVICES) ) {
	printk( "util_spi_ioctl(): Invalid Minor %d\n", minor );
 	return( -EINVAL );
    }

    if( spiDevices[ minor ].valid_flag == SPI_DEV_INVALID ) {
	printk( "util_spi_ioctl(): Minor %d, Device %s not Active\n",
		minor, spiDevices[ minor ].modalias );
 	return( -EINVAL );
    } else {
	spi = spiDevices[ minor ].spi;
    }


    switch( cmd ) {

	case DRONE_IOCTL_SET_32_BIT_WORDS:
#ifdef	DEBUG_MSGS
	    printk( "util_spi_ioctl(): Setting 32 Bit Words on %s\n",
			 spiDevices[ minor ].modalias );
#endif

            spi->bits_per_word = 32;
            spi_setup( spi );
	    break;

	case DRONE_IOCTL_SET_16_BIT_WORDS:
#ifdef	DEBUG_MSGS
	    printk( "util_spi_ioctl(): Setting 16 Bit Words on %s\n",
			 spiDevices[ minor ].modalias );
#endif

            spi->bits_per_word = 16;
            spi_setup( spi );
	    break;

	case DRONE_IOCTL_SET_8_BIT_WORDS:
#ifdef	DEBUG_MSGS
	    printk( "util_spi_ioctl(): Setting 8 Bit Words on %s\n",
			 spiDevices[ minor ].modalias );
#endif

            spi->bits_per_word = 8;
            spi_setup( spi );
	    break;

	case DRONE_IOCTL_SET_MODE_0:
#ifdef	DEBUG_MSGS
	    printk( "util_spi_ioctl(): Setting Mode 0%s\n",
			 spiDevices[ minor ].modalias );
#endif
            spi->mode = SPI_MODE_0;
            spi_setup( spi );
	    break;

	case DRONE_IOCTL_SET_MODE_1:
#ifdef	DEBUG_MSGS
	    printk( "util_spi_ioctl(): Setting Mode 1%s\n",
			 spiDevices[ minor ].modalias );
#endif
            spi->mode = SPI_MODE_1;
            spi_setup( spi );
	    break;

	case DRONE_IOCTL_SET_MODE_2:
#ifdef	DEBUG_MSGS
	    printk( "util_spi_ioctl(): Setting Mode 2%s\n",
			 spiDevices[ minor ].modalias );
#endif
            spi->mode = SPI_MODE_2;
            spi_setup( spi );
	    break;

	case DRONE_IOCTL_SET_MODE_3:
#ifdef	DEBUG_MSGS
	    printk( "util_spi_ioctl(): Setting Mode 3%s\n",
			 spiDevices[ minor ].modalias );
#endif
            spi->mode = SPI_MODE_3;
            spi_setup( spi );
	    break;

	case DRONE_IOCTL_SET_RATE:
#ifdef	DEBUG_MSGS
	    printk( "util_spi_ioctl(): Setting Rate %d on%s\n",
			 (int)arg, spiDevices[ minor ].modalias );
#endif
            spi->max_speed_hz = (u32)arg;
            spi_setup( spi );
	    break;

	case DRONE_IOCTL_DW1000_CS_ASSERT:
#ifdef	DEBUG_MSGS
	    printk( "util_spi_ioctl(): Asserting Chip Select\n" );
#endif
		spi_imx_csFlagEnable( spi );
	    break;
	case DRONE_IOCTL_DW1000_CS_CLEAR:
#ifdef	DEBUG_MSGS
	    printk( "util_spi_ioctl(): Clearing Chip Select\n" );
#endif
		spi_imx_csFlagDisable( spi );
	    break;

	default:
	   return( -EINVAL );

    }

    return( 0 );

}


#define DRONE_IOBUFF_SIZE 1024

static char localIoBuff[ DRONE_IOBUFF_SIZE ];

static ssize_t util_spi_write( int minor, const char __user *buf, size_t count )
{
struct spi_device  *spi;
size_t tmpCount;
int rc;

//    printk( "util_spi_write(): minor = %d, count = %d\n", minor, count );

    if( (minor < 0) || (minor >= NUM_SPI_DEVICES) ) {
	printk( "util_spi_write(): Invalid Minor %d\n", minor );
 	return( -EINVAL );
    }

    if( spiDevices[ minor ].valid_flag == SPI_DEV_INVALID ) {
	printk( "util_spi_write(): Minor %d, Device %s not Active\n",
		minor, spiDevices[ minor ].modalias );
 	return( -EINVAL );
    } else {
	spi = spiDevices[ minor ].spi;
    }

    tmpCount = count;
    while( tmpCount > 0 ) {
	if( tmpCount > DRONE_IOBUFF_SIZE ) {

	    if( copy_from_user( localIoBuff, buf, DRONE_IOBUFF_SIZE ) ) {
		printk( "util_spi_write() copy_from_user() Fault, tmpCount = %d\n", tmpCount );
		return( -EFAULT );
	    }

            rc = spi_write( spi, localIoBuff, DRONE_IOBUFF_SIZE );
            if( rc < 0 ) {
                printk( "util_spi_write(): spi_write() error\n" );
                break;
            }

	    tmpCount = (tmpCount - DRONE_IOBUFF_SIZE);

	} else {

	    if( copy_from_user( localIoBuff, buf, tmpCount ) ) {
		printk( "util_spi_write() copy_from_user() Fault, tmpCount = %d\n", tmpCount );
		return( -EFAULT );
	    }

            rc = spi_write( spi, localIoBuff, tmpCount );
            if( rc < 0 ) {
                printk( "util_spi_write(): spi_write() error\n" );
                break;
            }

	    break;
	}

    }

    return( count );

}

static ssize_t util_spi_read( int minor, char __user *buf, size_t count )
{
struct spi_device  *spi;
int rc;

    printk( "util_spi_read(): minor = %d, count = %d\n", minor, count );

    if( (minor < 0) || (minor >= NUM_SPI_DEVICES) ) {
	printk( "util_spi_read(): Invalid Minor %d\n", minor );
 	return( -EINVAL );
    }

    if( spiDevices[ minor ].valid_flag == SPI_DEV_INVALID ) {
	printk( "util_spi_read(): Minor %d, Device %s not Active\n",
		minor, spiDevices[ minor ].modalias );
 	return( -EINVAL );
    } else {
	spi = spiDevices[ minor ].spi;
    }

    if( count > DRONE_IOBUFF_SIZE ) {
	printk( "util_spi_read(): Read greater than %d no supported\n", DRONE_IOBUFF_SIZE );
 	return( -EINVAL );
    }

    rc = spi_read( spi, (void *)localIoBuff, count );
    if( rc < 0 ) {
        printk( "util_spi_read(): spi_read() error\n" );
        return( -EINVAL );
    }

    if( copy_to_user(buf, localIoBuff, count) ) {
        printk( "util_spi_read(): copy_to_user() error\n" );
 	return( -EINVAL );
    }



    return( count );

}


static ssize_t drone_util_read(struct file *file, char __user *buf,
						size_t count, loff_t *ppos)
{
unsigned int minor;

    minor = iminor( file_inode(file) );

    if( minor < NUM_SPI_DEVICES ) {
	return( util_spi_read( minor, buf, count ) );
    }

    return 0;

}

static ssize_t drone_util_write(struct file *file, const char __user *buf,
						size_t count, loff_t *ppos)
{
unsigned int minor;

    minor = iminor( file_inode(file) );

    if( minor < NUM_SPI_DEVICES ) {
	return( util_spi_write( minor, buf, count ) );
    }

    return 0;
}


static long drone_util_ioctl(struct file *file, unsigned int cmd,
			unsigned long arg)
{
unsigned int minor;


    minor = iminor( file_inode(file) );

    if( minor < NUM_SPI_DEVICES ) {
	return( util_spi_ioctl( minor, cmd, arg ) );
    }

    switch (cmd) {
	default:
	   return( -EINVAL );
    }

    return( 0 );
}

static int drone_util_open(struct inode *inode, struct file *file)
{

	return 0;
}

static int drone_util_release(struct inode *inode, struct file *file)
{

	return 0;
}


static const struct file_operations drone_util_fops = {
	.owner		= THIS_MODULE,
	.read		= drone_util_read,
	.write		= drone_util_write,
	.unlocked_ioctl	= drone_util_ioctl,
	.open		= drone_util_open,
	.release	= drone_util_release,
};

static int __init drone_util_init(void)
{
	int ret;

	ret = register_chrdev( 40, "drone_util", &drone_util_fops );
	if( ret < 0 ) {
	    printk( "drone_util_init(): registr_chrdev() failed\n" );
	    return( 0 );
	}

	printk( "drone_util_init(): SPI Initialization\n" );

	ret = util_spi_init();
	if( ret < 0 ) {
	    printk( "drone_util_init(): util_spi_init() failed\n" );
	    return( 0 );
	}

	return 0;
}

static void __exit drone_util_cleanup_module(void)
{
int ret;
 
    util_spi_remove();
    unregister_chrdev( 40, "drone_util" );

}

module_init(drone_util_init);
module_exit(drone_util_cleanup_module);

MODULE_LICENSE("GPL");
MODULE_ALIAS_MISCDEV(0);

