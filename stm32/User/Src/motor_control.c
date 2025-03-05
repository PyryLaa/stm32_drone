#include "motor_control.h"

/**
 * @brief This function will setup TIM1 PWM output
 *
 * TIM1 is used for PWM output to motors since it has 4
 * independent channels that can output different PWM signals.
 * Time will be initialized here
 */
void pwm_setup() {
	TIM1->PSC = TIM_PRESCALER_VAL; // APB2 clock at 84MHz, want timer to count with 1MHz
	TIM1->ARR = TIM_ARR_VAL; // PWM frequency to 10kHz

	// Make every channel's duty cycle 50% for default
	TIM1->CCR1 = TIM_CH1_DEFAULT_CCR;
	TIM1->CCR2 = TIM_CH2_DEFAULT_CCR;
	TIM1->CCR3 = TIM_CH3_DEFAULT_CCR;
	TIM1->CCR4 = TIM_CH4_DEFAULT_CCR;
}

void start_motors() {
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
}

void motor1_pwm(uint16_t new_duty) {
	if (new_duty < TIM_CH1_MIN_CCR) {
		TIM1->CCR1 = TIM_CH1_MIN_CCR;
	} else {
		TIM1->CCR1 = new_duty;
	}
}

void motor2_pwm(uint16_t new_duty) {
	if (new_duty < TIM_CH1_MIN_CCR) {
		TIM1->CCR2 = TIM_CH1_MIN_CCR;
	} else {
		TIM1->CCR2 = new_duty;
	}
}

void motor3_pwm(uint16_t new_duty) {
	if (new_duty < TIM_CH1_MIN_CCR) {
		TIM1->CCR3 = TIM_CH1_MIN_CCR;
	} else {
		TIM1->CCR3 = new_duty;
	}
}

void motor4_pwm(uint16_t new_duty) {
	if (new_duty < TIM_CH1_MIN_CCR) {
		TIM1->CCR4 = TIM_CH1_MIN_CCR;
	} else {
		TIM1->CCR4 = new_duty;
	}
}

