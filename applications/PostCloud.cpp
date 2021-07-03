
#include <string.h>
#include <rtthread.h>
#include <webclient.h>
#include <cjson.h>
#include "CDeviceStatus.h"
#include "PostCloud.h"
#include <stdlib.h>
#define POST_RESP_BUFSZ                512
#define POST_HEADER_BUFSZ              2048
#define POST_LOCAL_URI                "http://47.100.172.1:8033/machine/api/detect"
#define POST_LOCAL_URI2               "http://221.214.6.66:7415/"
#define GET_HEADER_BUFSZ               1024
#define GET_RESP_BUFSZ                 1024

#define GET_LOCAL_URI                  "http://www.rt-thread.com/service/rt-thread.txt"
extern CDeviceStatus m_deviceStatus;
struct rt_event ev_postCloud;
unsigned char buffer[POST_RESP_BUFSZ];

static int webclient_post_comm2(const char *uri, const char *post_data, size_t data_len)
{
    struct webclient_session* session = RT_NULL;
   // unsigned char *buffer = RT_NULL;
    int index, ret = 0;
    int bytes_read, resp_status;

    //buffer = (unsigned char *) web_malloc(POST_RESP_BUFSZ);
    if (buffer == RT_NULL)
    {
        rt_kprintf("no memory for receive response buffer.\n");
        ret = -RT_ENOMEM;
        goto __exit;
    }


    session = webclient_session_create(POST_HEADER_BUFSZ);
    if (session == RT_NULL)
    {
        ret = -RT_ENOMEM;
        goto __exit;
    }

    webclient_header_fields_add(session, "Content-Length: %d\r\n",data_len);// strlen((const char*) post_data));
    //webclient_header_fields_add(session, "Content-Type: application/octet-stream\r\n");
    webclient_header_fields_add(session, "Content-Type: application/json\r\n");
    resp_status = webclient_post(session, uri, post_data);
    if ((resp_status)> 300)
    {
        rt_kprintf("webclient POST request failed, response(%d) error.\n", resp_status);
        ret = -RT_ERROR;
        goto __exit;
    }

   // rt_kprintf("webclient post response data: \n");
    do
    {
        bytes_read = webclient_read(session, buffer, POST_RESP_BUFSZ);
        if (bytes_read <= 0)
        {
            break;
        }

        for (index = 0; index < bytes_read; index++)
        {
            rt_kprintf("%c", buffer[index]);
        }
    } while (1);

    rt_kprintf("\n");

    __exit: if (session)
    {
        webclient_close(session);
    }

    return ret;
}



