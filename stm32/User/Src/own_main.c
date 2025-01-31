#include "own_main.h"
#include "main.h"
#include <string.h>

char recv_buf[128];
char final_buf[128];
uint8_t temp;
int idx = 0;
uint8_t received = 0;

void own_main(UART_HandleTypeDef* huart){

    HAL_UART_Receive_IT(huart, &temp, 1);
    while(1){
    	if(received == 1){
    		if(strcmp(final_buf + 1, "blue") == 0){
    			GPIOD->ODR = 0;
    			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
    		}else if(strcmp(final_buf + 1, "red") == 0){
    			GPIOD->ODR = 0;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
    		}else if(strcmp(final_buf + 1, "orange") == 0){
    			GPIOD->ODR = 0;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
    		}else if(strcmp(final_buf + 1, "green") == 0){
    			GPIOD->ODR = 0;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
    		}
    		received = 0;
    		HAL_UART_Receive_IT(huart, &temp, 1);
    		memset(recv_buf, '\0', sizeof recv_buf / sizeof recv_buf[0]);
    		memset(final_buf, '\0', sizeof final_buf / sizeof final_buf[0]);

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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
	if(temp == '}'){
		memcpy(recv_buf + idx, &temp, 1);
		memcpy(final_buf, recv_buf, idx);
		final_buf[idx + 1] = '\0';
		received = 1;
		idx = 0;
	}else{
		memcpy(recv_buf + idx, &temp, 1);
		if(idx >= 127){ //Leave room for null termination
			idx = 0;
		} else {
			++idx;
		}
		HAL_UART_Receive_IT(huart, &temp, 1);
	}
}
