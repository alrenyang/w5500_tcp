#include "wiz5500.h"


// 사용할 장비 번호 선택
#define DEVICE_ID   0

// 장비별 네트워크 정보 테이블 정의
typedef struct {
    uint8_t mac[6];
    uint8_t ip[4];
} DeviceConfig_t;

const DeviceConfig_t DEVICE_LIST[] = {
    // ID 0번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xA0}, {192, 168, 10, 20} },
    // ID 1번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xA1}, {192, 168, 10, 21} },
    // ID 2번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xA2}, {192, 168, 10, 22} },
    // ID 3번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xA3}, {192, 168, 10, 23} },
    // ID 4번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xA4}, {192, 168, 10, 24} },
    // ID 5번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xA5}, {192, 168, 10, 25} },
    // ID 6번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xA6}, {192, 168, 10, 26} },
    // ID 7번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xA7}, {192, 168, 10, 27} },
    // ID 8번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xA8}, {192, 168, 10, 28} },
    // ID 9번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xA9}, {192, 168, 10, 29} },
    // ID 10번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xAA}, {192, 168, 10, 30} },
    // ID 11번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xAB}, {192, 168, 10, 31} },
    // ID 12번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xAC}, {192, 168, 10, 32} },
    // ID 13번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xAD}, {192, 168, 10, 33} },
    // ID 14번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xAE}, {192, 168, 10, 34} },
    // ID 15번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xAF}, {192, 168, 10, 35} },
    // ID 16번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xB0}, {192, 168, 10, 36} },
    // ID 17번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xB1}, {192, 168, 10, 37} },
    // ID 18번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xB2}, {192, 168, 10, 38} },
    // ID 19번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xB3}, {192, 168, 10, 39} },
    // ID 20번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xB4}, {192, 168, 10, 40} },
    // ID 21번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xB5}, {192, 168, 10, 41} },
    // ID 22번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xB6}, {192, 168, 10, 42} },
    // ID 23번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xB7}, {192, 168, 10, 43} },
    // ID 24번 장비
    { {0x00, 0x08, 0xDC, 0x77, 0x84, 0xB8}, {192, 168, 10, 44} }
};


wiz_NetInfo gWIZNETINFO  = {

	.mac = { 
        DEVICE_LIST[DEVICE_ID].mac[0], 
        DEVICE_LIST[DEVICE_ID].mac[1], 
        DEVICE_LIST[DEVICE_ID].mac[2], 
        DEVICE_LIST[DEVICE_ID].mac[3], 
        DEVICE_LIST[DEVICE_ID].mac[4], 
        DEVICE_LIST[DEVICE_ID].mac[5] 
    },
    .ip = { 
        DEVICE_LIST[DEVICE_ID].ip[0], 
        DEVICE_LIST[DEVICE_ID].ip[1], 
        DEVICE_LIST[DEVICE_ID].ip[2], 
        DEVICE_LIST[DEVICE_ID].ip[3] 
    },

	.gw = {192, 168, 10, 1},
	.dns = {168, 126, 63, 1},
	// .dns = {168, 126, 63, 1},                       // 필요시 DNS 설정 (KT DNS 등)
    .sn = {255, 255, 255, 0},

    .dhcp = NETINFO_STATIC
};

#define ETH_MAX_BUF_SIZE  2048

const uint8_t URL[] = "www.google.com";
uint8_t dns_server_ip[4] = {168,126,63,1};
//uint8_t dns_server_ip[4] = {164,124,101,2};
uint8_t dnsclient_ip[4] = {0,};
//uint8_t dnsclient_ip[4] = {112, 168, 210, 249};
unsigned int targetPort = 1883; // mqtt server port

unsigned char targetIP[4] = {112, 168, 210, 249}; // mqtt server IP 112.168.210.249

unsigned char ethBuf0[ETH_MAX_BUF_SIZE];

uint8_t IP_TYPE;


bool w5500Init(void)
{
	reg_wizchip_cs_cbfunc(wizchip_csEnable,wizchip_csDisable);// CS function register
	HAL_Delay(100);
	reg_wizchip_spi_cbfunc(spiReadByte, spiWriteByte);

	reg_wizchip_spiburst_cbfunc(spiReadBurst, spiWriteBurst);
	//uartPrintf(_DEF_CH1, "--test-----\r\n");
	HAL_Delay(100);
	wizchip_initialize();

	return true;
}


