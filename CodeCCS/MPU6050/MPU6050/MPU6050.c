#include "MPU6050.h"

#define MPU6050_SMPLRT_DIV                  0x19
#define MPU6050_INT_PIN_CFG                 0x37
#define MPU6050_ACCEL_XOUT_H                0x3B
#define MPU6050_GYRO_XOUT_H                 0x43
#define MPU6050_PWR_MGMT_1                  0x6B
#define MPU6050_WHO_AM_I                    0x75

#define MPU6050_ADDRESS                     0x68
#define MPU6050_WHO_AM_I_ID                 0x68

#define RAD_TO_DEG                          (180/3.14159)

int16_t accel_raw[3], gyro_raw[3];
float pitch, roll;

float Kalman(float newAngle, float newRate);

void MPU6050_Init(void) {

    I2C_Init();

    //MPU6050 configure
    uint8_t i2cBuffer[5]; // Buffer for I2C data
    i2cBuffer[0] = I2C_Read(MPU6050_ADDRESS, MPU6050_WHO_AM_I);
    I2C_Write(MPU6050_ADDRESS, MPU6050_PWR_MGMT_1, (1 << 7)); // Reset device, this resets all internal registers to their default values
    SysCtlDelay(SysCtlClockGet()/100);
    while (I2C_Read(MPU6050_ADDRESS, MPU6050_PWR_MGMT_1) & (1 << 7)) ;
    SysCtlDelay(SysCtlClockGet()/100);
    I2C_Write(MPU6050_ADDRESS, MPU6050_PWR_MGMT_1, (1 << 3) | (1 << 0)); // Disable sleep mode, disable temperature sensor and use PLL as clock reference

    i2cBuffer[0] = 0; // Set the sample rate to 1kHz - 1kHz/(1+0) = 1kHz
    i2cBuffer[1] = 0x03; // Disable FSYNC and set 41 Hz Gyro filtering, 1 KHz sampling
    i2cBuffer[2] = 3 << 3; // Set Gyro Full Scale Range to +-2000deg/s
    i2cBuffer[3] = 2 << 3; // Set Accelerometer Full Scale Range to +-8g
    i2cBuffer[4] = 0x03; // 41 Hz Acc filtering
    I2C_Write_Data(MPU6050_ADDRESS, MPU6050_SMPLRT_DIV, i2cBuffer, 5); // Write to all five registers at once

    /* Enable Raw Data Ready Interrupt on INT pin */
    i2cBuffer[0] = (1 << 5) | (1 << 4); // Enable LATCH_INT_EN and INT_ANYRD_2CLEAR
    // When this bit is equal to 1, the INT pin is held high until the interrupt is cleared
    // When this bit is equal to 1, interrupt status is cleared if any read operation is performed
    i2cBuffer[1] = (1 << 0);            // Enable RAW_RDY_EN - When set to 1, Enable Raw Sensor Data Ready interrupt to propagate to interrupt pin
    I2C_Write_Data(MPU6050_ADDRESS, MPU6050_INT_PIN_CFG, i2cBuffer, 2); // Write to both registers at once
    SysCtlDelay(200);

}

void MPU6050_Update_Accel_Raw() {
    uint8_t buf[6];
    I2C_Read_Data(MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_H, buf, 6); // Note that we can't write directly into MPU6050_t, because of endian conflict. So it has to be done manually

    accel_raw[0] = (buf[0] << 8) | buf[1];
    accel_raw[1] = (buf[2] << 8) | buf[3];
    accel_raw[2] = (buf[4] << 8) | buf[5];
}

void MPU6050_Update_Gyro_Raw() {
    uint8_t buf[6];
    I2C_Read_Data(MPU6050_ADDRESS, MPU6050_GYRO_XOUT_H, buf, 6); // Note that we can't write directly into MPU6050_t, because of endian conflict. So it has to be done manually

    gyro_raw[0] = (buf[0] << 8) | buf[1];
    gyro_raw[1] = (buf[2] << 8) | buf[3];
    gyro_raw[2] = (buf[4] << 8) | buf[5];
}

float MPU6050_Get_Pitch(void){
    MPU6050_Update_Accel_Raw();
    pitch = atan2(-accel_raw[0], accel_raw[2]) * RAD_TO_DEG;
    return pitch;
}

float MPU6050_Get_Roll(void){
    MPU6050_Update_Accel_Raw();
    roll = atan2(-accel_raw[1], accel_raw[2]) * RAD_TO_DEG;
    return roll;
}

float dt = 0.1; // T Sampling
float Q_angle = 0.005;
float Q_bias = 0.003;
float R_measure = 0.03;
float bias = 0; // Reset bias
float rate;
float angle;
float S; // estimate error
float y; // different angle
float P_00 = 0 , P_01 = 0 , P_10 =0 ,P_11 =0;
float K_0 =0,K_1=0; // Kalman gain

float MPU6050_Get_Filtered_Pitch(){
    float filtered_pitch;
    filtered_pitch = Kalman(MPU6050_Get_Pitch(), 0);
    return filtered_pitch;
}



float Kalman(float newAngle, float newRate){

    // Discrete Kalman filter time update equations - Time Update ("Predict")
    // Update xhat - Project the state ahead
    /* Step 1 */
    //angle = X_Raw_Gyro_Angle;
    rate = newRate - bias;
    angle += dt * rate;

    // Update estimation error covariance - Project the error covariance ahead
    /* Step 2 */
    P_00 += dt * ( dt*P_11 - P_10 - P_01 + Q_angle);
    P_01 -= dt * P_11;
    P_10 -= dt * P_11;
    P_11 += Q_bias * dt;

    // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
    // Calculate Kalman gain - Compute the Kalman gain
    /* Step 4 */
    S = P_00 + R_measure;
    /* Step 5 */
    K_0 = P_00 / S;
    K_1 = P_10 / S;

    // Calculate angle and bias - Update estimate with measurement zk (newAngle)
    /* Step 3 */
    y = newAngle - angle;
    /* Step 6 */
    angle += K_0 * y;
    bias += K_1 * y;

    // Calculate estimation error covariance - Update the error covariance
    /* Step 7 */
    P_00 -= K_0 * P_00;
    P_01 -= K_0 * P_01;
    P_10 -= K_1 * P_00;
    P_11 -= K_1 * P_01;

    return angle;
}


