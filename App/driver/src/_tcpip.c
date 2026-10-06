#include "socket.h"
#include "httpServer.h"
#include "w5500.h"
#include "httpUtil.h"
#include <string.h>
#include "main.h"


// 1. 소켓 인덱스 정의 수정
uint8_t sockindex[8] = {0, 1, 2, 3, 4, 5, 6, 7};
// 웹 서버에서 사용할 소켓 번호 지정 (예: 소켓 0번~3번 중 사용)
uint8_t http_send_buf[1024];
uint8_t http_rcv_buf[1024];


#define SOCK_TCPSOCK  0
uint8_t server_ip[4] = {112, 168, 210, 249};
uint16_t server_port = 1883;
uint8_t rx_buffer[256];

void Run_Tcp_Client(void)
{
    int32_t ret;
    uint16_t size = 0;

    switch(getSn_SR(SOCK_TCPSOCK))
    {
        case SOCK_INIT:
            ret = connect(SOCK_TCPSOCK, server_ip, server_port);
            break;

        case SOCK_ESTABLISHED:
            if(getSn_IR(SOCK_TCPSOCK) & Sn_IR_CON) {
                setSn_IR(SOCK_TCPSOCK, Sn_IR_CON);
            }

            // 1. 데이터 수신 확인
            size = getSn_RX_RSR(SOCK_TCPSOCK);
            if(size > 0) {
                if(size > sizeof(rx_buffer) - 1) size = sizeof(rx_buffer) - 1;
                ret = recv(SOCK_TCPSOCK, rx_buffer, size);
                
                if(ret > 0) {
                    rx_buffer[ret] = '\0'; // 문자열 형태 처리를 위해 널 캐릭터 추가

                    // ==========================================
                    // 2. 수신된 데이터에 따른 GPIO 제어 로직
                    // ==========================================
                    // 예: 서버에서 "RELAY_ON" 이라는 문자열을 보내면 릴레이 핀을 켬 (회로도의 R_CTR 등)
                    if(strstr((char*)rx_buffer, "RELAY_ON") != NULL) {
                        // 회로도 상의 릴레이 제어 핀(예: PA11 또는 정의된 핀) High 출력
                        HAL_GPIO_WritePin(R_CTR_GPIO_Port, R_CTR_Pin, GPIO_PIN_SET); 
                    }
                    else if(strstr((char*)rx_buffer, "RELAY_OFF") != NULL) {
                        HAL_GPIO_WritePin(R_CTR_GPIO_Port, R_CTR_Pin, GPIO_PIN_RESET);
                    }

                    // ==========================================
                    // 3. 특정 값이 수신되면 나의 상태 정보 전송
                    // ==========================================
                    // 예: 서버에서 "GET_STATUS"를 요청하면 현재 장비 상태를 전송
                    if(strstr((char*)rx_buffer, "GET_STATUS") != NULL) {
                        const char *status_msg = "STATUS:OK,RELAY:ON\r\n";
                        send(SOCK_TCPSOCK, (uint8_t*)status_msg, strlen(status_msg));
                    }
                }
            }
            break;

        case SOCK_CLOSE_WAIT:
            disconnect(SOCK_TCPSOCK);
            break;

        case SOCK_CLOSED:
            socket(SOCK_TCPSOCK, Sn_MR_TCP, 50000, 0x00);
            break;
            
        default:
            break;
    }
}

void WebServer_Init(void)
{
    uint8_t rss[2] = {2, 3}; // TCP 클라이언트(0번)와 겹치지 않도록 소켓 2, 3번 할당
    httpServer_init(http_send_buf, http_rcv_buf, 2, rss);
    
    // 2. 함수 이름 수정 (reg_httpServer_cb -> reg_httpServer_cbfunc)
    // reg_httpServer_cbfunc(predefined_get_cgi_processor, predefined_set_cgi_processor);
}