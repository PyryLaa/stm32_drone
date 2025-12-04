#include "own_main.h"
#include "main.h"
#include "motor_control.h"
#include "gyro.h"
#include "pid.h"
#include <string.h>

extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;
float gyro_x = 0, gyro_y = 0, gyro_z = 0;
float real_pitch = 0, real_roll = 0, gyro_roll = 0, gyro_pitch = 0;
uint8_t user_throttle_percent = 0;
uint8_t pid_counter = 0;
float initial_acc_pitch = 0.0, initial_acc_roll = 0.0, initial_gyro_x = 0.0, initial_gyro_y = 0.0, initial_gyro_z = 0.0;
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
	gyro_setup(&hi2c1);
	// Initialize timer and start pwm to motors
	pwm_setup();
	start_motors();
	motor1_pwm(100);
	motor2_pwm(100);
	motor3_pwm(100);
	motor4_pwm(100);

	float degrees[] = {0, 0};

	uint32_t last_time = HAL_GetTick();
	float alpha = 0.98;
	float dt = 0.0; // Used for integration, delta time
	PID_Data_t pid_pitch = { .kp = 2.0f, .ki = 0.0f, .kd = 0.8f };
	PID_Data_t pid_roll  = { .kp = 2.0f, .ki = 0.0f, .kd = 0.8f };
	float base = 130;
	read_initial_values();
	while (1) {
		// Base value that would be written to CCR registers, will be modified with pid
		if(user_throttle_percent > 10){
			base = MIN_CCR + (user_throttle_percent / 100.0f) * (MAX_CCR - MIN_CCR);
			LIS_read_pitch_roll(degrees, sizeof degrees / sizeof degrees[0]);
			gyro_read(&gyro_x, &gyro_y, &gyro_z, &hi2c1);
			float acc_pitch = degrees[0] - initial_acc_pitch, acc_roll = degrees[1] - initial_acc_roll;
			uint32_t now = HAL_GetTick();
			dt = (now - last_time) / 1000.0f;
			last_time = now;

			// Integrate gyro
			gyro_roll = real_roll + (gyro_y - initial_gyro_y) * dt;
			gyro_pitch = real_pitch + (gyro_x - initial_gyro_x) * dt;

			// Filter
			real_pitch = alpha * gyro_pitch + (1.0f - alpha) * acc_pitch;
			real_roll = alpha * gyro_roll + (1.0f - alpha) * acc_roll;

			float pitch_err = -real_pitch;
			float roll_err = -real_roll;

			// Pid correct pitch and roll values
			float pitch_output = pid(&pid_pitch, pitch_err, dt);
			float roll_output  = pid(&pid_roll,  roll_err,  dt);

			// Get CCR value
			float m1 = base + pitch_output + roll_output;
			float m2 = base + pitch_output - roll_output;
			float m3 = base - pitch_output + roll_output;
			float m4 = base - pitch_output - roll_output;
			if(++pid_counter == 4){ // Don't update motors every loop
				motor1_pwm(clamp(m1));
				motor2_pwm(clamp(m2));
				motor3_pwm(clamp(m3));
				motor4_pwm(clamp(m4));
				pid_counter = 0;
			}
			HAL_Delay(5); // Small delay before running pid loop again
		} else {
			motor1_pwm(100);
			motor2_pwm(100);
			motor3_pwm(100);
			motor4_pwm(100);

		}

	}

}

void read_initial_values(){
	float buf[] = {0.0, 0.0};
	LIS_read_pitch_roll(buf, sizeof buf / sizeof buf[0]);

	gyro_read(&initial_gyro_x, &initial_gyro_y, &initial_gyro_z, &hi2c1);
	initial_acc_pitch = buf[0], initial_acc_roll = buf[1];
}
