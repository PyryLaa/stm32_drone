/*
 * gyro.h
 *
 *  Created on: Nov 14, 2025
 *      Author: pyryl
 */

#ifndef INC_GYRO_H_
#define INC_GYRO_H_

#include "main.h"

#define IAM_GYRO_DEV_ADDR			0x68
#define IAM_WHOAMI_VALUE			0xFD
// Register definitions
#define IAM_SELF_TEST_X_GYRO_REG	0x00
#define IAM_SELF_TEST_Y_GYRO_REG	0x01
#define IAM_SELF_TEST_Z_GYRO_REG	0x02
#define IAM_XG_OFFS_USRH_REG		0x13
#define IAM_XG_OFFS_USRL_REG		0x14
#define IAM_YG_OFFS_USRH_REG		0x15
#define IAM_YG_OFFS_USRL_REG		0x16
#define IAM_ZG_OFFS_USRH_REG		0x17
#define IAM_ZG_OFFS_USRL_REG		0x18
#define IAM_SMPLRT_DIV_REG			0x19
#define IAM_CONFIG_REG				0x1A
#define IAM_GYRO_CONFIG_REG			0x1B
#define IAM_FIFO_SIZE_CONFIG_REG	0x1D
#define IAM_LP_MODE_CFG_REG			0x1E
#define IAM_FIFO_EN_REG				0x23
#define IAM_FSYNC_INT_REG			0x36
#define IAM_INT_PIN_CFG_REG			0x37
#define IAM_INT_ENABLE_REG			0x38
#define IAM_INT_STATUS_REG			0x3A
#define IAM_TEMP_OUT_H_REG			0x41
#define IAM_TEMP_OUT_L_REG			0x42
#define IAM_GYRO_XOUT_H_REG			0x43
#define IAM_GYRO_XOUT_L_REG			0x44
#define IAM_GYRO_YOUT_H_REG			0x45
#define IAM_GYRO_YOUT_L_REG			0x46
#define IAM_GYRO_ZOUT_H_REG			0x47
#define IAM_GYRO_ZOUT_L_REG			0x48
#define IAM_SIGNAL_PATH_RESET_REG	0x68
#define IAM_USER_CTRL_REG			0x6A
#define IAM_PWR_MGMT_1_REG			0X6B
#define IAM_PWR_MGMT_2_REG			0X6C
#define IAM_FIFO_COUNTH_REG			0X72
#define IAM_FIFO_COUNTL_REG			0X73
#define IAM_FIFO_R_W_REG			0X74
#define IAM_WHO_AM_I_REG			0X75

extern I2C_HandleTypeDef i2c1;

void i2c_read(uint16_t dev_ddr, uint8_t* addr_buf, uint8_t* recv_buf, I2C_HandleTypeDef* hi2c);
void i2c_write(uint8_t addr, uint8_t* buf, I2C_HandleTypeDef* hi2c);
void gyro_setup();

#endif /* INC_GYRO_H_ */



