/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-02     alanl       the first version
 */
#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_


//#include <rtconfig.h>
//#include <board.h>

#define FLASH_SIZE_GRANULARITY_16K   (4 * 16 * 1024)
#define FLASH_SIZE_GRANULARITY_64K   (1 * 64 * 1024)
#define FLASH_SIZE_GRANULARITY_128K  (7 * 128 * 1024)
#define STM32_FLASH_START_ADRESS_16K  STM32_FLASH_START_ADRESS
#define STM32_FLASH_START_ADRESS_64K  (STM32_FLASH_START_ADRESS_16K + FLASH_SIZE_GRANULARITY_16K)
#define STM32_FLASH_START_ADRESS_128K (STM32_FLASH_START_ADRESS_64K + FLASH_SIZE_GRANULARITY_64K)
/* ===================== Flash device Configuration ========================= */
extern const struct fal_flash_dev stm32_onchip_flash_16k;
extern const struct fal_flash_dev stm32_onchip_flash_64k;
extern const struct fal_flash_dev stm32_onchip_flash_128k;
extern struct fal_flash_dev nor_flash0;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &stm32_onchip_flash_16k,                                           \
    &stm32_onchip_flash_64k,                                           \
    &stm32_onchip_flash_128k,                                           \
    &nor_flash0,\
}
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                               \
{                                                                                    \
    {FAL_PART_MAGIC_WORD,        "bl",     "onchip_flash_16k",         0,   64*1024, 0}, \
    {FAL_PART_MAGIC_WORD,       "app",     "onchip_flash_64k",   0,  64*1024, 0}, \
    {FAL_PART_MAGIC_WORD,       "app2",     "onchip_flash_128k",   0,  4*128*1024, 0}, \
    {FAL_PART_MAGIC_WORD,  "ota", "onchip_flash_128k", 4*128*1024, 2*128*1024, 0}, \
    {FAL_PART_MAGIC_WORD,  "easyflash", "nor_flash0", 0, 4*1024*1024, 0}, \
}//0x0808000,start ADDR_FLASH_SECTOR_8
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif
