#ifndef DEF_H_
#define DEF_H_


#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#include "main.h"

//#define _USE_WSDG_
#define _USE_DBG_

#define _DEF_FIRMWATRE_VERSION    "V260908"
#define _DEF_BOARD_NAME           "STM32F411RETx "

#define _DEF_CH1          0
#define _DEF_CH2          1
#define _DEF_CH3          2
#define _DEF_CH4          3

#define _DEF_UART1            0
#define _DEF_UART2            1
#define _DEF_UART3            2
#define _DEF_UART4            3

#define _USE_HW_UART
#define      HW_UART_MAX_CH         2
#define      HW_UART_CH_SWD         _DEF_UART1
#define      HW_UART_CH_USB         _DEF_UART2
#define      HW_UART_CH_CLI         HW_UART_CH_SWD


#define _USE_HW_LOG
#define      HW_LOG_CH              _DEF_UART1
#define      HW_LOG_BOOT_BUF_MAX    2048
#define      HW_LOG_LIST_BUF_MAX    4096

#endif