void wizchip_initialize(void)
{
  uint8_t W5x00_AdrSet[2][8] = {{2, 2, 2, 2, 2, 2, 2, 2},{2, 2, 2, 2, 2, 2, 2, 2},};
  //uint8_t tmp1, tmp2;
  int8_t phy_link =0;
  intr_kind temp= IK_DEST_UNREACH;

  wizchip_reset();
  HAL_Delay(200);
  if (ctlwizchip(CW_INIT_WIZCHIP, (void*)W5x00_AdrSet) == -1)
	  uartPrintf(_DEF_CH1,">> [W5500] memory initialization failed\r\n");
  HAL_Delay(200);

  if(ctlwizchip(CW_SET_INTRMASK,&temp) == -1)
	  uartPrintf(_DEF_CH1,">> [W5500] interrupt\r\n");
  HAL_Delay(200);


  if(getVERSIONR() != 0x04){
	  uartPrintf(_DEF_CH1,">> [W5500] Access ERR: VERSION != 0x04, value = %02x\r\n", getVERSIONR());
	  NVIC_SystemReset();
  }else{
	  uartPrintf(_DEF_CH1,">> [W5500] Access Get: VERSION = [ %02x ]\r\n", getVERSIONR());\
	  uartPrintf(_DEF_CH1,"\r\n");
  }

  do{//check phy status.
  		if(ctlwizchip(CW_GET_PHYLINK,&phy_link) == -1){
  			uartPrintf(_DEF_CH1,">> [W5500] Unknown PHY link status.\r\n");
  			HAL_Delay(10);
  			NVIC_SystemReset();
  		}

  	}while(phy_link == PHY_LINK_OFF);

//  while(1)
//  {
//    ctlwizchip(CW_GET_PHYLINK, &phy_link );
//    HAL_Delay(4000);
//    ctlwizchip(CW_GET_PHYLINK, &tmp2 );
//    HAL_Delay(4000);
//    if(tmp1==PHY_LINK_ON && tmp2==PHY_LINK_ON)
//	{
//    	uartPrintf(_DEF_CH1,">> [W5500] W5x00s done initialization....\r\n");
//		break;
//	}
//    else{
//    	uartPrintf(_DEF_CH1,">> [W5500] W5x00s done initialization failed....\r\n");
//    	NVIC_SystemReset();
//    }
//  }
}


bool w5500Info(void)
{
	wizchip_setnetinfo(&gWIZNETINFO);

	return true;
}

void print_network_information(void)
{
	wizchip_getnetinfo(&gWIZNETINFO);
	memset(&gWIZNETINFO,0,sizeof(gWIZNETINFO));
#ifdef _USE_DBG_
	
	uartPrintf(_DEF_CH1,">> [W5500] MAC Address : %02x:%02x:%02x:%02x:%02x:%02x\n\r",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
	uartPrintf(_DEF_CH1,">> [W5500] IP  Address : %d.%d.%d.%d\n\r",gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
	uartPrintf(_DEF_CH1,">> [W5500] Subnet Mask : %d.%d.%d.%d\n\r",gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
	uartPrintf(_DEF_CH1,">> [W5500] Gateway     : %d.%d.%d.%d\n\r",gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
	uartPrintf(_DEF_CH1,">> [W5500] DNS Server  : %d.%d.%d.%d\n\r",gWIZNETINFO.dns[0],gWIZNETINFO.dns[1],gWIZNETINFO.dns[2],gWIZNETINFO.dns[3]);

	uartPrintf(_DEF_CH1, "\n\r");
#endif
	if(gWIZNETINFO.mac[0] == 0xFF)
	{
		while(1)
		{
			////forever loop wdg call
			NVIC_SystemReset();
		}
	}
}

void DnsInit(void)
{
    uint32_t start_tick;
    uint8_t dns_retry = 0;
    const uint8_t max_retry = 5;       // 최대 재시도 횟수
    const uint32_t timeout_ms = 3000;  // 3초 타임아웃

    DNS_init(0, ethBuf0);
    IP_TYPE = 0x1c;

    while (1)
    {
        // DNS 요청 실행 및 상태 체크
        int8_t dns_result = DNS_run(dns_server_ip, (uint8_t*)URL, dnsclient_ip);
        
        if (dns_result == 1) {
            // DNS 변환 성공
            break;
        }
        else if (dns_result < 0) {
            // 에러 발생 시 처리 (필요에 따라 로그 출력 등)
            #ifdef _USE_DBG_
            uartPrintf(_DEF_CH1, ">> [W5500]DNS Error Code: %d\r\n", dns_result);
            #endif
        }

        // 타임아웃 또는 재시도 횟수 초과 체크 로직
        // (HAL_GetTick()이 1ms마다 증가한다고 가정)
        start_tick = HAL_GetTick();
        while ((HAL_GetTick() - start_tick) < timeout_ms) {
            // 타임아웃 대기 중에도 DNS_run을 폴링하거나 짧게 쉴 수 있습니다.
            // 여기서는 간단히 루프를 돌며 상태를 체크합니다.
            if (DNS_run(dns_server_ip, (uint8_t*)URL, dnsclient_ip) == 1) {
                return; // 성공 시 즉시 탈출
            }
        }

        // 타임아웃 도달 시 재시도 횟수 증가
        dns_retry++;
        if (dns_retry >= max_retry) {
            #ifdef _USE_DBG_
            uartPrintf(_DEF_CH1, ">> [W5500] DNS Init Timeout! Failed to resolve URL.\r\n");
            #endif
            // 실패 시 무한 루프에 갇히지 않고 함수를 탈출하거나 에러 플래그 리턴
            return; 
        }

        #ifdef _USE_DBG_
        uartPrintf(_DEF_CH1, ">> [W5500] DNS Retry count: %d\r\n", dns_retry);
        #endif
    }

#ifdef _USE_DBG_
    uartPrintf(_DEF_CH1, ">> [W5500] DNS Init done initialization\n\r");

#endif
}

