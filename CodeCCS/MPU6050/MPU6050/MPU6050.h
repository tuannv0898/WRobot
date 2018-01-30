#ifndef MPU6050_H_
#define MPU6050_H_

#include "I2C/I2C.h"

void MPU6050_Init(void);
float MPU6050_Get_Pitch(void);
float MPU6050_Get_Filtered_Pitch(void);
float MPU6050_Get_Roll(void);

#endif
