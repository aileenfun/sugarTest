/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-14     alanl       the first version
 */


#include "helperfunc.h"
#include <string.h>
#include <stdlib.h>
std::string int2string(int s)
{
    char buffer [20];
    return itoa(s,buffer,10);
}
