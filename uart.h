/*
 * uart_task.h
 *
 *  Created on: Apr 1, 2022
 *      Author: Tigrero
*/



/*
#ifndef MAIN_UART_TASK_H_
#define MAIN_UART_TASK_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"

static const int RX_BUF_SIZE = 1024;

#define TXD_PIN (GPIO_NUM_4)
#define RXD_PIN (GPIO_NUM_5)

void init(void);

int sendData(const char* logName, const char* data);

static void tx_task(void *arg);

static void rx_task(void *arg);



#endif /* MAIN_UART_TASK_H_ */

