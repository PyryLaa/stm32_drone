#include "own_main.h"
#include "main.h"
#include "motor_control.h"
#include <string.h>

extern UART_HandleTypeDef huart2;

/**
 * @brief Own main function to keep user code separate from auto generated
 */
void own_main() {
	// Initialize communications and start receiving
	init_comms();

	// Initialize accelerometer
	LIS_Init_typedef lis_init;
	lis_init.axis_enable = LIS_XYZ_EN;
	lis_init.datarate = LIS_DATARATE_100;
	LIS_init(&lis_init);
	// Initialize timer and start pwm to motors
	pwm_setup();
	start_motors();
	motor1_pwm(60);
	motor2_pwm(60);
	motor3_pwm(60);
	motor4_pwm(60);

	float degrees[] = {0, 0};
	while (1) {
		LIS_read_pitch_roll(degrees, sizeof degrees / sizeof degrees[0]);
		float pitch = degrees[0], roll = degrees[1];
		for(uint32_t i = 0; i < 0xFFFF; ++i);
	}

}
