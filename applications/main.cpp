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
//#include <rtdevice.h>
//#include <board.h>
#include "fal.h"

#include "UartInput.h"
#include "keyApp.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include <rthw.h>

#include "CDeviceStatus.h"
#include "PWMOut.h"
#include "EC600App.h"
#include "SensorCap.h"
#include "stm32f4xx.h"
#include "PostCloud.h"
#include "easyflash.h"
void get_uid(rt_uint32_t* UID)
{
    UID[0] = (rt_uint32_t)(READ_REG(*((rt_uint32_t*)UID_BASE)));
    UID[1] = (rt_uint32_t)(READ_REG(*((rt_uint32_t*)(UID_BASE + 4U))));
    UID[2] = (rt_uint32_t)(READ_REG(*((rt_uint32_t*)(UID_BASE + 8U))));
}

int main(void)
{
    keyApp();
    fal_init();
   // fal_init_check();
    easyflash_init();
    uart_dma_sample();

    u8g2_ssd1306_12864_hw_i2c_example(0, 0, 0);
    EC600App();
    postCloudApp();
    rt_uint32_t id[3];
    get_uid(id);
    while (1)
    {

        rt_thread_mdelay(1000);
        //ef_set_env_blob

    }

    //return RT_EOK;
}
