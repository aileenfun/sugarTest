/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-12     alanl       the first version
 */
#include "CalcSugar.h"
const float input00[256]={34.33333333,72.66666667,55,55.33333333,88.33333333,47,33,91.33333333,64,-16.66666667,34.66666667,29,-3.666666667,25.33333333,65.66666667,19,6.666666667,-5.333333333,3,-13.66666667,4,9.666666667,17.33333333,16,36.66666667,-5.666666667,-11,0.666666667,20.33333333,60.66666667,-15.66666667,4.333333333,69.33333333,31,16.66666667,1.666666667,16.66666667,24.33333333,-6,9.333333333,12.33333333,-6.333333333,-10.66666667,-19.33333333,18.66666667,-2,13.33333333,8,-17.33333333,12.66666667,21.33333333,24.66666667,-3.666666667,-11.33333333,4.666666667,-4.666666667,41,-0.666666667,-19,2.666666667,-33,950.3333333,2858,2378.666667,3214.666667,4517.666667,4571.666667,5443,6446.666667,7750.666667,8952.666667,10187,11486.33333,12441.66667,13566,14538,15545.66667,16616.33333,18044.33333,19054.33333,20566.33333,22093,23575.33333,25226,26974.66667,28949,30554,32675.33333,34646.66667,35784,36823.66667,37499.33333,39070.33333,40210.33333,42442,44406.33333,47622.66667,49239.66667,50786.33333,51871,52535.33333,53420.33333,54131.66667,54941,55619.66667,56151.66667,56360.33333,56648.66667,56456.66667,56783,56633.33333,57495,57911,57882,57640.33333,57509.66667,57034.33333,57111.33333,56541.66667,56582,57627,57500.66667,57569,57718,57519.66667,58008.66667,57301,57595.33333,58101.66667,58500,57780.66667,57430.33333,56905.66667,56628.66667,56456.66667,56190,56173,56275,55890.33333,55558,55348.66667,54645,54184.66667,53694.33333,53754.66667,53214.33333,52659,51883,50804.66667,50045.66667,48861,48010.33333,47257,45986.66667,44209,42705.33333,40880,39304.66667,37449,35804.66667,35085,33277.33333,31935,30499.33333,29070.33333,27707,26226.66667,25003.66667,23811.33333,22982.33333,21735,20450,19231.66667,18059.66667,17023.33333,15922.33333,15098.66667,13983,13114,12270.66667,11434.33333,10577,9823,9042.333333,8756,8113.333333,7415,6922.333333,6375.666667,6051.333333,5489.666667,5102.666667,4808.333333,4732,4263,4070,3753.666667,3556,3451.666667,3569,3485.333333,3389,3115.333333,3019,2904,2935.333333,2990,2783.666667,2836.333333,2815,2862.666667,2671.333333,2915.666667,2681,2695,2369,2566.333333,2552,2553.333333,2485.333333,2535,2370.666667,2421.666667,2273.666667,2514.333333,2327.333333,2624,2394,2375.666667,2297,2163.333333,1963.333333,2086.333333,1786.666667,1591,1912,1850,1606.333333,1754.333333,1667,1996.666667,1952.333333,1626.666667,1965.666667,1980.333333,1659.666667,1627.333333,1345,1904.666667,1763.666667,1628.333333,2048.333333,1724,1708.333333,1901.666667,1529};
const float input01[256]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.045747728,-0.043831116,-0.026697643,0.038306383,0.044442787,0.033032685,0.040696175,0.016580709,0.019542894,-0.001656445,-0.020945813,-0.042173521,-0.034100696,-0.03539903,-0.015102511,0.011105301,0.057890633,0.090188524,0.102900519,0.087116443,0.056603615,0.051632697,0.008646275,0.000856905,-0.027852351,-0.015958243,-0.053239801,-0.044859643,-0.053571819,-0.049212715,-0.035591623,-0.029307029,-0.021490604,-0.016077765,-0.007188881,-0.005144568,-0.007098101,-0.002157936,0.001313736,-0.004845848,0.011454112,-6.11E-05,0.016105295,0.000347922,-0.000357459,0.002661237,0.003354283,-0.001004051,-0.006639152,-0.001323588,-0.01650759,-0.014388654,-0.024267997,-0.029502879,-0.033534982,-0.026577078,-0.025296073,-0.019092655,-0.007287442,-0.01453636,-0.012096422,-0.014135956,-0.00522811,-0.016189049,-0.005778175,-0.010042099,-0.010841118,-0.014356169,-0.007394186,-0.019202352,-0.007353403,-0.020048371,-0.01109982,-0.012033598,-0.005485604,-0.017412909,-0.007966791,-0.011566589,-0.01539475,-0.012911132,-0.009879662,-0.018717336,-0.013515306,-0.022982862,-0.021004436,-0.020151782,-0.019773469,-0.024441829,-0.017103942,-0.024189837,-0.00896964,-0.009275521,0.004724985,-0.01227887,0.01966212,-0.007877861,-0.009577738,-0.017232514,0.02062996,4.76E-18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const float input02[256]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.228920774,1.5056167,1.658057754,4.685336639,5.201899878,13.50390817,3.179502381,12.19370868,1.87221845,-0.026621075,-2.113353014,-14.01203572,-8.60223151,-1.876095524,6.717193456,-9.896914982,-7.221743744,-10.54817012,-3.174820274,4.461228805,-9.064883001,1.021871492,0.669334232,0.807082222,9.781834552,1.577059642,9.204560309,10.1111707,9.429169888,8.944588999,-9.795966422,2.203715405,-4.513262372,-2.211483837,-4.466183725,-5.451400816,2.090765916,-3.480707123,1.617458605,-3.296958659,7.103224769,-8.02E+00,-9.624337946,4.156274673,1.547776203,-1.347096124,-5.742297339,0.861537196,-3.012201997,1.832734201,3.880575708,3.132632252,9.222805959,12.32340293,9.772762854,13.22360865,0.802749004,9.836483477,-3.634149276,5.111326871,4.261170769,-0.763052823,5.566419997,-1.469009321,-0.043309166,-0.802380506,-1.356321906,6.724585476,-3.812650116,0.090496492,-1.728459941,-0.197693321,0.420053442,-4.791858823,-4.719794562,-1.677611371,1.598734833,-3.13886593,2.518184499,3.117514463,-0.795701351,9.756329623,-0.937009398,7.052497181,8.479180722,11.70772686,2.055752176,15.43269006,-2.476711696,16.5324162,0.884738145,10.82907806,-1.394912135,-1.980254896,5.816311086,-4.924802942,-2.938922394,-4.965385343,-11.83778482,1.67E-13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const float input03=13.928606741573030;


