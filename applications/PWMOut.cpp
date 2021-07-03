/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-08     alanl       the first version
 */


#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#define PWM0 67
#define PWM1 66//EN1

static void pwm_thread_entry(void *parameter)
{


   rt_pin_mode(PWM1, PIN_MODE_OUTPUT);
   //int keyvalue=rt_pin_read(PWM1);
   rt_pin_mode(PWM0, PIN_MODE_OUTPUT);
   rt_pin_write(PWM0, PIN_LOW);
   rt_pin_write(PWM0, PIN_HIGH);
   rt_pin_write(PWM1, PIN_LOW);
   /*
    while(1)
    {
        //rt_pin_write(PWM1, PIN_HIGH);
        rt_hw_us_delay(10);

        rt_pin_write(PWM1, PIN_LOW);
        rt_hw_us_delay(30);
        //rt_thread_mdelay(1);
    }*/
}
int PWMApp()
{
    int ret=0;
    rt_thread_t thread = rt_thread_create("PWMApp", pwm_thread_entry, RT_NULL, 256, 12, 10);
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
