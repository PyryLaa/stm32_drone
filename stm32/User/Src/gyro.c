/*
 * gyro.c
 *
 *  Created on: Nov 14, 2025
 *      Author: pyryl
 */
#include "gyro.h"
#include <stdio.h>

void i2c_read_mem(uint16_t dev_ddr, uint16_t mem_addr, uint8_t* recv_buf, size_t recv_len, I2C_HandleTypeDef* hi2c){
	HAL_I2C_Mem_Read(hi2c, dev_ddr, mem_addr, I2C_MEMADD_SIZE_8BIT, recv_buf, recv_len, 2);
}

void i2c_write_mem(uint16_t dev_addr, uint16_t mem_addr, uint8_t* buf, size_t write_len,I2C_HandleTypeDef* hi2c){
	HAL_I2C_Mem_Write(hi2c, dev_addr, mem_addr, I2C_MEMADD_SIZE_8BIT, buf, write_len, 2);
}

void gyro_setup(){
	// Read who am i register to confirm connectivity
	uint8_t whoamibuf[1];
	size_t recv_len = sizeof(whoamibuf) / sizeof(whoamibuf[0]);
	i2c_read_mem(IAM_GYRO_DEV_ADDR, IAM_WHO_AM_I_REG, whoamibuf, recv_len, &i2c1);
	if(whoamibuf[0] != IAM_WHOAMI_VALUE){
		return;
	}
}
