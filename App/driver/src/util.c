/*
 * util.c
 *
 *  Created on: Oct 30, 2023
 *      Author: alren
 */

#include "util.h"


void delay(uint32_t time_ms)
{
  HAL_Delay(time_ms);
}

uint32_t millis(void)
{
  return HAL_GetTick();
}
