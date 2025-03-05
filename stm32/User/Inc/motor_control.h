#include "own_main.h"

// Timer 1 PWM register values
#define TIM_PRESCALER_VAL 84-1 // Prescaler value will be PSC+1
#define TIM_ARR_VAL 100

// Default CCR register values, adjusted as needed
#define TIM_CH1_DEFAULT_CCR 50
#define TIM_CH2_DEFAULT_CCR 50
#define TIM_CH3_DEFAULT_CCR 50
#define TIM_CH4_DEFAULT_CCR 50

// Minimum CCR values, adjusted as needed
#define TIM_CH1_MIN_CCR 10
#define TIM_CH2_MIN_CCR 10
#define TIM_CH3_MIN_CCR 10
#define TIM_CH4_MIN_CCR 10

// Timer handle for PWM timer
extern TIM_HandleTypeDef htim1;

void pwm_setup();
void start_motors();

void motor1_pwm(uint16_t new_duty);
void motor2_pwm(uint16_t new_duty);
void motor3_pwm(uint16_t new_duty);
void motor4_pwm(uint16_t new_duty);
