/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-15     alanl       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "stm32f4xx.h"
#include "../libraries/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"
#define SENSOR_CLK 18//pb2
#define SENSOR_OE 17//pb1 always high
#define SENSOR_EOS 16//pb0 no use
#define SENSOR_ST 36//PC4
#define SENSOR_TRG 73//PE9

#define AD_DATA 4//PA4 F_BU_D
#define AD_CLK 5//PA5
#define AD_CNV 6//PA6
#define AD_EN 7//PA7
#define AD_SL  71//PE7

//((GPIO_TypeDef *) ((0x40000000UL + 0x00020000UL) + 0x0400UL))->BSRR= GPIO_PIN_2//
//((GPIO_TypeDef *) ((0x40000000UL + 0x00020000UL) + 0x0400UL))->BSRR=0x1000000//
volatile uint32_t* BSSR_B = (volatile uint32_t*) 0x40020418;
volatile uint32_t* ODR_B = (volatile uint32_t*) 0x40020414;
//#define SENSOR_CLK_HIGH *ODR_B = GPIO_PIN_2
//#define SENSOR_CLK_LOW *ODR_B = ~GPIO_PIN_2
#define SENSOR_CLK_HIGH GPIOB->BSRR = (uint32_t)GPIO_PIN_2
#define SENSOR_CLK_LOW  GPIOB->BSRR = 0x1000000

#define SENSOR_ST_HIGH GPIOC->BSRR = GPIO_PIN_4
#define SENSOR_ST_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_4<<16U

#define AD_CLK_HIGH GPIOA->BSRR=GPIO_PIN_5
#define AD_CLK_LOW GPIOA->BSRR=(uint32_t)GPIO_PIN_5<<16U


#define AD_CNV_HIGH GPIOA->BSRR=GPIO_PIN_6
#define AD_CNV_LOW GPIOA->BSRR=(uint32_t)GPIO_PIN_6<<16U
//#define _USE_RT_PIN
void InitSensorIO()
{
#ifndef _USE_RT_PIN
    GPIO_InitTypeDef GPIO_InitStruct = {0};
      __HAL_RCC_GPIOC_CLK_ENABLE();
      __HAL_RCC_GPIOH_CLK_ENABLE();
      __HAL_RCC_GPIOB_CLK_ENABLE();


      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

      //sensor OE
      GPIO_InitStruct.Pin = GPIO_PIN_1;
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
      HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

      GPIO_InitStruct.Pin = GPIO_PIN_4;
      HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
      //SENSOR_ST_LOW;



      GPIO_InitStruct.Pin = GPIO_PIN_4;//AD DATA PA4
      GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;//AD CLK PA5,AD CNV PA6
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    AD_CLK_LOW;

#else

    rt_pin_mode(SENSOR_CLK,PIN_MODE_OUTPUT);
    rt_pin_mode(SENSOR_ST,PIN_MODE_OUTPUT);
    rt_pin_mode(AD_DATA,PIN_MODE_INPUT);
    rt_pin_mode(AD_CLK,PIN_MODE_OUTPUT);
#endif

    rt_pin_mode(SENSOR_TRG,PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(AD_SL,PIN_MODE_INPUT_PULLUP);

    rt_pin_mode(AD_EN,PIN_MODE_OUTPUT);
    rt_pin_write(AD_EN, 0);
    rt_thread_mdelay(1);
    rt_pin_write(AD_EN, 1);

    rt_pin_mode(SENSOR_OE,PIN_MODE_OUTPUT);
    rt_pin_write(SENSOR_OE, 0);
    rt_thread_mdelay(1);
    rt_pin_write(SENSOR_OE, 1);


}
void toggleSensorClk(int cnt)
{
    while(cnt--)
    {
        //rt_pin_write(SENSOR_CLK, 0);
        //rt_pin_write(SENSOR_CLK, 1);
        GPIOB->ODR ^=GPIO_PIN_2;
    }
}
void toggleADClk(int cnt)
{
    while(cnt--)
    {
        //rt_pin_write(AD_CLK, 0);
        //rt_pin_write(AD_CLK, 1);
        //HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
        GPIOA->ODR^=GPIO_PIN_5;
    }

}
inline void toggleADClk2()
{
    GPIOA->ODR^=GPIO_PIN_5;
    GPIOA->ODR^=GPIO_PIN_5;
}
inline void toggleADClk6()
{
    GPIOA->ODR^=GPIO_PIN_5;
    GPIOA->ODR^=GPIO_PIN_5;
    GPIOA->ODR^=GPIO_PIN_5;
    GPIOA->ODR^=GPIO_PIN_5;
    GPIOA->ODR^=GPIO_PIN_5;
    GPIOA->ODR^=GPIO_PIN_5;
}

inline rt_uint16_t readAD()
{
    rt_uint16_t rst=0;
    rt_uint8_t cnt=0;
    //while(cnt<16)
    {
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        //rst+=rst<<cnt;

        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;

        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        AD_CLK_HIGH;
        rst = GPIOA->IDR & GPIO_PIN_4;
        AD_CLK_LOW;
        //cnt++;
    }

}

/*
rt_uint16_t readADPin()
{
    uint8_t bitstatus = 0x00;
    if ((GPIOA->IDR & GPIO_PIN_4) != (uint32_t)1)
      {
        bitstatus = (uint8_t)1;
      }
      else
      {
        bitstatus = (uint8_t)0;
      }
      return bitstatus;
}
*/
void SensorCapData(rt_uint16_t* adlist)
{
    int sensor_clk_cnt=0;
    //rt_uint16_t adlist[256];
    rt_uint32_t cnt=0;
    while(1)
    {
        /*
        rt_uint32_t cnt=0;
        SENSOR_CLK_LOW;
        SENSOR_ST_HIGH;
        SENSOR_CLK_HIGH;
        toggleSensorClk(4);//least 4 clk;
        toggleSensorClk(50);
        SENSOR_ST_LOW;
        SENSOR_CLK_LOW;
        toggleSensorClk(88);
*/

        for(int i=0;i<255;i++)
        {
            SENSOR_CLK_HIGH;
            AD_CNV_HIGH;
            //toggleADClk(2);
            toggleADClk2();
            AD_CLK_LOW;
            AD_CNV_LOW;
            toggleADClk6();
            AD_CLK_LOW;
            readAD();
            SENSOR_CLK_LOW;
        }

        //
        //rt_thread_mdelay(1000);
    }
}
