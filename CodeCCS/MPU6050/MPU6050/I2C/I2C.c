#include "I2C.h"

uint8_t pui8DataTx[8];
uint8_t pui8DataRx[8];

void pfnHandler();

void I2C_Init(void) {
    SysCtlPeripheralEnable(MPU6050_I2C); // Enable I2C1 peripheral
    SysCtlPeripheralEnable(MPU6050_I2C_GPIO); // Enable GPIOA peripheral
    while(!SysCtlPeripheralReady(MPU6050_I2C) || !SysCtlPeripheralReady(MPU6050_I2C_GPIO));

    // Use alternate pin function
    GPIOPinConfigure(MPU6050_I2C_SCL);
    GPIOPinConfigure(MPU6050_I2C_SDA);
    GPIOPinTypeI2CSCL(MPU6050_I2C_GPIO_BASE, MPU6050_GPIO_SCL); // Use pin with I2C SCL peripheral
    GPIOPinTypeI2C(MPU6050_I2C_GPIO_BASE, MPU6050_GPIO_SDA); // Use pin with I2C peripheral

//

    I2CIntRegister(MPU6050_I2C_BASE, pfnHandler);
    I2CMasterIntEnableEx(MPU6050_I2C_BASE, I2C_MASTER_INT_STOP);
    I2CMasterIntEnable(MPU6050_I2C_BASE);
//
//    I2CTxFIFOConfigSet(MPU6050_I2C_BASE, I2C_FIFO_CFG_TX_MASTER|I2C_FIFO_CFG_TX_TRIG_8);
//    I2CRxFIFOConfigSet(MPU6050_I2C_BASE, I2C_FIFO_CFG_RX_MASTER|I2C_FIFO_CFG_RX_TRIG_8);

    I2CMasterInitExpClk(MPU6050_I2C_BASE, SysCtlClockGet(), true); // Enable and set frequency to 400 kHz

    SysCtlDelay(200); // Insert a few cycles after enabling the I2C to allow the clock to be fully activated
}

void pfnHandler(){
    I2CFIFODataGetNonBlocking(MPU6050_I2C_BASE, pui8DataRx);
    I2CMasterIntClear(MPU6050_I2C_BASE);
}

void I2C_Write_Data(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length) {
    I2CMasterSlaveAddrSet(MPU6050_I2C_BASE, addr, false); // Set to write mode

    I2CMasterDataPut(MPU6050_I2C_BASE, regAddr); // Place address into data register
    I2CMasterControl(MPU6050_I2C_BASE, I2C_MASTER_CMD_BURST_SEND_START); // Send start condition
    while (I2CMasterBusy(MPU6050_I2C_BASE)); // Wait until transfer is done

    uint8_t i = 0;
    for (i = 0; i < length - 1; i++) {
        I2CMasterDataPut(MPU6050_I2C_BASE, data[i]); // Place data into data register
        I2CMasterControl(MPU6050_I2C_BASE, I2C_MASTER_CMD_BURST_SEND_CONT); // Send continues condition
        while (I2CMasterBusy(MPU6050_I2C_BASE)); // Wait until transfer is done
    }

    I2CMasterDataPut(MPU6050_I2C_BASE, data[length - 1]); // Place data into data register
    I2CMasterControl(MPU6050_I2C_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH); // Send finish condition
    while (I2CMasterBusy(MPU6050_I2C_BASE)); // Wait until transfer is done
}

void I2C_Write(uint8_t addr, uint8_t regAddr, uint8_t data) {

    I2CMasterSlaveAddrSet(MPU6050_I2C_BASE, addr, false); // Set to write mode
    I2CMasterDataPut(MPU6050_I2C_BASE, regAddr); // Place address into data register
    I2CMasterControl(MPU6050_I2C_BASE, I2C_MASTER_CMD_BURST_SEND_START); // Send start condition
    while (I2CMasterBusy(MPU6050_I2C_BASE)); // Wait until transfer is done

    I2CMasterDataPut(MPU6050_I2C_BASE, data); // Place data into data register
    I2CMasterControl(MPU6050_I2C_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH); // Send finish condition
    while (I2CMasterBusy(MPU6050_I2C_BASE)); // Wait until transfer is done

}

void I2C_Read_Data(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length) {
    I2CMasterSlaveAddrSet(MPU6050_I2C_BASE, addr, false); // Set to write mode

    I2CMasterDataPut(MPU6050_I2C_BASE, regAddr); // Place address into data register
    I2CMasterControl(MPU6050_I2C_BASE, I2C_MASTER_CMD_SINGLE_SEND); // Send data
    while (I2CMasterBusy(MPU6050_I2C_BASE)); // Wait until transfer is done

    I2CMasterSlaveAddrSet(MPU6050_I2C_BASE, addr, true); // Set to read mode

    I2CMasterControl(MPU6050_I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START); // Send start condition
    while (I2CMasterBusy(MPU6050_I2C_BASE)); // Wait until transfer is done

    data[0] = I2CMasterDataGet(MPU6050_I2C_BASE); // Place data into data register
    uint8_t i = 1;
    for (i = 1; i < length - 1; i++) {
        I2CMasterControl(MPU6050_I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT); // Send continues condition
        while (I2CMasterBusy(MPU6050_I2C_BASE)); // Wait until transfer is done
        data[i] = I2CMasterDataGet(MPU6050_I2C_BASE); // Place data into data register
    }

    I2CMasterControl(MPU6050_I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH); // Send finish condition
    while (I2CMasterBusy(MPU6050_I2C_BASE)); // Wait until transfer is done
    data[length - 1] = I2CMasterDataGet(MPU6050_I2C_BASE); // Place data into data register
}

uint8_t I2C_Read(uint8_t addr, uint8_t regAddr) {
    I2CMasterSlaveAddrSet(MPU6050_I2C_BASE, addr, false); // Set to write mode

    I2CMasterDataPut(MPU6050_I2C_BASE, regAddr); // Place address into data register
    I2CMasterControl(MPU6050_I2C_BASE, I2C_MASTER_CMD_SINGLE_SEND); // Send data
    while (I2CMasterBusy(MPU6050_I2C_BASE)); // Wait until transfer is done

    I2CMasterSlaveAddrSet(MPU6050_I2C_BASE, addr, true); // Set to read mode
    I2CMasterControl(MPU6050_I2C_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE); // Tell master to read data
    while (I2CMasterBusy(MPU6050_I2C_BASE)); // Wait until transfer is done
    return I2CMasterDataGet(MPU6050_I2C_BASE); // Read data
}
