#ifndef __BC20_H__
#define __BC20_H__

#include "string.h"
#include "math.h"
#include "stdio.h"
#include "stdarg.h"
#include "cJSON.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"



#include "io.h"
#include "uart.h"

/*
*
*控制引脚的定义
*
*/
#define BC20_PWRKEY  PI_GPIO0
#define BC20_EN      PI_GPIO2
#define BC20_RST     PI_GPIO1
#define BC20_PSM     PI_GPIO3


/*
*用于BC20的接口声明
*
*/
#define BC20_BUFFER_SIZE           UART_BUFFER_SIZE   //串口数组大小即可
#define BC20_UART_BUFFER           uart.rxBuffer      //数组指针
#define BC20_UART_SEND(data,len)   uart_send(data,len)
#define BC20_UART_CLEAR_BUFFER()   uart_clear_buffer()
#define BC20_DELAY(ms)             osDelay(ms)

#define BC20_PWR_PIN(state)        HAL_GPIO_WritePin(BC20_PWRKEY,(GPIO_PinState)state)
#define BC20_EN_PIN(state)         HAL_GPIO_WritePin(BC20_EN,(GPIO_PinState)state)
#define BC20_RST_PIN(state)        HAL_GPIO_WritePin(BC20_RST,(GPIO_PinState)state)
#define BC20_PSM_PIN(state)        HAL_GPIO_WritePin(BC20_PSM,(GPIO_PinState)state)
/*
*
*BC20的数据定义
*
*/
#define BC20_SendDataPeriod 60 //unit s
#define BC20_Server_IP       "\"139.199.66.243\",10081"
#define BC20_Local_Port      "10082"
//tcp mode 0-buffer access,1-direct push
#define BC20_TCP_Buffer_Mode "0"
//命令结束符和回应结束符
#define BC20_AT_CMD_END_CHAR "\r"
#define BC20_AT_RSP_END_CHAR "\r\n"
//消息结束符
#define BC20_Cmd_Fcs         "\r\n\r\nOK\r\n"
//接收消息特征符
#define BC20_REV_CHAR        "+QIURC: \"recv\","
//IP特征
#define BC20_IP_CHAR         "+IP: "





typedef enum
{
	TCP_INITIAL=0,
	TCP_OPENING,
	TCP_CONNECTED,
	TCP_CLOSING,
	TCP_STATUS_NUM
}TcpStatus_t;


typedef struct
{
	char status;
	char IMEI[20];
	char IMSI[20];
	char IP[20];
	char CSQ[8];
	char ERROR[64];
	char APN_LIST[512];
	char REV_MSG[1024];
	char GATT;                //1 means attached to network  successfully, while 0 means has not been attached to network
	char BAND;
	char REGOK;              //registration  status
	int32_t  RSSI;
	
	
}BC20TypeDef_t;


char bc20_CheckRxOk(void);
void bc20_Init(void);
void bc20_TaskSendData(int requestNumber,...);
char bc20_CheckURC_Rev(char* connectID, char* length);
void bc20_PackData(cJSON *datapackage,char* logString,char* requestArray[],int count);
char bc20_CheckIP(char* ipbuff);
char bc20_SendData(char connectID, char* data);
char bc20_SetGATT(void);
char bc20_OpenTcp(char connectID,const char*ip_port,const char* local_port,const char* tcp_buffer_mode);

char bc20_SetReg(void);
char bc20_SetBand(void);
char bc20_SetEcho(char mode);
char bc20_CheckNB(void);
void bc20_PowerOff(void);
void bc20_PowerOn(void);
void bc20_Reset(void);
void bc20_Disable(void);
void bc20_Enable(void);
void bc20_PsmExit(void);
char* bc20_ReceiveBuffer(void);

/**********************************************************
*
*  读取接口
*
**********************************************************/
void bc20_GetNetStatus(void);
void bc20_GetRSSI(int32_t* rssi);char bc20_GetGATT(char*buffer);
char bc20_GetError(char* error);
char bc20_GetTcpStatus(char connectID,const  char*ip_port,const char*local_port,const char*tcp_buffer_mode,char*buffer);
char bc20_GetBand(char*buffer);
char bc20_GetIMSI(char*buffer);
char bc20_GetIMEI(char*buffer);
char bc20_GetCSQ(char* buffer);
char bc20_GetReg(char* buffer);
char bc20_GetConfig(char*dataformat,char*viewmode,char*showlength);
char bc20_GetApnList(char* buffer);

char bc20_CopyIMEI(char* dest, uint32_t length);
/**********************************************************
*
*  写入接口
*
**********************************************************/
char bc20_SetAPN(char* pdp_type, char* apn, char* username, char* passwd);
char bc20_SetRST(void);

/**********************************************************
*
*  MQTT接口
*
**********************************************************/
char bc20_mqtt_Open(char* tcpid, char* ip, char* port);
char bc20_mqtt_Connect(char* tcpid,char* clientID, char* username, char*passwd);
char bc20_mqtt_Disconnect(char* tcpid);
char bc20_mqtt_Subscribe(char* tcpid, char* msgid, char* topic, char*qos);
char bc20_mqtt_Publish(char* tcpid, char* msgid, char*qos, char* retain, char* topic, char* msg);




#endif



