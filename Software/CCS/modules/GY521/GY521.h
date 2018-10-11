/*
 * GY521.h
 *
 *  Created on: May 8, 2018
 *      Author: light
 */

#ifndef MODULES_GY521_H_
#define MODULES_GY521_H_

#include <stdint.h>
#include <stdbool.h>

#include <peripheral/I2C/I2C.h>
#include "MPU6050.h"

#define MPU6050_ADDRESS                     0x68
#define RAD_TO_DEG                          (180/3.14159)

#define GYRO_SCALE_250                      0
#define GYRO_SCALE_500                      1
#define GYRO_SCALE_1000                     2
#define GYRO_SCALE_2000                     3

#define ACCEL_SCALE_2G                      0
#define ACCEL_SCALE_4G                      1
#define ACCEL_SCALE_8G                      2
#define ACCEL_SCALE_16G                     3

class GY521
{
public:
    GY521();
    virtual ~GY521();

    void init();
    void getAccel(float *accel);
    void getGyro(float *gyro);
    float getPitch();
    float getRoll();
private:
    I2C i2c;
    int16_t gyro_raw[3];
    int16_t accel_raw[3];
    uint8_t GYRO_SCALE;
    uint8_t ACCEL_SCALE;

    void updateAccel();
    void updateGyro();
};

#endif /* MODULES_GY521_H_ */
