/*
 * util.c
 *
 *  Created on: Oct 30, 2023
 *      Author: alren
 */

#include "util.h"
#include "main.h"

void delay(uint32_t time_ms)
{
  HAL_Delay(time_ms);
}

uint32_t millis(void)
{
  return HAL_GetTick();
}


void ledToggle(void)
{
	HAL_GPIO_TogglePin(LED_CRT_GPIO_Port, LED_CRT_Pin);
}