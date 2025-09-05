#include "lis_acc.h"
#include "stm32f4xx.h"
#include <math.h>

uint8_t read_buf[2];
uint8_t read_size = sizeof read_buf / sizeof read_buf[0];

void LIS_init(LIS_Init_typedef* lis_init) {
	uint16_t init_val = (uint16_t)(lis_init->datarate | lis_init->axis_enable);
	SPI1->CR1 |= (1 << SPI_CR1_SPE_Pos);
	LIS_write_data(LIS_CTRL_REG4_REG, init_val);
	LIS_read_data(LIS_WHOAMI_REG, read_buf, read_size);
}

void LIS_write_data(uint8_t addr, uint8_t data) {
	uint8_t temp_buf[2] = {addr, data};
	LIS_CS_ENABLE;
	SPI_write(temp_buf, 2);
	LIS_CS_DISABLE;
}

void LIS_read_data(uint8_t addr, uint8_t* buf, uint8_t size) {
	addr |= 0x80;
	LIS_CS_ENABLE;
	SPI_write(&addr, 1);
	SPI_read(buf, size);
	LIS_CS_DISABLE;
}

void SPI_write(uint8_t* data, uint8_t size) {
		for(uint8_t i = 0; i < size; ++i) {
			/*Wait until TXE is set*/
			while(!(SPI1->SR & (SPI_SR_TXE)));

			/*Write the data to the data register*/
			SPI1->DR = data[i];
		}
		/*Wait until TXE is set*/
		while(!(SPI1->SR & (SPI_SR_TXE)));

		/*Wait for BUSY flag to reset*/
		while((SPI1->SR & (SPI_SR_BSY)));

		/*Clear OVR flag*/
		(void)SPI1->DR;
		(void)SPI1->SR;
}

void SPI_read(uint8_t* data, uint8_t size) {
	while(size){
			/*Send dummy data*/
			SPI1->DR =0;

			/*Wait for RXNE flag to be set*/
			while(!(SPI1->SR & (SPI_SR_RXNE))){}

			/*Read data from data register*/
			*data++ = (SPI1->DR);
			size--;
	}
}

void LIS_read_pitch_roll(float* buf, uint8_t size){
	if(size != 2){
		return;
	}
	uint8_t xl_read_buf[1];
	uint8_t xh_read_buf[1];
	uint8_t yl_read_buf[1];
	uint8_t yh_read_buf[1];
	uint8_t zl_read_buf[1];
	uint8_t zh_read_buf[1];
	float acc_g = 0.00006;
	uint8_t read_size = 1;

	LIS_read_data(LIS_OUT_X_L_REG, xl_read_buf, read_size);
	LIS_read_data(LIS_OUT_X_H_REG, xh_read_buf, read_size);
	LIS_read_data(LIS_OUT_Y_L_REG, yl_read_buf, read_size);
	LIS_read_data(LIS_OUT_Y_H_REG, yh_read_buf, read_size);
	LIS_read_data(LIS_OUT_Z_L_REG, zl_read_buf, read_size);
	LIS_read_data(LIS_OUT_Z_H_REG, zh_read_buf, read_size);
	int16_t x_val = (xh_read_buf[0] << 8) | (xl_read_buf[0]);
	int16_t y_val = (yh_read_buf[0] << 8) | (yl_read_buf[0]);
	int16_t z_val = (zh_read_buf[0] << 8) | (zl_read_buf[0]);
	float ax = x_val * acc_g;
	float ay = y_val * acc_g;
	float az = z_val * acc_g;
	buf[0] = atan2(ax, sqrt(ay*ay + az*az)) * 180.0f / M_PI;
	buf[1] = atan2(ay, sqrt(ax*ax + az*az)) *  180.0f / M_PI;
}
