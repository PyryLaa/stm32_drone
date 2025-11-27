/*
 * pid.c
 *
 *  Created on: Nov 27, 2025
 *      Author: pyryl
 */
#include "pid.h"
#include "motor_control.h"

/**
 * Clamps the given value between MIN_CCR and MAX_CCR
 *
 * @param [in:out] x: Value to be clamped
 */
uint16_t clamp(float x){
	if(x < MIN_CCR) return MIN_CCR;
	if(x > MAX_CCR) return MAX_CCR;
	return (uint16_t)x;
}

/**
 * PID function to correct given value error over time
 *
 * @param [in] pid: PID_Data_t type data structure that holds pid correction values
 * @param [in] error: Error value to correct
 * @param [in] dt: Time since last modificiation
 */
float pid(PID_Data_t* pid, float error, float dt){
	pid->integral += error * dt;
	float derivative = (error - pid->prev_error) / dt;

	float output = pid->kp * error + pid->ki * pid->integral + pid->kd * derivative;

	pid->prev_error = error;

	return output;
}
