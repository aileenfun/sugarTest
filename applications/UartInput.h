/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-30     alanliu       the first version
 */
#ifndef RT_THREAD_UARTINPUT_H_
#define RT_THREAD_UARTINPUT_H_


int uart_dma_sample();
int trig1Frame(int s);
float CalcBuff(int sugmode);
int send2PC(int s);
#endif /* RT_THREAD_UARTINPUT_H_ */
