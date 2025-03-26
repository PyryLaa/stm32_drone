#include "lis_acc.h"
#include "stm32f4xx.h"

uint16_t rx_temp;
uint16_t rx_data;
uint8_t whoami;
uint8_t read_buf[2];
uint8_t read_size = sizeof read_buf / sizeof read_buf[0];

void LIS_init(LIS_Init_typedef* lis_init) {
	SPI1->CR1 |= (1 << SPI_CR1_SPE_Pos);
}

void LIS_write_data(uint8_t data, uint8_t addr) {
	//LIS_SPI_write(addr);
	//LIS_SPI_write(data);
	HAL_SPI_Transmit(&hspi1, &addr, 1, 10);
	HAL_SPI_Transmit(&hspi1, &data, 1, 10);
}

void LIS_read_data(uint8_t addr, uint8_t *buf, uint8_t size) {
	addr |= 0x80;
	LIS_CS_ENABLE;
	HAL_SPI_Transmit(&hspi1, &addr, 1, 10);
	HAL_SPI_Receive(&hspi1, read_buf, 1, 10);
	LIS_CS_DISABLE;
}

uint16_t LIS_SPI_write(uint8_t data) {
	// Wait until SPI TX buffer is empty
	while (!(SPI1->SR & SPI_SR_TXE));
	SPI1->DR = data;

	while (!(SPI1->SR & SPI_SR_RXNE));
	// If reception is intended, read the value from the data register
	rx_temp = SPI1->DR;

	return rx_temp;

}

uint16_t LIS_SPI_read(uint8_t addr) {

	// OR with 0x80 to set MSB to indicate reading to LIS sensor
	addr |= 0x80;

	// Pull GPIOE pin 3 down for chip select
	GPIOE->BSRR = (1 << GPIO_BSRR_BR3_Pos);

	LIS_SPI_write(addr);

	// Write 0 as dummy data to receive the data from
	rx_data = LIS_SPI_write(0);
	GPIOE->BSRR = (1 << GPIO_BSRR_BS3_Pos);
	return rx_data;
}
