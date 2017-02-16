#ifndef __UTIL_DRIVER__
#define __UTIL_DRIVER__

#define DRONE_IOCTL_BASE 0x89F0

typedef enum {

        /*  SPI Operations.
         */
        DRONE_IOCTL_SET_32_BIT_WORDS = DRONE_IOCTL_BASE,
        DRONE_IOCTL_SET_16_BIT_WORDS,
        DRONE_IOCTL_SET_8_BIT_WORDS,
        DRONE_IOCTL_SET_MODE_0,
        DRONE_IOCTL_SET_MODE_1,
        DRONE_IOCTL_SET_MODE_2,
        DRONE_IOCTL_SET_MODE_3,
        DRONE_IOCTL_SET_RATE,

} DRONE_UTIL_IOCTLS;


#endif

