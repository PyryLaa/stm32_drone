#ifndef COMMS_H
#define COMMS_H

#include "own_main.h"

extern UART_HandleTypeDef huart2;

void init_comms();

void message_arrived();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif // COMMS_H
