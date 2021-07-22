
#include <rtthread.h>
#include <webclient.h>
#include <cjson.h>
#include "CDeviceStatus.h"
#include "PostCloud.h"
#include <stdlib.h>
#include <iostream>   // std::cout
#include <string.h>     // std::string, std::stoi
#include "Screen.h"
#define POST_RESP_BUFSZ                2048
#define POST_HEADER_BUFSZ              2048
#define POST_LOCAL_URI                "http://47.100.172.1:8033/machine/api/detect"
#define POST_LOCAL_URI2               "http://221.214.6.66:7415/"
#define GET_HEADER_BUFSZ               POST_RESP_BUFSZ
#define GET_RESP_BUFSZ                 POST_RESP_BUFSZ

std::string GET_MACHINE_URI= "http://47.100.172.1:8033/machine/api/machine/";//XCNIR000000
std::string GET_MODEL_URI = "http://47.100.172.1:8033/machine/api/model/"; //"http://47.100.172.1:8033/machine/api/model/56?col=Input0"
extern CDeviceStatus m_deviceStatus;
struct rt_event ev_postCloud;
unsigned char buffer[GET_HEADER_BUFSZ];

static int webclient_post_comm2(const char *uri, const char *post_data, size_t data_len)
{
    struct webclient_session* session = RT_NULL;
    memset(buffer, POST_RESP_BUFSZ, 0);
    int index, ret = 0;
    int bytes_read, resp_status;

    session = webclient_session_create(POST_HEADER_BUFSZ);
    if (session == RT_NULL)
    {
        ret = -RT_ENOMEM;
        goto __exit;
    }

    webclient_header_fields_add(session, "Content-Length: %d\r\n", data_len); // strlen((const char*) post_data));
    //webclient_header_fields_add(session, "Content-Type: application/octet-stream\r\n");
    webclient_header_fields_add(session, "Content-Type: application/json\r\n");
    resp_status = webclient_post(session, uri, post_data);
    if ((resp_status) > 300)
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

    cJSON *cid = cJSON_CreateString(m_deviceStatus.MachineSN.c_str());
    cJSON_AddItemToObject(cdatastream, "MachineSN", cid);

    cJSON *cMode = cJSON_CreateString(m_deviceStatus.str_ModelSN.c_str());
    cJSON_AddItemToObject(cdatastream, "ModelSN", cMode);

    cJSON *cRst = cJSON_CreateNumber((int) (m_deviceStatus.sugerRst * 10));
    cJSON_AddItemToObject(cdatastream, "MachineBRIX", cRst);

    cJSON *cTemp = cJSON_CreateNumber(m_deviceStatus.tempOut);
    cJSON_AddItemToObject(cdatastream, "Tempature", cTemp);

    cJSON *cTestMode = cJSON_CreateNumber(m_deviceStatus.FLAG);
    cJSON_AddItemToObject(cdatastream, "FLAG", cTestMode);

    m_deviceStatus.packID = time(RT_NULL);
    cJSON *cPackID = cJSON_CreateNumber(m_deviceStatus.packID);
    cJSON_AddItemToObject(cdatastream, "PackID", cPackID);

    cJSON *TotalPack = cJSON_CreateNumber(2);
    cJSON_AddItemToObject(cdatastream, "TotalPack", TotalPack);

    cJSON *thisPackCnt = cJSON_CreateNumber(1);
    cJSON_AddItemToObject(cdatastream, "PackCnt", thisPackCnt);

    cJSON *pwm = cJSON_CreateNumber(m_deviceStatus.PWM);
    cJSON_AddItemToObject(cdatastream, "PWM", pwm);

    cJSON *expo = cJSON_CreateNumber(m_deviceStatus.Exposure);
    cJSON_AddItemToObject(cdatastream, "Exposure", expo);

    cJSON *r1 = cJSON_CreateNumber(m_deviceStatus.DetectCalibLightRatio1);
    cJSON_AddItemToObject(cdatastream, "DetectCalibLightRatio1", r1);

    checkNet = 1;
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
    char * output = cJSON_PrintUnformatted(cdatastream);
    int rst = 0;
    if (output)
    {
        rt_kprintf(output);
        rst = webclient_post_comm2(uri, cJSON_PrintUnformatted(cdatastream), rt_strlen(output));
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

    cJSON *cPackID2 = cJSON_CreateNumber(m_deviceStatus.packID);
    cJSON_AddItemToObject(cdatastream2, "PackID", cPackID2);

    cJSON *TotalPack2 = cJSON_CreateNumber(2);
    cJSON_AddItemToObject(cdatastream2, "TotalPack", TotalPack2);

    cJSON *thisPackCnt2 = cJSON_CreateNumber(2);
    cJSON_AddItemToObject(cdatastream2, "PackCnt", thisPackCnt2);

    cJSON *cid2 = cJSON_CreateString(m_deviceStatus.MachineSN.c_str());
    cJSON_AddItemToObject(cdatastream2, "MachineSN", cid2);

    cJSON *val2 = cJSON_CreateArray();
    for (int i = 2; i < 514; i++)
    {
        cJSON *num2 = cJSON_CreateNumber(m_deviceStatus.LightRst[i]);
        cJSON_AddItemToArray(val2, num2);
    }
    cJSON_AddItemToObject(cdatastream2, "LightSpectrum", val2);

    char *uri = web_strdup(POST_LOCAL_URI);
    char * output = cJSON_PrintUnformatted(cdatastream2);
    int rst = 0;
    if (output)
    {
        //rt_kprintf(output);
        rst = webclient_post_comm2(uri, output, rt_strlen(output));
        free(output);
    }
    if (uri)
    {
        web_free(uri);
    }
    cJSON_Delete(cdatastream2);
    return rst;
}
int webclient_get_comm(const char *uri)
{
    struct webclient_session* session = RT_NULL;

    int index, ret = 0;
    int bytes_read, resp_status;
    int content_length = -1;
    /* create webclient session and set header response size */
    memset(buffer, POST_RESP_BUFSZ, 0);
    session = webclient_session_create(GET_HEADER_BUFSZ);
    if (session == RT_NULL)
    {
        ret = -RT_ENOMEM;
        goto __exit;
    }

    /* send GET request by default header */
    if ((resp_status = webclient_get(session, uri)) != 200)
    {
        rt_kprintf("webclient GET request failed, response(%d) error.\n", resp_status);
        ret = -RT_ERROR;
        goto __exit;
    }

    rt_kprintf("webclient get response data: \n");

    content_length = webclient_content_length_get(session);
    if (content_length < 0)
    {
        rt_kprintf("webclient GET request type is chunked.\n");
        do
        {
            bytes_read = webclient_read(session, buffer, GET_RESP_BUFSZ);
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
    }
    else
    {
        int content_pos = 0;

        do
        {
            bytes_read = webclient_read(session, buffer,
                    content_length - content_pos > GET_RESP_BUFSZ ?
                    GET_RESP_BUFSZ :
                                                                    content_length - content_pos);
            if (bytes_read <= 0)
            {
                break;
            }

            for (index = 0; index < bytes_read; index++)
            {
                rt_kprintf("%c", buffer[index]);
            }

            content_pos += bytes_read;
        } while (content_pos < content_length);

        rt_kprintf("\n");
    }
    __exit: if (session)
    {
        webclient_close(session);
    }

    return ret;
}
int getMachine()
{

    if (webclient_get_comm((GET_MACHINE_URI+m_deviceStatus.MachineSN).c_str()) != 0)
    {
        rt_kprintf("get machine url error\n");
        return -1;
    }

//parse json
    cJSON *cj = cJSON_Parse((const char*) buffer);
    if (cj == NULL)
    {
        rt_kprintf("get machine cjson parse error\n");
    }
    else
    {
        char * output = cJSON_Print(cj);
        if (output != NULL)
        {
            rt_kprintf(output);
            free(output);
        }
    }
    int id = cJSON_GetObjectItem(cj, "id")->valueint;
    cJSON* modelsArr = cJSON_GetObjectItem(cj, "models");
    cJSON* arrayItem = modelsArr->child;
    int modelsSize = cJSON_GetArraySize(modelsArr);
    m_deviceStatus.modelIDs.clear();
    for (int i = 0; i < modelsSize; i++)
    {
        m_deviceStatus.modelIDs.push_back(arrayItem->valueint);
        arrayItem = arrayItem->next;

    }
    m_deviceStatus.PWM=cJSON_GetObjectItem(cj, "PWM")->valueint;
    m_deviceStatus.Exposure=cJSON_GetObjectItem(cj, "Exposure")->valueint;
    m_deviceStatus.DetectCalibLightRatio1=cJSON_GetObjectItem(cj, "DetectCalibLightRatio1")->valuedouble;
    m_deviceStatus.saveStatus();
    cJSON_Delete(cj);
//send to screen get 2 models
    return 1;

}
int getInputN(float *f,std::string modelNo,std::string sInput)
{
   std::string url = GET_MODEL_URI + modelNo + "?cols="+sInput;
           if (webclient_get_comm(url.c_str()) != 0)
           {
               rt_kprintf((sInput + " get url error\n").c_str());
               return -1;
           }

           cJSON* cj = cJSON_Parse((const char*) buffer);
           if (cj == NULL)
           {
               rt_kprintf((sInput+" cJSON_Parse cjson parse error\n").c_str());
           }
           else
           {
               char * output = cJSON_Print(cj);
               if (output != NULL)
               {
                   rt_kprintf(output);
                   free(output);
               }
           }

           cJSON* input0array = cJSON_GetObjectItem(cj, sInput.c_str());
           cJSON* arrayItem = input0array->child;
           int arraysize = cJSON_GetArraySize(input0array);

           for (int i = 0; i < arraysize; i++)
           {
               f[i] = (arrayItem->valuedouble);
               arrayItem = arrayItem->next;
           }
           cJSON_Delete(cj);
}
int getModels()
{
    for (int id = 0; id < m_deviceStatus.modelIDs.size(); id++)
    {
        char temp[3];
        itoa(id, temp, 10);
        std::string url =
                GET_MODEL_URI + temp
                        + "?cols=ModelSN,ModelFUNC,Exposure,DetectRepert,DetectFrequency,DetectCalibLightRatio1,PreMethod,TempCalibK,TempCalibB,Label,CalibX,Input3";
        rt_kprintf(url.c_str());

        if (webclient_get_comm(url.c_str()) != 0)
        {
            rt_kprintf("get machine url error\n");
            return -1;
        }

        //parse json
        cJSON *cj = cJSON_Parse((const char*) buffer);
        if (cj == NULL)
        {
            rt_kprintf("cJSON_Parse machine error\n");
        }
        else
        {
            char * output = cJSON_Print(cj);
            if (output != NULL)
            {
                rt_kprintf(output);
                free(output);
            }
        }
        CFruitModel model;
        model.ModelSN = cJSON_GetObjectItem(cj, "ModelSN")->valuestring;
        model.ModelFUNC = cJSON_GetObjectItem(cj, "ModelFUNC")->valuestring;
        model.Exposure = cJSON_GetObjectItem(cj, "Exposure")->valueint;
        model.DetectRepert = cJSON_GetObjectItem(cj, "DetectRepert")->valueint;
        model.DetectFrequency = cJSON_GetObjectItem(cj, "DetectFrequency")->valueint;
        model.PreMethod = cJSON_GetObjectItem(cj, "PreMethod")->valueint;
        model.TempCalibB = cJSON_GetObjectItem(cj, "TempCalibB")->valuedouble;
        model.TempCalibK = cJSON_GetObjectItem(cj, "TempCalibK")->valuedouble;
        model.input3 = cJSON_GetObjectItem(cj, "Input3")->valuedouble;
        model.Label = cJSON_GetObjectItem(cj, "Label")->valuestring;
/*
        cJSON* calibx = cJSON_GetObjectItem(cj, "CalibX");
        cJSON* arrayItem = calibx->child;
        int Size = cJSON_GetArraySize(calibx);
        for (int i = 0; i < Size; i++)
        {
            model.CalibX[i] = (arrayItem->valueint);
            arrayItem = arrayItem->next;

        }
*/
        cJSON_Delete(cj);
/////////////////////INPUT array
        getInputN(model.input0,temp,"Input0");
        getInputN(model.input1,temp,"Input1");
        getInputN(model.input2,temp,"Input2");

    }
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
        else if(m_deviceStatus.netWorkStatus<1)
        {
             rt_thread_mdelay(10000);
             m_deviceStatus.netWorkStatus =  getMachine();
             if (m_deviceStatus.netWorkStatus <1)
             {
                 m_deviceStatus.netWorkStatus = -1;
                 rt_kprintf("network OFF \n");

             }
             else
             {
                 rt_kprintf("network OK \n");
                 screenShowRst();
             }
         }
        else {
            rt_thread_mdelay(10000);
        }





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
MSH_CMD_EXPORT_ALIAS(getMachine, getMachineTest, get machine test.);
#endif

