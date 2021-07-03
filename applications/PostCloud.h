/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-24     alanl       the first version
 */
#ifndef APPLICATIONS_POSTCLOUD_H_
#define APPLICATIONS_POSTCLOUD_H_

int postCloud(int checkNet=0);
int webclient_post_test2(int argc, char **argv);
int postCloudApp();
extern struct rt_event ev_postCloud;
#endif /* APPLICATIONS_POSTCLOUD_H_ */
