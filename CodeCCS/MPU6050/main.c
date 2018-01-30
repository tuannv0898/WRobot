#include <stdint.h>
#include <stdbool.h>

#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_gpio.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/adc.h"
#include "driverlib/sysctl.h"

#include "driverlib/sysctl.h"

#include "MPU6050/MPU6050.h"
#include "UART0/UART.h"

float x,y;

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    IntMasterEnable();

    MPU6050_Init();
    UART_Start();

    while(1){
        x = MPU6050_Get_Filtered_Pitch();
        UARTprintf("-100,%d,%d,100\r\n",(int)x,(int)MPU6050_Get_Pitch());
        SysCtlDelay(50000);
    }
}
