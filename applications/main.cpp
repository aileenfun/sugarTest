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
#include <rtdevice.h>

#include <board.h>
#include "fal.h"
#define HAL_SPI_MODULE_ENABLED
#include "UartInput.h"
#include "keyApp.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include <rthw.h>
#include"Screen.h"
#include "CDeviceStatus.h"
#include "PWMOut.h"
#include "EC600App.h"
#include "SensorCap.h"
#include "stm32f4xx.h"
#include "PostCloud.h"
#include "easyflash.h"

#include "spi_flash_sfud.h"
#include "drv_spi.h"


int main(void)
{
    rt_hw_spi_device_attach("spi1","spi10",GPIOA,GPIO_PIN_15);
    if(rt_sfud_flash_probe("nor_flash0","spi10"))
    {
       rt_kprintf("rt sfud flash success");
    }
    else {
       rt_kprintf("rt sfud flash error");
    }
    fal_init();
   // fal_init_check();
    easyflash_init();
    m_deviceStatus.readStatus();
    keyApp();
    uart_dma_sample();
    screenShowRst();
    EC600App();
    postCloudApp();
   // CDeviceStatus m_deviceStatus2;

    while (1)
    {

        rt_thread_mdelay(1000);
        //ef_set_env_blob

    }

    //return RT_EOK;
}
