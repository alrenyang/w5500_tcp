/*
 * uart.c
 *
 *  Created on: Oct 30, 2023
 *      Author: alren
 */

#include "uart.h"
#include "main.h"

#include "hw_def.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

#define UART_Q_BUF_MAX      256

//#define UART_RX_BUF_LENGTH        1024

/*
typedef struct
{
  bool is_open;
  uint32_t baud;

  uint8_t  rx_buf[UART_RX_BUF_LENGTH];
  qbuffer_t qbuffer;
  UART_HandleTypeDef *p_huart;
  DMA_HandleTypeDef  *p_hdma_rx;

  uint32_t rx_cnt;
  uint32_t tx_cnt;
} uart_tbl_t;
*/

extern UART_HandleTypeDef huart1;	//deburg uart
// extern UART_HandleTypeDef huart1;	//sonic uart


static uint16_t q_in = 0;
static uint16_t q_out = 0;
static uint8_t  q_buf[UART_Q_BUF_MAX];
//static uint8_t  rx_data;


/*
bool uartInit(void)
{
  for (int i=0; i<UART_MAX_CH; i++)
  {
    uart_tbl[i].is_open = false;
    uart_tbl[i].baud = 115200;
    uart_tbl[i].rx_cnt = 0;
    uart_tbl[i].tx_cnt = 0;
  }

  is_init = true;

#if CLI_USE(HW_UART)
  cliAdd("uart", cliUart);
#endif
  return true;
}
*/


bool uartInit(void)
{

  //HAL_UART_Receive_IT(&huart1, &rx_data, 1);	//uart interrut
  // HAL_UART_Receive_DMA(&huart1, &q_buf[0], UART_Q_BUF_MAX);

  // if (HAL_UART_Receive_DMA(&huart1, &q_buf[0], UART_Q_BUF_MAX) != HAL_OK)
  // {
  //   // 에러 발생 시 처리
  // }

  return true;
}

uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length)
{
  uint32_t ret = 0;
  HAL_StatusTypeDef hal_ret;


  switch(ch)
  {
    case _DEF_CH1:
      hal_ret = HAL_UART_Transmit(&huart1, p_data, length, 100);
      if (hal_ret == HAL_OK)
      {
        ret = length;
      }
      break;
  }

  return ret;
}

uint32_t uartAvailable(uint8_t ch)
{
  uint32_t ret = 0;


  switch(ch)
  {
    case _DEF_CH1:
	    // q_in = (UART_Q_BUF_MAX - huart1.hdmarx->Instance->CNDTR) % UART_Q_BUF_MAX;
      q_in = (UART_Q_BUF_MAX - huart1.hdmarx->Instance->NDTR) % UART_Q_BUF_MAX;
      ret = (UART_Q_BUF_MAX + q_in - q_out) % UART_Q_BUF_MAX;
      break;
  }

  return ret;
}

uint8_t  uartRead(uint8_t ch)
{
  uint8_t ret = 0;


  switch(ch)
  {
    case _DEF_CH1:
      if (q_out != q_in)
      {
        ret = q_buf[q_out];
        q_out = (q_out + 1) % UART_Q_BUF_MAX;
      }
      break;
  }

  return ret;
}

uint32_t uartPrintf(uint8_t ch, const char *fmt, ...)
{
  uint32_t ret = 0;
  va_list arg;
  char print_buf[256];


  va_start(arg, fmt);

  int len;
  len = vsnprintf(print_buf, 256, fmt, arg);
  va_end(arg);

  if (len > 0)
  {
    ret = uartWrite(ch, (uint8_t *)print_buf, len);
  }

  return ret;
}

uint32_t uartVPrintf(uint8_t ch, const char *fmt, va_list arg)
{
  uint32_t ret = 0;
  char print_buf[256];


  int len;
  len = vsnprintf(print_buf, 256, fmt, arg);

  if (len > 0)
  {
    ret = uartWrite(ch, (uint8_t *)print_buf, len);
  }


  return ret;
}

/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		if(rx_data == 'R')
		{
			uartPrintf(_DEF_CH1,"uart1: %c\r\n", rx_data);
		}

	  HAL_UART_Receive_IT(&huart1, &rx_data, 1);
	}

  if (&huart1 == huart)
  {

    // Buffer Write
    //
    uint16_t q_in_next;

    q_in_next = (q_in + 1) % UART_Q_BUF_MAX;
    if (q_in_next != q_out)
    {
      q_buf[q_in] = q_data;
      q_in = q_in_next;
    }

    HAL_UART_Receive_IT(&huart1, &q_data, 1);
  }

}
*/

