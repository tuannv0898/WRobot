/*
 * Motors.c
 *
 *  Created on: Oct 9, 2019
 *      Author: 16138
 */
#include <stdlib.h>
#include "Motors.h"

#include "tim.h"
#include "gpio.h"

void motors_init(){
	HAL_TIM_PWM_Start(&MOTOR0_TIMER, MOTOR0_CHANNEL);
	HAL_TIM_PWM_Start(&MOTOR1_TIMER, MOTOR1_CHANNEL);

	HAL_GPIO_WritePin(MOTOR0_DIR_GPIO_Port, MOTOR0_DIR_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, GPIO_PIN_SET);
	__HAL_TIM_SET_COMPARE(&MOTOR0_TIMER, MOTOR0_CHANNEL, 999);
	__HAL_TIM_SET_COMPARE(&MOTOR1_TIMER, MOTOR1_CHANNEL, 999);

//	HAL_GPIO_WritePin(MOTORS_EN0_GPIO_Port, MOTORS_EN0_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(MOTORS_EN1_GPIO_Port, MOTORS_EN1_Pin, GPIO_PIN_RESET);
}

void motors_deinit(){
//	HAL_GPIO_WritePin(MOTORS_EN0_GPIO_Port, MOTORS_EN0_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(MOTORS_EN1_GPIO_Port, MOTORS_EN1_Pin, GPIO_PIN_RESET);
}

void motors_setspeed(motors_t motor, int32_t speed){
	if(speed > 999) speed = 999;
	if(speed < -999) speed = -999;
	switch(motor){
	case MOTOR_0:
//		if(speed == 0){
//			HAL_GPIO_WritePin(MOTORS_EN0_GPIO_Port, MOTORS_EN0_Pin, GPIO_PIN_RESET);
//			break;
//		}
//		HAL_GPIO_WritePin(MOTORS_EN0_GPIO_Port, MOTORS_EN0_Pin, GPIO_PIN_SET);
		if(speed > 0){
#ifndef MOTOR0_INVERT
			__HAL_TIM_SET_COMPARE(&MOTOR0_TIMER, MOTOR0_CHANNEL, abs(speed));
			HAL_GPIO_WritePin(MOTOR0_DIR_GPIO_Port, MOTOR0_DIR_Pin, GPIO_PIN_RESET);
#else
			__HAL_TIM_SET_COMPARE(&MOTOR0_TIMER, MOTOR0_CHANNEL, 1000 - abs(speed));
			HAL_GPIO_WritePin(MOTOR0_DIR_GPIO_Port, MOTOR0_DIR_Pin, GPIO_PIN_SET);
#endif
		}else{
#ifndef MOTOR0_INVERT
			__HAL_TIM_SET_COMPARE(&MOTOR0_TIMER, MOTOR0_CHANNEL, 1000 - abs(speed));
			HAL_GPIO_WritePin(MOTOR0_DIR_GPIO_Port, MOTOR0_DIR_Pin, GPIO_PIN_SET);
#else
			__HAL_TIM_SET_COMPARE(&MOTOR0_TIMER, MOTOR0_CHANNEL, abs(speed));
			HAL_GPIO_WritePin(MOTOR0_DIR_GPIO_Port, MOTOR0_DIR_Pin, GPIO_PIN_RESET);
#endif
		}
		break;
	case MOTOR_1:
//		if(speed == 0){
//			HAL_GPIO_WritePin(MOTORS_EN1_GPIO_Port, MOTORS_EN1_Pin, GPIO_PIN_RESET);
//			break;
//		}
//		HAL_GPIO_WritePin(MOTORS_EN1_GPIO_Port, MOTORS_EN1_Pin, GPIO_PIN_SET);
		if(speed > 0){
#ifndef MOTOR1_INVERT
			__HAL_TIM_SET_COMPARE(&MOTOR1_TIMER, MOTOR1_CHANNEL, abs(speed));
			HAL_GPIO_WritePin(MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, GPIO_PIN_RESET);
#else
			__HAL_TIM_SET_COMPARE(&MOTOR1_TIMER, MOTOR1_CHANNEL, 1000 - abs(speed));
			HAL_GPIO_WritePin(MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, GPIO_PIN_SET);
#endif
		}else{
#ifndef MOTOR1_INVERT
			__HAL_TIM_SET_COMPARE(&MOTOR1_TIMER, MOTOR1_CHANNEL, 1000 - abs(speed));
			HAL_GPIO_WritePin(MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, GPIO_PIN_SET);
#else
			__HAL_TIM_SET_COMPARE(&MOTOR1_TIMER, MOTOR1_CHANNEL, abs(speed));
			HAL_GPIO_WritePin(MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, GPIO_PIN_RESET);
#endif
		}
		break;
	}
}
