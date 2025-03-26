#include "comms.h"
#include "main.h"
#include <string.h>
#include <stdlib.h>
#include "motor_control.h"

char recv_buf[128];
char final_buf[128];
uint8_t temp;
int idx = 0;
uint8_t received = 0;

/**
 * @brief Clears communication buffers and starts receiving in UART interrupt mode
 */
void init_comms() {
	memset(recv_buf, '\0', sizeof recv_buf / sizeof recv_buf[0]);
	memset(final_buf, '\0', sizeof final_buf / sizeof final_buf[0]);
	HAL_UART_Receive_IT(&huart2, &temp, 1);
}

/**
 * @brief Run when UART rx cplt callback deems that message has arrived
 */
void message_arrived() {
	if (received == 1) {
		char* end;
		uint8_t val = strtol(final_buf + 1, &end, 10);
		motor1_pwm(val + MOTOR_PWM_CAL_VAL);
		received = 0;

		// Clear the buffers and start receiving again
		memset(recv_buf, '\0', sizeof recv_buf / sizeof recv_buf[0]);
		memset(final_buf, '\0', sizeof final_buf / sizeof final_buf[0]);
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
	received = 0;
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
		message_arrived();
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
