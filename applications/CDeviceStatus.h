/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-17     alanl       the first version
 */
#ifndef APPLICATIONS_CDEVICESTATUS_H_
#define APPLICATIONS_CDEVICESTATUS_H_

class CDeviceStatus
{
public:
    CDeviceStatus();
    virtual ~CDeviceStatus();
    float sugerRst;
    int testMode;
    int netWorkStatus;
    int tempOut;
};

#endif /* APPLICATIONS_CDEVICESTATUS_H_ */
