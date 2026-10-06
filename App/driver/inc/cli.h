/*
 * cli.h
 *
 *  Created on: Oct 30, 2023
 *      Author: alren
 */

#ifndef INCLUDE_CLI_H_
#define INCLUDE_CLI_H_

#include "hw_def.h"

typedef struct
{
  uint16_t   argc;
  char     **argv;

  int32_t  (*getData)(uint8_t index);
  float    (*getFloat)(uint8_t index);
  char    *(*getStr)(uint8_t index);
  bool     (*isStr)(uint8_t index, const char *p_str);
} cli_args_t;

bool cliInit(void);
bool cliMain(void);
bool cliAdd(const char *cmd_str, void (*cmd_func)(uint8_t argc, const char **argv));
void cliPrintf(const char *fmt, ...);
bool cliIsStr(const char *p_arg, const char *p_str);
bool cliKeepLoop(void);

int32_t cliGetData(const char *p_arg);

#endif /* INCLUDE_CLI_H_ */
