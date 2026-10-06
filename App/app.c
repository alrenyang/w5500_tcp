

#include "app.h"
#include "httpServer.h"

static void infoCli(uint8_t argc, const char **argv);

extern SPI_HandleTypeDef hspi1;

void apInit(void)
{
    delay(100);

    cliInit();
    uartInit();
    uartPrintf(_DEF_CH1,"\r\n[ Firmware Begin... ]\r\n");
    uartPrintf(_DEF_CH1,"Booting..Name \t\t: %s\r\n", _DEF_BOARD_NAME);
    uartPrintf(_DEF_CH1,"Booting..Ver  \t\t: %s\r\n", _DEF_FIRMWATRE_VERSION);
    uartPrintf(_DEF_CH1,"Booting..Clock\t\t: %d Mhz\r\n", (int)HAL_RCC_GetSysClockFreq()/1000000);
    uartPrintf(_DEF_CH1,"\r\nDATE: [%s] TIME[%s]\r\n",__DATE__,__TIME__);

    wizchip_reset();
    HAL_Delay(200);
    CheckRdy();
    HAL_Delay(20);
	  w5500Init();

    cliAdd("info", infoCli);

}


void apMain(void)
{
  uint32_t pre_time = 0;

  w5500Info();
  HAL_Delay(10);
  print_network_information();
	HAL_Delay(10);
	DnsInit();

  WebServer_Init();

  while (1)
  {
      /* USER CODE END WHILE */
      

      /* USER CODE BEGIN 3 */
      if (millis()-pre_time >= 500)
      {
          pre_time = millis();
          ledToggle();
      }
      Run_Tcp_Client();

      // HTTP 서버 루프 (주기적으로 폴링하며 웹 접속 처리)
      httpServer_run(0);
      httpServer_run(1);

      cliMain();
  }
}

void ledToggle(void)
{
	HAL_GPIO_TogglePin(LED_CRT_GPIO_Port, LED_CRT_Pin);
}


void infoCli(uint8_t argc, const char **argv)
{
  bool ret = false;


  if (argc == 1 && cliIsStr(argv[0], "test"))
	{
		cliPrintf("infoCli run test\r\n");
		ret = true;
	}

  if (argc == 2 && cliIsStr(argv[0], "print"))
	{
	  uint8_t count;

	count = (uint8_t)cliGetData(argv[1]);
	for (int i=0; i<count; i++)
	{
	  cliPrintf("print %d/%d\r\n", i+1, count);
	}

		ret = true;
	}

  if (argc == 1 && cliIsStr(argv[0], "led_on"))
	{
		// ledOn(_DEF_CH1);
		ret = true;
	}

  if (argc == 1 && cliIsStr(argv[0], "led_off"))
	{
		// ledOff(_DEF_CH1);
		ret = true;
	}

  if (argc == 1 && cliIsStr(argv[0], "netinfo"))
	{
		// print_network_information();
		ret = true;
	}

  if (argc == 1 && cliIsStr(argv[0], "mqttrun"))
  	{
	    // MqttRun();
  		ret = true;
  	}

  if (ret == false)
	{
		cliPrintf("info test\r\n");
		cliPrintf("info print 0~10\r\n");
		cliPrintf("info led_on\r\n");
		cliPrintf("info led_off\r\n");
		cliPrintf("info netinfo\r\n");
		cliPrintf("info MQTTRUN\r\n");
	}
}