const float input10[256]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,16,214,1261,1636,1497,1435,1359,2969,3476,4845,4460,5016,5711,6213,6742,7340,8024,8593,9499,10331,11217,12165,13229,14392,15680,17250,19022,20918,22736,24876,26628,27940,29321,30736,32429,34866,36905,40459,42258,44939,46520,48344,49720,51030,51979,53176,53990,54343,54334,54451,54556,54292,54422,54795,54709,53932,54136,53420,53395,52723,52575,53250,53006,52912,53270,52808,53069,52550,52714,52971,53244,52416,52154,51954,51491,51263,50930,51449,51201,50689,50624,50102,49472,49030,48107,48576,47608,47008,45890,44638,43580,42480,41287,40575,39501,37832,36526,35159,34090,32609,31346,30646,29470,28020,27089,25842,24573,23274,22177,21279,20231,19109,18042,16846,15904,15194,14297,13459,12551,11741,10989,10126,9608,8836,8135,7929,7356,6673,6372,5800,5526,5119,4930,4636,4594,4445,4288,4243,4028,3901,3854,3731,3336,3533,3278,2871,1680,1251,1601,1212,1568,1217,2003,1202,1808,1131,1173,1053,926,1085,935,857,818,869,1044,1367,1189,1173,1097,1635,1622,1737,1636,1725,1788,1783,1590,1872,1816,1779,1712,1782,1827,1828,1782,1901,1777,1723,1634,1829,1823,1259,1757,1850,1701,1836,1617};
const float input11[256]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.007866459,0.014442087,0.060409716,-0.029328107,0.020426018,0.00112909,-0.021753646,-0.031774759,-0.013710589,-0.011696587,-0.021126777,-0.026228019,0.005510394,0.030025006,0.046051365,0.059786778,0.063714525,0.048391712,0.034186209,0.023787471,0.007181455,0.00654013,-0.009743779,-0.01857248,-0.018958024,-0.028202248,-0.020569101,-0.02905473,-0.015796874,-0.015495328,-0.013054459,-0.003541802,-0.009663178,0.001267587,-0.001385881,0.00297384,-0.003521074,-0.000786883,-0.003680711,-0.000485689,0.00485124,-0.00036399,-1.15E-03,-0.000636108,-0.012822148,-0.001615102,-0.007603033,-0.00783049,-0.012872896,-0.015931066,-0.019825665,-0.017901135,-0.021441157,-0.016581523,-0.017877064,-0.006247782,-0.016042655,-0.006650993,-0.007888017,-0.013007968,-0.007750512,-0.013112392,-0.00646676,-0.015750633,-0.008976447,-0.010808134,-0.007957337,-0.014930094,-0.008019931,-0.013437653,-0.010866539,-0.01052745,-0.006024968,-0.013333196,-0.008626697,-0.008941362,-0.009184693,-0.015145159,-0.010392425,-0.01648448,-0.013188938,-0.018670156,-0.01669166,-0.017596022,-0.014816984,-0.015724536,-0.014597998,-0.013227689,-0.010393899,-0.01289952,-0.017987405,-0.011324902,-0.012071062,-0.000414573,-0.002578018,-0.000537683,0.000916742,-0.003355312,0.008185771,-8.24E-03,0.014472493,0.007404005,0.003963051,0.003497369,0.012737713,0.004953894,0.007664013,-0.0021837,0.015256036,0.007334047,-0.00294382,0.020208437,0.018175459,0.006735994,0.013634415,0.010043063,0.02121415,0.001737494,0.026957061,0.010009205,-0.003001793,0.007360658,0.027945639,0.002579537,0.007523613,0.00719202,0.008800459,-0.09109208,0.077735557,0.024453205,0.0104788,0.028443415,0.064327845,0.27661212,0.185547342,-0.166092363,0.286569792,-0.353974862,0.210141322,-0.728526183,0.60962187,-0.256009224,0.451986818,-0.024404205,0.012230401,0.17958223,-0.237959511,0.1687706,0.170501241,0.006032718,0.00765967,-0.253958183,-0.305431147,-0.283527234,-0.189331848,0.397157947,-0.127935897,-0.090129983,0.002833316,-0.042528212,-0.096295003,0.187023001,-0.065300217,-0.263511388,0.188476966,0.028802789,-0.038653814,-0.184163783,-0.087470316,0.14727964,-0.083956744,-0.038041177,0.06944745,0.054739106,0.173335071,-0.294004502,-0.043102283,0.019047484,-0.025939931,-0.084849194,0.10752943,-0.058155135,0.017803896,-0.032839982,-1.57153E-17};
const float input12[256]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.344462508,3.414012926,2.575859196,4.132841119,10.29552155,13.44719318,6.667944586,21.92005767,24.57302404,28.80436479,11.46694514,9.063138435,10.84180171,34.47030984,37.30943051,9.344495024,14.78442891,18.51835707,1.188209863,19.84672606,10.4305217,11.05548616,-2.122447184,33.66726858,17.01667633,26.50935835,36.02248572,-2.981228589,7.151878178,16.9056907,-5.374710073,-0.930817978,7.994593896,1.484913955,-1.022747003,15.89997769,4.222215223,-1.849445231,-0.601762913,-2.546570618,4.502455121,11.51034386,2.665195904,1.86E+00,6.614848105,-12.00246522,-5.423235586,4.394813731,15.94087705,-0.063851034,39.00964591,16.29760062,-0.030470804,11.6960511,5.614454608,-8.522492558,-1.802220743,21.48228736,0.362709385,12.78231095,4.838765392,11.14249637,-10.17253577,-0.578846728,1.951093617,-6.056274983,-6.688115463,8.784600667,-1.708225348,5.538907552,-20.51340195,-2.147831629,-14.24193734,5.650581441,-12.24684148,4.720679728,-3.773026062,22.67975347,8.720340038,2.385741444,7.699779697,22.44563951,-3.721425443,-1.043021346,13.14762023,5.066523706,23.55052636,26.20167414,40.94116977,-14.33372975,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const float input13=13.72;
struct paramInputStruct paramInput[2];
void initSugarCalcParam()
{

    paramInput[0].input0=input00;//{34.33333333,72.66666667,55,55.33333333,88.33333333,47,33,91.33333333,64,-16.66666667,34.66666667,29,-3.666666667,25.33333333,65.66666667,19,6.666666667,-5.333333333,3,-13.66666667,4,9.666666667,17.33333333,16,36.66666667,-5.666666667,-11,0.666666667,20.33333333,60.66666667,-15.66666667,4.333333333,69.33333333,31,16.66666667,1.666666667,16.66666667,24.33333333,-6,9.333333333,12.33333333,-6.333333333,-10.66666667,-19.33333333,18.66666667,-2,13.33333333,8,-17.33333333,12.66666667,21.33333333,24.66666667,-3.666666667,-11.33333333,4.666666667,-4.666666667,41,-0.666666667,-19,2.666666667,-33,950.3333333,2858,2378.666667,3214.666667,4517.666667,4571.666667,5443,6446.666667,7750.666667,8952.666667,10187,11486.33333,12441.66667,13566,14538,15545.66667,16616.33333,18044.33333,19054.33333,20566.33333,22093,23575.33333,25226,26974.66667,28949,30554,32675.33333,34646.66667,35784,36823.66667,37499.33333,39070.33333,40210.33333,42442,44406.33333,47622.66667,49239.66667,50786.33333,51871,52535.33333,53420.33333,54131.66667,54941,55619.66667,56151.66667,56360.33333,56648.66667,56456.66667,56783,56633.33333,57495,57911,57882,57640.33333,57509.66667,57034.33333,57111.33333,56541.66667,56582,57627,57500.66667,57569,57718,57519.66667,58008.66667,57301,57595.33333,58101.66667,58500,57780.66667,57430.33333,56905.66667,56628.66667,56456.66667,56190,56173,56275,55890.33333,55558,55348.66667,54645,54184.66667,53694.33333,53754.66667,53214.33333,52659,51883,50804.66667,50045.66667,48861,48010.33333,47257,45986.66667,44209,42705.33333,40880,39304.66667,37449,35804.66667,35085,33277.33333,31935,30499.33333,29070.33333,27707,26226.66667,25003.66667,23811.33333,22982.33333,21735,20450,19231.66667,18059.66667,17023.33333,15922.33333,15098.66667,13983,13114,12270.66667,11434.33333,10577,9823,9042.333333,8756,8113.333333,7415,6922.333333,6375.666667,6051.333333,5489.666667,5102.666667,4808.333333,4732,4263,4070,3753.666667,3556,3451.666667,3569,3485.333333,3389,3115.333333,3019,2904,2935.333333,2990,2783.666667,2836.333333,2815,2862.666667,2671.333333,2915.666667,2681,2695,2369,2566.333333,2552,2553.333333,2485.333333,2535,2370.666667,2421.666667,2273.666667,2514.333333,2327.333333,2624,2394,2375.666667,2297,2163.333333,1963.333333,2086.333333,1786.666667,1591,1912,1850,1606.333333,1754.333333,1667,1996.666667,1952.333333,1626.666667,1965.666667,1980.333333,1659.666667,1627.333333,1345,1904.666667,1763.666667,1628.333333,2048.333333,1724,1708.333333,1901.666667,1529};
    paramInput[0].input1=input01;//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.045747728,-0.043831116,-0.026697643,0.038306383,0.044442787,0.033032685,0.040696175,0.016580709,0.019542894,-0.001656445,-0.020945813,-0.042173521,-0.034100696,-0.03539903,-0.015102511,0.011105301,0.057890633,0.090188524,0.102900519,0.087116443,0.056603615,0.051632697,0.008646275,0.000856905,-0.027852351,-0.015958243,-0.053239801,-0.044859643,-0.053571819,-0.049212715,-0.035591623,-0.029307029,-0.021490604,-0.016077765,-0.007188881,-0.005144568,-0.007098101,-0.002157936,0.001313736,-0.004845848,0.011454112,-6.11E-05,0.016105295,0.000347922,-0.000357459,0.002661237,0.003354283,-0.001004051,-0.006639152,-0.001323588,-0.01650759,-0.014388654,-0.024267997,-0.029502879,-0.033534982,-0.026577078,-0.025296073,-0.019092655,-0.007287442,-0.01453636,-0.012096422,-0.014135956,-0.00522811,-0.016189049,-0.005778175,-0.010042099,-0.010841118,-0.014356169,-0.007394186,-0.019202352,-0.007353403,-0.020048371,-0.01109982,-0.012033598,-0.005485604,-0.017412909,-0.007966791,-0.011566589,-0.01539475,-0.012911132,-0.009879662,-0.018717336,-0.013515306,-0.022982862,-0.021004436,-0.020151782,-0.019773469,-0.024441829,-0.017103942,-0.024189837,-0.00896964,-0.009275521,0.004724985,-0.01227887,0.01966212,-0.007877861,-0.009577738,-0.017232514,0.02062996,4.76E-18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    paramInput[0].input2=input02;//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.228920774,1.5056167,1.658057754,4.685336639,5.201899878,13.50390817,3.179502381,12.19370868,1.87221845,-0.026621075,-2.113353014,-14.01203572,-8.60223151,-1.876095524,6.717193456,-9.896914982,-7.221743744,-10.54817012,-3.174820274,4.461228805,-9.064883001,1.021871492,0.669334232,0.807082222,9.781834552,1.577059642,9.204560309,10.1111707,9.429169888,8.944588999,-9.795966422,2.203715405,-4.513262372,-2.211483837,-4.466183725,-5.451400816,2.090765916,-3.480707123,1.617458605,-3.296958659,7.103224769,-8.02E+00,-9.624337946,4.156274673,1.547776203,-1.347096124,-5.742297339,0.861537196,-3.012201997,1.832734201,3.880575708,3.132632252,9.222805959,12.32340293,9.772762854,13.22360865,0.802749004,9.836483477,-3.634149276,5.111326871,4.261170769,-0.763052823,5.566419997,-1.469009321,-0.043309166,-0.802380506,-1.356321906,6.724585476,-3.812650116,0.090496492,-1.728459941,-0.197693321,0.420053442,-4.791858823,-4.719794562,-1.677611371,1.598734833,-3.13886593,2.518184499,3.117514463,-0.795701351,9.756329623,-0.937009398,7.052497181,8.479180722,11.70772686,2.055752176,15.43269006,-2.476711696,16.5324162,0.884738145,10.82907806,-1.394912135,-1.980254896,5.816311086,-4.924802942,-2.938922394,-4.965385343,-11.83778482,1.67E-13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    paramInput[0].input3=input03;

    paramInput[1].input0=input10;//{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,16,214,1261,1636,1497,1435,1359,2969,3476,4845,4460,5016,5711,6213,6742,7340,8024,8593,9499,10331,11217,12165,13229,14392,15680,17250,19022,20918,22736,24876,26628,27940,29321,30736,32429,34866,36905,40459,42258,44939,46520,48344,49720,51030,51979,53176,53990,54343,54334,54451,54556,54292,54422,54795,54709,53932,54136,53420,53395,52723,52575,53250,53006,52912,53270,52808,53069,52550,52714,52971,53244,52416,52154,51954,51491,51263,50930,51449,51201,50689,50624,50102,49472,49030,48107,48576,47608,47008,45890,44638,43580,42480,41287,40575,39501,37832,36526,35159,34090,32609,31346,30646,29470,28020,27089,25842,24573,23274,22177,21279,20231,19109,18042,16846,15904,15194,14297,13459,12551,11741,10989,10126,9608,8836,8135,7929,7356,6673,6372,5800,5526,5119,4930,4636,4594,4445,4288,4243,4028,3901,3854,3731,3336,3533,3278,2871,1680,1251,1601,1212,1568,1217,2003,1202,1808,1131,1173,1053,926,1085,935,857,818,869,1044,1367,1189,1173,1097,1635,1622,1737,1636,1725,1788,1783,1590,1872,1816,1779,1712,1782,1827,1828,1782,1901,1777,1723,1634,1829,1823,1259,1757,1850,1701,1836,1617};
    paramInput[1].input1=input11;//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.007866459,0.014442087,0.060409716,-0.029328107,0.020426018,0.00112909,-0.021753646,-0.031774759,-0.013710589,-0.011696587,-0.021126777,-0.026228019,0.005510394,0.030025006,0.046051365,0.059786778,0.063714525,0.048391712,0.034186209,0.023787471,0.007181455,0.00654013,-0.009743779,-0.01857248,-0.018958024,-0.028202248,-0.020569101,-0.02905473,-0.015796874,-0.015495328,-0.013054459,-0.003541802,-0.009663178,0.001267587,-0.001385881,0.00297384,-0.003521074,-0.000786883,-0.003680711,-0.000485689,0.00485124,-0.00036399,-1.15E-03,-0.000636108,-0.012822148,-0.001615102,-0.007603033,-0.00783049,-0.012872896,-0.015931066,-0.019825665,-0.017901135,-0.021441157,-0.016581523,-0.017877064,-0.006247782,-0.016042655,-0.006650993,-0.007888017,-0.013007968,-0.007750512,-0.013112392,-0.00646676,-0.015750633,-0.008976447,-0.010808134,-0.007957337,-0.014930094,-0.008019931,-0.013437653,-0.010866539,-0.01052745,-0.006024968,-0.013333196,-0.008626697,-0.008941362,-0.009184693,-0.015145159,-0.010392425,-0.01648448,-0.013188938,-0.018670156,-0.01669166,-0.017596022,-0.014816984,-0.015724536,-0.014597998,-0.013227689,-0.010393899,-0.01289952,-0.017987405,-0.011324902,-0.012071062,-0.000414573,-0.002578018,-0.000537683,0.000916742,-0.003355312,0.008185771,-8.24E-03,0.014472493,0.007404005,0.003963051,0.003497369,0.012737713,0.004953894,0.007664013,-0.0021837,0.015256036,0.007334047,-0.00294382,0.020208437,0.018175459,0.006735994,0.013634415,0.010043063,0.02121415,0.001737494,0.026957061,0.010009205,-0.003001793,0.007360658,0.027945639,0.002579537,0.007523613,0.00719202,0.008800459,-0.09109208,0.077735557,0.024453205,0.0104788,0.028443415,0.064327845,0.27661212,0.185547342,-0.166092363,0.286569792,-0.353974862,0.210141322,-0.728526183,0.60962187,-0.256009224,0.451986818,-0.024404205,0.012230401,0.17958223,-0.237959511,0.1687706,0.170501241,0.006032718,0.00765967,-0.253958183,-0.305431147,-0.283527234,-0.189331848,0.397157947,-0.127935897,-0.090129983,0.002833316,-0.042528212,-0.096295003,0.187023001,-0.065300217,-0.263511388,0.188476966,0.028802789,-0.038653814,-0.184163783,-0.087470316,0.14727964,-0.083956744,-0.038041177,0.06944745,0.054739106,0.173335071,-0.294004502,-0.043102283,0.019047484,-0.025939931,-0.084849194,0.10752943,-0.058155135,0.017803896,-0.032839982,-1.57153E-17};
    paramInput[1].input2=input12;//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.344462508,3.414012926,2.575859196,4.132841119,10.29552155,13.44719318,6.667944586,21.92005767,24.57302404,28.80436479,11.46694514,9.063138435,10.84180171,34.47030984,37.30943051,9.344495024,14.78442891,18.51835707,1.188209863,19.84672606,10.4305217,11.05548616,-2.122447184,33.66726858,17.01667633,26.50935835,36.02248572,-2.981228589,7.151878178,16.9056907,-5.374710073,-0.930817978,7.994593896,1.484913955,-1.022747003,15.89997769,4.222215223,-1.849445231,-0.601762913,-2.546570618,4.502455121,11.51034386,2.665195904,1.86E+00,6.614848105,-12.00246522,-5.423235586,4.394813731,15.94087705,-0.063851034,39.00964591,16.29760062,-0.030470804,11.6960511,5.614454608,-8.522492558,-1.802220743,21.48228736,0.362709385,12.78231095,4.838765392,11.14249637,-10.17253577,-0.578846728,1.951093617,-6.056274983,-6.688115463,8.784600667,-1.708225348,5.538907552,-20.51340195,-2.147831629,-14.24193734,5.650581441,-12.24684148,4.720679728,-3.773026062,22.67975347,8.720340038,2.385741444,7.699779697,22.44563951,-3.721425443,-1.043021346,13.14762023,5.066523706,23.55052636,26.20167414,40.94116977,-14.33372975,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    paramInput[1].input3=input13;

}



