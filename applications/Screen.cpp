/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-20     alanl       the first version
 */
#include "Screen.h"
#include <U8g2lib.h>
#include "CDeviceStatus.h"
extern CDeviceStatus m_deviceStatus;
static U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

void screenShowRst()
{
    //char strTemp[10];
    //int high = (int) m_deviceStatus.tempOut;
    //int low = (m_deviceStatus.tempOut - high) * 10;
    //sprintf(strTemp, "%d.%d C", (int) m_deviceStatus.tempOut, low);
    u8g2.begin();
    u8g2.clearBuffer();                         // clear the internal memory
    //u8g2.setFont(u8g2_font_6x13_tr);            // choose a suitable font
    //u8g2.drawStr(1, 18, p);

    //u8g2.setFont(u8g2_font_unifont_t_chinese2);
    //u8g2.drawStr(1, 18, "电量");   // write something to the internal memory
    // u8g2.drawStr(x, y, s)
    u8g2.enableUTF8Print();
    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
    u8g2.setCursor(0, 15);
    u8g2.print("电量：100%  ");
    u8g2.print(m_deviceStatus.tempOut, 1);
    u8g2.print("°C");

    u8g2.setCursor(0, 30);
    u8g2.print("模式： ");
    switch (m_deviceStatus.enum_ModeSN)
    {
    case 0:
        u8g2.print("苹果");
        break;
    case 1:
        u8g2.print("橘子");
        break;
    default:
        u8g2.print("其他");
    }
    u8g2.print(m_deviceStatus.enum_ModeSN);

    u8g2.setCursor(0, 45);
    u8g2.print("   糖度：");
    if (m_deviceStatus.sugerRst < 1)
    {
        u8g2.print("-----");
    }
    else
    {
        u8g2.print(m_deviceStatus.sugerRst, 1);
    }


    u8g2.setCursor(0, 60);
if(m_deviceStatus.netWorkStatus<1)
{
    u8g2.print("网络连接中......");
}
else {
    u8g2.print("网络已连接");
}
u8g2.sendBuffer();     // transfer internal memory to the display
}


