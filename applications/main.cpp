/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-30     RT-Thread    first version
 */

#include <rtthread.h>
#include "UartInput.h"
#include "keyApp.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include <rthw.h>
#include <rtdevice.h>


int main(void)
{
    char strTemp[10];
    uart_dma_sample();
    keyApp();

    rt_thread_mdelay(1000);
    u8g2_ssd1306_12864_hw_i2c_example(0,0,0);
    while (1)
    {

        rt_thread_mdelay(1000);


    }

    return RT_EOK;
}
