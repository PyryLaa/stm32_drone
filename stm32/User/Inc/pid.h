/*
 * pid.h
 *
 *  Created on: Nov 27, 2025
 *      Author: pyryl
 */

#ifndef INC_PID_H_
#define INC_PID_H_
#include <stdint.h>

typedef struct{
	float kp, ki, kd;
	float prev_error;
	float integral;
}PID_Data_t;

uint16_t clamp(float x);
float pid(PID_Data_t* pid, float error, float dt);

#endif /* INC_PID_H_ */
