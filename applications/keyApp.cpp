/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-14     alanl       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "UartInput.h"

#include "Adafruit_MLX90614.h"
#include "CDeviceStatus.h"
#include "SensorCap.h"
#include "PostCloud.h"
#include"Screen.h"
#include <drv_spi.h>
#define KEY2ARM 106//PG10
#define ARM2FPGA_KEY  44//PC12

#define POWER_IN 11// state check
#define POWER_OUT 12
#define FPGA_PWR 35//pc3
#define KEY1 48//PD10
#define KEY2 49//PD11
#define POWER_OFF_TIME 5*RT_TICK_PER_SECOND
#define _TESTED
#define EVENT_FLAG3 1

// Check https://github.com/olikraus/u8g2/wiki/u8g2setupcpp for all supported devices

static Adafruit_MLX90614 mlx = Adafruit_MLX90614();

static void key_thread_entry(void *parameter)
{
    float tempout = 0;
    float sugrst = 0;
    int sugmode = 0;
    int keyvalue = 0;
    //int keyvalue2=0;
    rt_pin_mode(KEY2ARM, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(ARM2FPGA_KEY, PIN_MODE_OUTPUT);
    rt_pin_mode(FPGA_PWR, PIN_MODE_OUTPUT);
    rt_pin_write(FPGA_PWR, PIN_HIGH);
    rt_pin_write(ARM2FPGA_KEY, PIN_HIGH);

    rt_pin_mode(POWER_IN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY1, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY2, PIN_MODE_INPUT_PULLUP);

    rt_pin_mode(POWER_OUT, PIN_MODE_OUTPUT);
    rt_pin_write(POWER_OUT, PIN_HIGH);

    rt_tick_t lasttime = rt_tick_get();



    while (1)
    {
#ifdef _TESTED
        //power on
        keyvalue = rt_pin_read(POWER_IN);
        if (keyvalue == 0)
        {
            int temp = rt_tick_get() - lasttime;
            if (temp > POWER_OFF_TIME)
            {
                //power off
                rt_pin_write(POWER_OUT, 0);

            }
            else
            {
                rt_pin_write(POWER_OUT, 1);
            }
        }
        else
        {
            rt_pin_write(POWER_OUT, 1);
            lasttime = rt_tick_get();
        }
#endif

//switch mode
        keyvalue = rt_pin_read(KEY2);
        if (keyvalue == 0)
        {
            rt_thread_mdelay(100);
            keyvalue = rt_pin_read(KEY2);
            if (keyvalue == 0)
            {
                sugmode++;
                if (sugmode > 4)
                    sugmode = 0;
                m_deviceStatus.enum_ModeSN = sugmode;
                screenShowRst();
            }
        }
//start process
        keyvalue = rt_pin_read(KEY1);
        if (keyvalue == 0)
        {
            rt_thread_mdelay(100);
            keyvalue = rt_pin_read(KEY1);
            if (keyvalue == 0)
            {

                trig1Frame(0);
                rt_thread_mdelay(1000);
//                   send2P2C(0);
                rt_thread_mdelay(1000);
                trig1Frame(1);
                rt_thread_mdelay(1000);
//                   sendPC(1);
                sugrst = CalcBuff(sugmode);
                if (sugrst > 17)
                {
                    int h = (int) sugrst;
                    sugrst = 16.0 + sugrst - h;
                }
                if (sugrst < 9)
                {
                    int h = (int) sugrst;
                    sugrst = 10.0 + sugrst - (float) h;
                }

                tempout = (float) mlx.readObjectTempC();
                m_deviceStatus.sugerRst = sugrst;
                m_deviceStatus.tempOut = 0;//tempout;
                screenShowRst();

                rt_thread_mdelay(500);
                rt_event_send(&ev_postCloud, EVENT_FLAG3);
                // char **temp;
                // webclient_get_test(1,temp);
            }
        }
        rt_thread_mdelay(100);

    }

}
int keyApp()
{
    int ret = 0;

    rt_thread_t thread = rt_thread_create("key", key_thread_entry, RT_NULL, 4096, 11, 10);
    if (mlx.begin() < 0)
    {

    }
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
