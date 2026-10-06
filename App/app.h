#ifndef AP_H_
#define AP_H_



#include "util.h"
#include "hw_def.h"
#include "uart.h"
#include "cli.h"
#include "spi.h"
#include "wiz5500.h"
#include "_tcpip.h"

void apInit(void);
void apMain(void);
void ledToggle(void);

#endif /* AP_H_ */