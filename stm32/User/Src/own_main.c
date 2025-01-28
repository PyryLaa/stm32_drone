#include "own_main.h"
#include "main.h"
#include <string.h>

uint8_t recv_buf[128];
uint8_t final_buf[128];
uint8_t temp;
int idx = 0;
uint8_t received = 0;

void own_main(UART_HandleTypeDef huart){

    HAL_UART_Receive_IT(&huart, &temp, 1);
    while(1){
    	if(received == 1){
    		//do something
    		received = 0;
    		HAL_UART_Receive_IT(&huart, &temp, 1);
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
		memcpy(final_buf, recv_buf, idx);
		received = 1;
		idx = 0;
	}else{
		memcpy(recv_buf + idx, &temp, 1);
		if(idx >= 128){
			idx = 0;
		} else {
			++idx;
		}
		HAL_UART_Receive_IT(huart, &temp, 1);
	}
}

