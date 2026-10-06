/*
 * spi.c
 *
 *  Created on: Oct 31, 2023
 *      Author: alren
 */

#include "spi.h"

extern SPI_HandleTypeDef hspi1;


bool spiInit(void)
{

	return true;
}

uint8_t spiReadByte(void)
{
  uint8_t readByte=0;
  uint8_t writeByte=0xFF;

  while(HAL_SPI_GetState(&hspi1)!=HAL_SPI_STATE_READY);
  HAL_SPI_TransmitReceive(&hspi1, &writeByte, &readByte, 1, 10);

  return readByte;
}

void spiWriteByte(uint8_t writeByte)
{
  uint8_t readByte=0;

  while(HAL_SPI_GetState(&hspi1)!=HAL_SPI_STATE_READY);
  HAL_SPI_TransmitReceive(&hspi1, &writeByte, &readByte, 1, 10);

}

void spiReadBurst(uint8_t* pBuf, uint16_t len)
{
  while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY &&
      HAL_DMA_GetState(hspi1.hdmarx) != HAL_DMA_STATE_READY && HAL_DMA_GetState(hspi1.hdmatx) != HAL_DMA_STATE_READY);

  HAL_SPI_Receive_DMA(&hspi1, pBuf, len);

  while (HAL_DMA_GetState(hspi1.hdmarx) == HAL_DMA_STATE_BUSY|| HAL_DMA_GetState(hspi1.hdmarx) == HAL_DMA_STATE_RESET);
  while (HAL_DMA_GetState(hspi1.hdmatx) == HAL_DMA_STATE_BUSY|| HAL_DMA_GetState(hspi1.hdmatx) == HAL_DMA_STATE_RESET);

  return;
}

void spiWriteBurst(uint8_t* pBuf, uint16_t len)
{
  while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY &&
      HAL_DMA_GetState(hspi1.hdmarx) != HAL_DMA_STATE_READY && HAL_DMA_GetState(hspi1.hdmatx) != HAL_DMA_STATE_READY);

  HAL_SPI_Transmit_DMA(&hspi1, pBuf, len);

  while (HAL_DMA_GetState(hspi1.hdmarx) == HAL_DMA_STATE_BUSY|| HAL_DMA_GetState(hspi1.hdmarx) == HAL_DMA_STATE_RESET);
  while (HAL_DMA_GetState(hspi1.hdmatx) == HAL_DMA_STATE_BUSY|| HAL_DMA_GetState(hspi1.hdmatx) == HAL_DMA_STATE_RESET);

  return;
}

void wizchip_csEnable(void)
{
  HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);  //chip select
}

void wizchip_csDisable(void)
{
  HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);  //chip unselect
}

void wizchip_reset()
{
  HAL_GPIO_WritePin(W5500R_RST_GPIO_Port, W5500R_RST_Pin, GPIO_PIN_RESET);
  HAL_Delay(500);
  HAL_GPIO_WritePin(W5500R_RST_GPIO_Port, W5500R_RST_Pin, GPIO_PIN_SET);
  HAL_Delay(200);
}

bool CheckRdy(void)
{
	bool ret = false;

	while(1)
	{
		if(HAL_GPIO_ReadPin(W5500_RDY_GPIO_Port, W5500_RDY_Pin) == 1)
		{
			break;
		}
	}


	return ret;
}




