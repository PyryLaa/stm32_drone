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

/**
 * @brief Will start PWM generation on 4 TIM1 channels
 */
void start_motors() {
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	//TIM1->CCR1 = PWM_HIGH_CYCLE_VAL;
	//calibrate_esc();
}

/*void calibrate_esc() {
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
	HAL_Delay(4000);
	TIM1->CCR1 = PWM_LOW_CYCLE_VAL;
	HAL_Delay(2000);
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
	TIM1->CCR1 = PWM_HIGH_CYCLE_VAL - 25;
}*/

/**
 * @brief Changes the CCR value (duty cycle) of TIM1 channel 1
 *
 * @param[in] new_duty The value that will be written to CCRx to
 * 			  achieve desired duty cycle. If less than set minimum,
 * 			  minimum value will be written instead
 */
void motor1_pwm(uint16_t new_duty) {
	if (new_duty < TIM_CH1_MIN_CCR) {
		TIM1->CCR1 = TIM_CH1_MIN_CCR;
	} else {
		TIM1->CCR1 = new_duty;
	}
}

/**
 * @brief Changes the CCR value (duty cycle) of TIM1 channel 2
 *
 * @param[in] new_duty The value that will be written to CCRx to
 * 			  achieve desired duty cycle. If less than set minimum,
 * 			  minimum value will be written instead
 */
void motor2_pwm(uint16_t new_duty) {
	if (new_duty < TIM_CH1_MIN_CCR) {
		TIM1->CCR2 = TIM_CH1_MIN_CCR;
	} else {
		TIM1->CCR2 = new_duty;
	}
}

/**
 * @brief Changes the CCR value (duty cycle) of TIM1 channel 3
 *
 * @param[in] new_duty The value that will be written to CCRx to
 * 			  achieve desired duty cycle. If less than set minimum,
 * 			  minimum value will be written instead
 */
void motor3_pwm(uint16_t new_duty) {
	if (new_duty < TIM_CH1_MIN_CCR) {
		TIM1->CCR3 = TIM_CH1_MIN_CCR;
	} else {
		TIM1->CCR3 = new_duty;
	}
}

/**
 * @brief Changes the CCR value (duty cycle) of TIM1 channel 4
 *
 * @param[in] new_duty The value that will be written to CCRx to
 * 			  achieve desired duty cycle. If less than set minimum,
 * 			  minimum value will be written instead
 */
void motor4_pwm(uint16_t new_duty) {
	if (new_duty < TIM_CH1_MIN_CCR) {
		TIM1->CCR4 = TIM_CH1_MIN_CCR;
	} else {
		TIM1->CCR4 = new_duty;
	}
}

