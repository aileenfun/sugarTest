/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-09     alanl       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#define POWER_EN 62
#define U_NB_POWER_KEY 41
#define U_NB_WAKEUP 38
#define U_NB_STATUS 40



static void EC600_thread_entry(void *parameter)
{
    rt_pin_mode(POWER_EN, PIN_MODE_OUTPUT);

    rt_pin_write(POWER_EN, PIN_HIGH);//enable
    rt_pin_mode(U_NB_POWER_KEY, PIN_MODE_OUTPUT);
    rt_pin_write(U_NB_POWER_KEY, PIN_HIGH);//power
    rt_thread_mdelay(20000);
    rt_pin_write(U_NB_POWER_KEY, PIN_LOW);//power
    rt_thread_mdelay(800);
    rt_pin_write(U_NB_POWER_KEY, PIN_HIGH);//power
    rt_kprintf("power down\n \r");
}

int EC600App()
{
    int ret=0;
       rt_thread_t thread = rt_thread_create("EC600App", EC600_thread_entry, RT_NULL, 256, 12, 10);
       if (thread != RT_NULL)
       {
             rt_thread_startup(thread);
         }
         else
         {
             ret = RT_ERROR;
         }

         return ret;
}

