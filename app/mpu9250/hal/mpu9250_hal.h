#ifndef __MPC9250_HAL_H__
#define __MPC9250_HAL_H__

int mpu9250HalOpen();
int mpu9250HalClose();
int mpu9250HalReadReg( int regId, uint8_t *regVal );
int mpu9250HalWriteReg( int regId, uint8_t regVal );

#endif

