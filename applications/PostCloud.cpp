#include <string.h>

#include <rtthread.h>
#include <webclient.h>
#include <cjson.h>
#define POST_RESP_BUFSZ                1024
#define POST_HEADER_BUFSZ              1024
#define POST_LOCAL_URI                 "http://221.214.6.66:7415/"
int postCloud(float data)
{/*
    char *uri = RT_NULL;

    uri = web_strdup(POST_LOCAL_URI);
    if (uri == RT_NULL)
    {
        rt_kprintf("no memory for create post request uri buffer.\n");
        return -RT_ENOMEM;
    }

    int idnum = 123;

    cJSON *cdatastream = cJSON_CreateObject();

    cJSON *cid = cJSON_CreateNumber(idnum);
    cJSON_AddItemToObject(cdatastream, "ID", cid);

    cJSON *val = cJSON_CreateArray();
    for (int i = 0; i < 256; i++)
    {
        cJSON *num1 = cJSON_CreateNumber(i);
        cJSON_AddItemToArray(val, num1);
    }
    cJSON_AddItemToObject(cdatastream, "Light", val);


    for (int i = 0; i < 256; i++)
    {
        cJSON *num1 = cJSON_CreateNumber(i);
        cJSON_AddItemToArray(val, num1);
    }
    cJSON_AddItemToObject(cdatastream, "Dark", val);

    //rt_kprintf(cJSON_Print(cdatastream));

    webclient_post_comm(uri, cJSON_Print(cdatastream));
    */
}
