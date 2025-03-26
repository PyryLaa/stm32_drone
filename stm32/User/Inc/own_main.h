#ifndef OWN_MAIN_H
#define OWN_MAIN_H

#include "stm32f4xx.h"
#include "comms.h"
#include "lis_acc.h"

void own_main();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif //OWN_MAIN_H