int postCloud(int checkNet)
{
//pack 1
    cJSON *cdatastream = cJSON_CreateObject();

    cJSON *cid=cJSON_CreateString(m_deviceStatus.deviceSN.c_str());
    cJSON_AddItemToObject(cdatastream, "MachineSN", cid);

    cJSON *cMode = cJSON_CreateString(m_deviceStatus.str_ModelSN.c_str());
    cJSON_AddItemToObject(cdatastream, "ModelSN", cMode);

    cJSON *cRst = cJSON_CreateNumber((int) (m_deviceStatus.sugerRst * 10));
    cJSON_AddItemToObject(cdatastream, "MachineBRIX", cRst);

    cJSON *cTemp = cJSON_CreateNumber(m_deviceStatus.tempOut);
    cJSON_AddItemToObject(cdatastream, "Tempature", cTemp);

    cJSON *cTestMode = cJSON_CreateNumber(m_deviceStatus.FLAG);
    cJSON_AddItemToObject(cdatastream, "FLAG", cTestMode);

    m_deviceStatus.packID=time(RT_NULL);
    cJSON *cPackID=cJSON_CreateNumber( m_deviceStatus.packID);
    cJSON_AddItemToObject(cdatastream, "PackID", cPackID);

    cJSON *TotalPack=cJSON_CreateNumber(2);
    cJSON_AddItemToObject(cdatastream, "TotalPack", TotalPack);

    cJSON *thisPackCnt=cJSON_CreateNumber(1);
    cJSON_AddItemToObject(cdatastream, "PackCnt", thisPackCnt);

    cJSON *pwm=cJSON_CreateNumber(m_deviceStatus.PWM);
    cJSON_AddItemToObject(cdatastream, "PWM", pwm);

    cJSON *expo=cJSON_CreateNumber(m_deviceStatus.expo);
    cJSON_AddItemToObject(cdatastream, "Exposure", expo);


    checkNet=1;
    if (m_deviceStatus.DarkRst != nullptr && checkNet != 0)
    {
        cJSON *val = cJSON_CreateArray();
        for (int i = 2; i < 514; i++)
        {
            cJSON *num1 = cJSON_CreateNumber(m_deviceStatus.DarkRst[i]);
            cJSON_AddItemToArray(val, num1);
        }
        cJSON_AddItemToObject(cdatastream, "DarkSpectrum", val);

    }
    else
    {
        rt_kprintf("\n \n no Light rst data \n");
    }


    char *uri = RT_NULL;

    uri = web_strdup(POST_LOCAL_URI);
    if (uri == RT_NULL)
    {
        rt_kprintf("no memory for create post request uri buffer.\n");
        return -RT_ENOMEM;
    }
    char * output=cJSON_PrintUnformatted(cdatastream);
    int rst=0;
    if(output)
    {
        rt_kprintf(output);
         rst= webclient_post_comm2(uri, cJSON_PrintUnformatted(cdatastream), rt_strlen(output));
        free(output);
    }
    if (uri)
    {
      web_free(uri);
    }

    cJSON_Delete(cdatastream);


    return rst;
}
int postCloudPack2()
{

    //pack 2
        cJSON *cdatastream2 = cJSON_CreateObject();

        cJSON *cPackID2=cJSON_CreateNumber(m_deviceStatus.packID);
        cJSON_AddItemToObject(cdatastream2, "PackID", cPackID2);

        cJSON *TotalPack2=cJSON_CreateNumber(2);
        cJSON_AddItemToObject(cdatastream2, "TotalPack", TotalPack2);

        cJSON *thisPackCnt2=cJSON_CreateNumber(2);
        cJSON_AddItemToObject(cdatastream2, "PackCnt", thisPackCnt2);

        cJSON *cid2=cJSON_CreateString(m_deviceStatus.deviceSN.c_str());
        cJSON_AddItemToObject(cdatastream2, "MachineSN", cid2);

        cJSON *val2 = cJSON_CreateArray();
        for (int i = 2; i < 514; i++)
        {
           cJSON *num2 = cJSON_CreateNumber(m_deviceStatus.LightRst[i]);
           cJSON_AddItemToArray(val2, num2);
        }
        cJSON_AddItemToObject(cdatastream2, "LightSpectrum", val2);

       char *uri = web_strdup(POST_LOCAL_URI);
       char * output=cJSON_PrintUnformatted(cdatastream2);
       int rst =0;
       if(output)
       {
           //rt_kprintf(output);
           rst= webclient_post_comm2(uri, output, rt_strlen(output));
           free(output);
       }
       if (uri)
        {
            web_free(uri);
        }
        cJSON_Delete(cdatastream2);
        return rst;
}
static void postCloud_thread_entry(void *parameter)
{
    rt_uint32_t e;
    rt_kprintf("post cloud app start\n \r");
    rt_thread_mdelay(10000);

    while (1)
    {
        if (rt_event_recv(&ev_postCloud, 1,
        RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
        RT_WAITING_NO, &e) == RT_EOK)
        {
            rt_kprintf("key pressed 0x%x\n", e);
           postCloud();
            postCloudPack2();
        }
        rt_thread_mdelay(10000);
        /*
        else {
            rt_thread_mdelay(3000);
            int netstatus = postCloud(1); //1 for check net
                   if (netstatus != 0)
                   {
                       m_deviceStatus.netWorkStatus = -1;
                       rt_kprintf("network OFF \n");
                   }
                   else
                   {
                       rt_kprintf("network OK \n");
                   }
        }
        */
    }
}
static void checkNet_thread_entry(void *parameter)
{
    rt_uint32_t e;

    rt_kprintf("checkNet app start\n");
    while (1)
    {
        rt_thread_mdelay(3000);
    }
}
int postCloudApp()
{
    int ret = 0;
    ret = rt_event_init(&ev_postCloud, "event", RT_IPC_FLAG_FIFO);
    if (ret != RT_EOK)
    {
        rt_kprintf("init event failed.\n");
        return -1;
    }

    rt_thread_t thread = rt_thread_create("postCloud", postCloud_thread_entry, RT_NULL, 2048, 5, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);

    }
    else
    {
        ret = RT_ERROR;
    }
//
//    rt_thread_t thread2 = rt_thread_create("check network", checkNet_thread_entry, RT_NULL, 2048, 5, 10);
//    if (thread2 != RT_NULL)
//    {
//        rt_thread_startup(thread2);
//
//    }
//    else
//    {
//        ret = RT_ERROR;
//    }

    return ret;
}

#ifdef FINSH_USING_MSH
#include <finsh.h>
MSH_CMD_EXPORT_ALIAS(postCloud, postCloud_test, post cloud request test.);
#endif

