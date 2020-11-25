/*************************************************** 
  This is a library for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_MLX90614.h"
#include <rtdevice.h>
Adafruit_MLX90614::Adafruit_MLX90614(rt_uint8_t i2caddr) {
  _addr = i2caddr;
}


int Adafruit_MLX90614::begin() {
  //Wire.begin();
         /* I2C总线设备句柄 */

    /* 查找I2C总线设备，获取I2C总线设备句柄 */
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find("i2c1");
     if (i2c_bus == RT_NULL)
        return -1;
  /*
  for (uint8_t i=0; i<0x20; i++) {
    Serial.print(i); Serial.print(" = ");
    Serial.println(read16(i), HEX);
  }
  */
  return 1;
}

//////////////////////////////////////////////////////


double Adafruit_MLX90614::readObjectTempF(void) {
  return (readTemp(MLX90614_TOBJ1) * 9 / 5) + 32;
}


double Adafruit_MLX90614::readAmbientTempF(void) {
  return (readTemp(MLX90614_TA) * 9 / 5) + 32;
}

double Adafruit_MLX90614::readObjectTempC(void) {
  return readTemp(MLX90614_TOBJ1);
}


double Adafruit_MLX90614::readAmbientTempC(void) {
  return readTemp(MLX90614_TA);
}

float Adafruit_MLX90614::readTemp(rt_uint8_t reg) {
  float temp;
  
  temp = read16(reg)*0.02;
  temp  -= 273.15;
  return temp;
}

/*********************************************************************/

rt_uint16_t Adafruit_MLX90614::read16(rt_uint8_t a) {
/*
  Wire.beginTransmission(_addr); // start transmission to device 
  Wire.write(a); // sends register address to read from
  Wire.endTransmission(false); // end transmission
  
  Wire.requestFrom(_addr, (uint8_t)3);// send data n-bytes read
  ret = Wire.read(); // receive DATA
  ret |= Wire.read() << 8; // receive DATA

  uint8_t pec = Wire.read();
*/
  struct rt_i2c_msg msgs[2];
  rt_uint16_t rst=0;
  rt_uint8_t buff[3];
  buff[0]=a;
  msgs[0].addr = _addr;     /* 从机地址 */
  msgs[0].flags = RT_I2C_WR;     /* 读标志 */
  msgs[0].buf = buff;             /* 读写数据缓冲区指针　*/
  msgs[0].len = 1;             /* 读写数据字节数 */

  msgs[1].addr = _addr;     /* 从机地址 */
  msgs[1].flags = RT_I2C_RD;     /* 读标志 */
        msgs[1].buf = buff;             /* 读写数据缓冲区指针　*/
        msgs[1].len = 3;             /* 读写数据字节数 */

  int it=rt_i2c_transfer(i2c_bus, msgs, 2);
  if(it>0)
     {
          rst=buff[1];
          rst=(rst<<8)+buff[0];
          return rst;
     }

}
