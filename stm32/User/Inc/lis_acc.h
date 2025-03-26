#ifndef INC_LIS_ACC_H_
#define INC_LIS_ACC_H_

#include <stdint.h>
#include "own_main.h"

// LIS accelerometer registers
#define LIS_OUT_T_REG		0x0C
#define LIS_INFO1_REG		0x0D
#define LIS_INFO2_REG		0x0E
#define LIS_WHOAMI_REG		0x0F
#define LIS_OFF_X_REG		0x10
#define LIS_OFF_Y_REG		0x11
#define	LIS_OFF_Z_REG		0x12
#define LIS_CS_X_REG		0x13
#define LIS_CS_Y_REG		0x14
#define LIS_CS_Z_REG		0x15
#define LIS_LC_L_REG		0x16
#define LIS_LC_H_REG		0x17
#define LIS_STAT_REG		0x18
#define LIS_PEAK1_REG		0x19
#define LIS_PEAK2_REG		0x1A
#define LIS_VFC_1_REG		0x1B
#define LIS_VFC_2_REG		0x1C
#define LIS_VFC_3_REG		0x1D
#define LIS_VFC_4_REG		0x1E
#define LIS_THRS3_REG		0x1F
#define LIS_CTRL_REG4_REG	0x20
#define LIS_CTRL_REG1_REG	0x21
#define LIS_CTRL_REG2_REG	0x22
#define LIS_CTRL_REG3_REG	0x23
#define LIS_CTRL_REG5_REG	0x24
#define LIS_CTRL_REG6_REG	0x25
#define LIS_STATUS_REG		0x27
#define LIS_OUT_X_L_REG		0x28
#define LIS_OUT_X_H_REG		0x29
#define LIS_OUT_Y_L_REG		0x2A
#define LIS_OUT_Y_H_REG		0x2B
#define LIS_OUT_Z_L_REG		0x2C
#define LIS_OUT_Z_H_REG		0x2D
#define LIS_FIFO_CTRL_REG	0x2E
#define LIS_FIFO_SRC_REG	0x2F
#define LIS_TIM4_1_REG		0x50
#define LIS_TIM3_1_REG		0x51
#define LIS_TIM2_1_L_REG	0x52
#define LIS_TIM2_1_H_REG	0x53
#define LIS_TIM1_1_L_REG	0x54
#define LIS_TIM1_1_H_REG	0x55
#define LIS_THRS2_1_REG		0x56
#define LIS_THRS1_1_REG		0x57
#define LIS_MASK1_B_REG		0x59
#define LIS_MASK1_A_REG		0x5A
#define LIS_SETT1_REG		0x5B
#define LIS_PR1_REG			0x5C
#define LIS_TC1_L			0x5D
#define LIS_TC1_H			0x5E
#define LIS_OUTS1_REG		0x5F
#define LIS_TIM4_2_REG		0x70
#define LIS_TIM3_2_REG		0x71
#define LIS_TIM2_2_L_REG	0x72
#define LIS_TIM2_2_H_REG	0x73
#define LIS_TIM1_2_L_REG	0x74
#define LIS_TIM1_2_H_REG	0x75
#define LIS_THRS2_2_REG		0x76
#define LIS_THRS1_2_REG		0x77
#define LIS_DES2_REG		0x78
#define LIS_MASK2_B_REG		0x79
#define LIS_MASK2_A_REG		0x7A
#define LIS_SETT2_REG		0x7B
#define LIS_PR2_REG			0x7C
#define LIS_TC2_L_REG		0x7D
#define LIS_TC2_H_REG		0x7E
#define LIS_OUTS2_REG		0x7F

// LIS data rate values
#define LIS_DATARATE_PDOWN	0x00
#define LIS_DATARATE_3		0x01
#define LIS_DATARATE_6		0x02
#define LIS_DATARATE_12		0x03
#define LIS_DATARATE_25		0x04
#define LIS_DATARATE_50		0x05
#define LIS_DATARATE_100	0x06
#define LIS_DATARATE_400	0x07
#define LIS_DATARATE_800	0x08
#define LIS_DATARATE_1600	0x09

// LIS axis enable macros
#define LIS_X_EN			0x01
#define LIS_Y_EN			0x02
#define LIS_Z_EN			0x03
#define LIS_XYZ_EN			0x06


#define LIS_DATAR_BIT_POS	0x04
#define LIS_AXIS_EN_BIT_POS	0x00

#define LIS_CS_ENABLE			(GPIOE->BSRR = (1 << GPIO_BSRR_BR3_Pos))
#define LIS_CS_DISABLE			(GPIOE->BSRR = (1 << GPIO_BSRR_BS3_Pos))


typedef struct{
	uint8_t datarate;
	uint8_t	axis_enable;
}LIS_Init_typedef;

extern SPI_HandleTypeDef hspi1;

void LIS_init();
void LIS_write_data(uint8_t data, uint8_t addr);
void LIS_read_data(uint8_t addr, uint8_t *buf, uint8_t size);
uint16_t LIS_SPI_write(uint8_t data);
uint16_t LIS_SPI_read(uint8_t addr);

#endif /* INC_LIS_ACC_H_ */
