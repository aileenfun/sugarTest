/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-03     alanl       the first version
 */
#ifndef APPLICATIONS_CFRUITMODEL_H_
#define APPLICATIONS_CFRUITMODEL_H_
#include <string.h>
class CFruitModel
{
public:
    CFruitModel();
    virtual ~CFruitModel();
    string ModelSN;//modelsn0001
    string Label;//梨
    string ModelFUNC;//"modelfuntion256"
    int  Exposure;//60ms
    int DetectRepert;//
    int DetectFrequency;
    float DetectCalibLightRatio1;//
    int PreMethod;//1,2
    float TempCalibK;
    float TempCalibB;
    float input1[256];
    float input2[256];
    float input3;
};

#endif /* APPLICATIONS_CFRUITMODEL_H_ */
