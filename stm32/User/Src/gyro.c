/*
 * gyro.c
 *
 *  Created on: Nov 14, 2025
 *      Author: pyryl
 */
#include "gyro.h"
#include <stdio.h>

float gyro_sensitivity = 131.2f; // When sensitivity scale is 250 dps

HAL_StatusTypeDef i2c_read_mem(uint16_t dev_ddr, uint16_t mem_addr, uint8_t* recv_buf, size_t recv_len, I2C_HandleTypeDef* hi2c){
	return HAL_I2C_Mem_Read(hi2c, dev_ddr << 1, mem_addr, I2C_MEMADD_SIZE_8BIT, recv_buf, recv_len, 2);
}

HAL_StatusTypeDef i2c_write_mem(uint16_t dev_addr, uint16_t mem_addr, uint8_t* buf, size_t write_len,I2C_HandleTypeDef* hi2c){
	return HAL_I2C_Mem_Write(hi2c, dev_addr << 1, mem_addr, I2C_MEMADD_SIZE_8BIT, buf, write_len, 2);
}

/**
 * Configures gyroscope for use
 * @param [in] hi2c: I2C Handle
 */
void gyro_setup(I2C_HandleTypeDef* hi2c){
	// Read who am i register to confirm connectivity
	uint8_t whoamibuf[1];
	uint8_t write_buf[] = {0x81}; // Soft reset value that is written to power management register
	//Soft reset must be done before whoami register is readable
	i2c_write_mem(IAM_GYRO_DEV_ADDR, IAM_PWR_MGMT_1_REG, write_buf, 1, hi2c);
	HAL_Delay(10);
	i2c_read_mem(IAM_GYRO_DEV_ADDR, IAM_WHO_AM_I_REG, whoamibuf, 1, hi2c);
}

/**
 * Reads gyroscope x, y and z data register and transforms them into angular readings
 *
 * @param [out] x: Pointer to where x will be stored
 * @param [out] y: Pointer to where y will be stored
 * @param [out] z: Pointer to where z will be stored
 * @param [in] hi2c: I2C Handle
 */
void gyro_read(float* x, float* y, float* z, I2C_HandleTypeDef* hi2c){
	uint8_t low_buffer[1], high_buffer[1];
	// Read x low and high buffers
	i2c_read_mem(IAM_GYRO_DEV_ADDR, IAM_GYRO_XOUT_H_REG, high_buffer, 1, hi2c);
	i2c_read_mem(IAM_GYRO_DEV_ADDR, IAM_GYRO_XOUT_L_REG, low_buffer, 1, hi2c);
	*x = (float)((*high_buffer << 8) | (*low_buffer));

	// Y low and high buffers
	i2c_read_mem(IAM_GYRO_DEV_ADDR, IAM_GYRO_YOUT_H_REG, high_buffer, 1, hi2c);
	i2c_read_mem(IAM_GYRO_DEV_ADDR, IAM_GYRO_YOUT_L_REG, low_buffer, 1, hi2c);
	*y =  (float)((*high_buffer << 8) | (*low_buffer));

	// Z low and high buffers
	i2c_read_mem(IAM_GYRO_DEV_ADDR, IAM_GYRO_ZOUT_H_REG, high_buffer, 1, hi2c);
	i2c_read_mem(IAM_GYRO_DEV_ADDR, IAM_GYRO_ZOUT_L_REG, low_buffer, 1, hi2c);
	*z =  (float)((*high_buffer << 8) | (*low_buffer));

	// Convert raw values to actual angular speed values
	*x = *x / gyro_sensitivity;
	*y = *y / gyro_sensitivity;
	*z = *z / gyro_sensitivity;
}


