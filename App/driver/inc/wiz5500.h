
#ifndef INCLUDE_WIZ5500_H_
#define INCLUDE_WIZ5500_H_

#include "hw_def.h"
#include "spi.h"
#include "wizchip_conf.h"
#include "socket.h"
#include "inttypes.h"
#include "Internet/MQTT/MQTTClient.h"
#include "Internet/DNS/dns.h"
#include "DNS/dns.h"
// #include "mqtt_interface.h"
#include "uart.h"
#include "cJSON.h"

bool w5500Init(void);
bool w5500Info(void);
void print_network_information(void);
void DnsInit(void);
void wizchip_initialize(void);
// void messageArrived(MessageData* md);
// void MqttRun(void);
// void MqttSendData(char *data);
// void Loopback_Test(void);
// void repeating_timer_callback(void);

#endif /* INCLUDE_IZ5500_H_ */
