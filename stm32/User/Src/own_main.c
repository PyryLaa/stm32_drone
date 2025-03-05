#include "own_main.h"
#include "main.h"
#include "motor_control.h"
#include <string.h>

char recv_buf[128];
char final_buf[128];
uint8_t temp;
int idx = 0;
uint8_t received = 0;
extern UART_HandleTypeDef huart2;


/**
 * @brief Own main function to keep user code separate from auto generated
 */
void own_main() {

	// Initialize timer and start pwm to motors
	pwm_setup();
	start_motors();

	// Communication code, will be moved and refactored later
	HAL_UART_Receive_IT(&huart2, &temp, 1);
	while (1) {
		if (received == 1) {
			if (strcmp(final_buf + 1, "blue") == 0) {
				GPIOD->ODR = 0;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
			} else if (strcmp(final_buf + 1, "red") == 0) {
				GPIOD->ODR = 0;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
			} else if (strcmp(final_buf + 1, "orange") == 0) {
				GPIOD->ODR = 0;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
			} else if (strcmp(final_buf + 1, "green") == 0) {
				GPIOD->ODR = 0;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
			}
			received = 0;

			// Clear the buffers and start receiving again
			memset(recv_buf, '\0', sizeof recv_buf / sizeof recv_buf[0]);
			memset(final_buf, '\0', sizeof final_buf / sizeof final_buf[0]);
			HAL_UART_Receive_IT(&huart2, &temp, 1);
		}
	}

}

/**
 * @brief UART receive complete callback
 *
 * UART data is received one byte at a time, with a maximum of 128 bytes.
 * When data is received, it is copied into recv_buf. The temp buf is checked for
 * '}' which means that the message has ended.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (temp == '}') {
		/* Copy the end character '}' to receive buffer, then copy receive buffer to
		   final buffer and null terminate it */
		memcpy(recv_buf + idx, &temp, 1);
		memcpy(final_buf, recv_buf, idx);
		final_buf[idx + 1] = '\0';
		received = 1;
		idx = 0;
	} else {
		memcpy(recv_buf + idx, &temp, 1);
		if (idx >= 127) { //Leave room for null termination
			idx = 0;
		} else {
			++idx;
		}
		HAL_UART_Receive_IT(huart, &temp, 1);
	}
}
