#include "bc20.h"

const char BC20_CMD_FCS[]={BC20_Cmd_Fcs};
const char SERVER_IP[]={BC20_Server_IP};
const char LOCAL_PORT[]={BC20_Local_Port};
const char TCP_BUFFER_MODE[]={BC20_TCP_Buffer_Mode};



BC20TypeDef_t bc20;


/****************************************************************************

PSM模式
at least 10ms
****************************************************************************/
void bc20_PsmExit(void)
{
	BC20_PSM_PIN(1);
	BC20_DELAY(10);
	BC20_PSM_PIN(0);
}

/**********************************************************
*
*  NB 使能
*
**********************************************************/
void bc20_Enable(void)
{
	BC20_EN_PIN(1);
}
/**********************************************************
*
*  NB 失能
*
**********************************************************/
void bc20_Disable(void)
{
	BC20_EN_PIN(0);
}/**********************************************************
*
*  NB 复位
*
**********************************************************/
void bc20_Reset(void)
{
	BC20_RST_PIN(0);
	BC20_DELAY(50);
	BC20_RST_PIN(1);
	BC20_DELAY(100);
	BC20_RST_PIN(0);
	BC20_DELAY(50);
}/**********************************************************
*
*  NB 开机
*
**********************************************************/
void bc20_PowerOn(void)
{
	bc20_Enable();
	BC20_PWR_PIN(0);
	BC20_DELAY(100);
	BC20_PWR_PIN(1);
	BC20_DELAY(2000);
	BC20_PWR_PIN(0);
	BC20_DELAY(100);
}
/**********************************************************
*
*  NB 关机
*
**********************************************************/
void bc20_PowerOff(void)
{
	bc20_Disable();
}


/**********************************************************
*
*  检查nb是否在线
*  因为发生在初始化阶段，因为必须使用硬件延时
**********************************************************/
char bc20_CheckNB(void)
{
	uint32_t counter = 0;
	BC20_UART_SEND((uint8_t*)"AT\r\n",4);

  while(counter < 100)
	{
		if(strstr((const char*)BC20_UART_BUFFER,"OK")!=NULL)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}
/**********************************************************
*
*  设置指令回声模式
*   
**********************************************************/
char bc20_SetEcho(char mode)
{
	
	uint32_t counter = 0;
	
	if(mode == 1)
	{
		BC20_UART_SEND((uint8_t*)"ATE1\r",5);
	}
	else if(mode == 0)
	{
		BC20_UART_SEND((uint8_t*)"ATE0\r",5);
	}	
	
	while(counter < 100)
	{
		if(strstr((const char*)BC20_UART_BUFFER,"OK")!=NULL)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}
/**********************************************************
*
*
*查询OK 回复
*
**********************************************************/
char bc20_CheckRxOk(void)
{

	if(strstr((const char*)BC20_UART_BUFFER,"\r\nOK\r\n")!=NULL)
	{
		return 1;
	}
	return 0;
}
/**********************************************************
*
*
*从缓存区获取消息
*
**********************************************************/
char bc20_CheckRxBuffer(char* dest, const char* str1, const char* str2)
{
	uint8_t counter = 0;
	uint32_t i;
	char* tmp;
	char* p1;
	char* p2;
	tmp = (char*)BC20_UART_BUFFER;

	for(i = 0; i < BC20_BUFFER_SIZE;i++)
	{
		if(BC20_UART_BUFFER[i]==0x00)
		{
			tmp++;
		}
		else
		{
			break;
		}	
	}
	
	p1=strstr(tmp,str1);
	if(p1==NULL)
	{
		return 0 ;
	}
		
	p1+=strlen(str1);
	
	p2=strstr(p1,str2); 
	if(p2==NULL||(p2<p1))
	{
		return 0;
	}
	
	memcpy(dest,p1,p2-p1);
	return 1;
}
/**********************************************************
*
*  配置睡眠模式
*   
**********************************************************/	
char bc20_SetSleepMode(uint8_t state)
{
	uint32_t counter = 0;
	char temp[32]={0};
	char data[32]={"AT+QSCLK="};
	if(state >= 3){return 0;}
	sprintf(temp,"%d",state);
	strcat(data,temp);
	strcat(data,"\r");
	BC20_UART_SEND((uint8_t*)data,strlen(data));
	
	while(counter < 100)
	{
		if(bc20_CheckRxOk()==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}

/**********************************************************
*
*  查询IMEI
*   
**********************************************************/	
char bc20_GetIMEI(char*buffer)
{
	uint32_t counter = 0;
	char data[32]={"AT+CGSN=1\r"};
	BC20_UART_SEND((uint8_t*)data,strlen(data));
	
	while(counter < 100)
	{
		if(bc20_CheckRxBuffer(buffer,"CGSN: ",BC20_CMD_FCS)==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}
/**********************************************************
*
*  查询IMSI
*
**********************************************************/

char bc20_GetIMSI(char*buffer)
{
	uint32_t counter = 0;
 	char data[32]={"AT+CIMI\r"};
	BC20_UART_SEND((uint8_t*)data,strlen(data));
	
	while(counter < 100)
	{
		if(bc20_CheckRxBuffer(buffer,"CIMI\r\r\n",BC20_CMD_FCS)==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;

}
/**********************************************************
*
*  查BAND
*AT+NBAND?
**********************************************************/
char bc20_GetBand(char*buffer)
{
	uint32_t counter = 0;
  char data[32]={"AT+QBAND?\r"};
	BC20_UART_SEND((uint8_t*)data,strlen(data));
	
	while(counter < 100)
	{
		if(bc20_CheckRxBuffer(buffer,"+QBAND: ",BC20_CMD_FCS)==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;

}

/**********************************************************
*
*  
*设置BAND
**********************************************************/
char bc20_SetBand(void)
{
	uint32_t counter = 0;
 	char data[32]={"AT+QBAND=1,8\r"};
	BC20_UART_SEND((uint8_t*)data,strlen(data));
	
	while(counter < 100)
	{
		if(bc20_CheckRxOk()==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}

/**********************************************************
*
*  查信号
**********************************************************/

char bc20_GetCSQ(char* buffer)
{
	uint32_t counter = 0;
 	char data[32]={"AT+CSQ\r"};
	BC20_UART_SEND((uint8_t*)data,strlen(data));
	
	while(counter < 100)
	{
		if(bc20_CheckRxBuffer(buffer,"CSQ: ",BC20_CMD_FCS)==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}

/**********************************************************
*
*  查RSSI
**********************************************************/
void bc20_GetRSSI(int32_t* rssi)
{
	*rssi = ((int32_t)atoi(bc20.CSQ))*2-113.0;
}
/**********************************************************
*
*  注册网络
*
**********************************************************/
char bc20_SetReg(void)
{
	uint32_t counter = 0;
 char data[32]={"AT+CEREG=1\r"};

	BC20_UART_SEND((uint8_t*)data,strlen(data));
	while(counter < 100)
	{
		if(bc20_CheckRxOk()==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}
/**********************************************************
*
*  查询注册状态
*
**********************************************************/
char bc20_GetReg(char* buffer)
{
	uint32_t counter = 0;
	char data[32]={"AT+CEREG?\r"};
	BC20_UART_SEND((uint8_t*)data,strlen(data));
	while(counter < 100)
	{
		if(bc20_CheckRxBuffer(buffer,"+CEREG: ",",1\r\n\r\nOK\r\n")==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;

}
/**********************************************************
*
*  打开TCP链接
*  direct push modes
**********************************************************/
char bc20_OpenTcp(char connectID,const char*ip_port,const char* local_port,const char* tcp_buffer_mode)
{	
	uint32_t counter = 0;
	//
  char data[64]={"AT+QIOPEN=1"};
	char temp[32]={0};
	strcat(data,",");
	sprintf(temp,"%d",connectID);
	strcat(data,temp);
	strcat(data,",");
	strcat(data,"\"TCP\"");
	strcat(data,",");
	//IP and remote port 10081
	strcat(data,ip_port);
	strcat(data,",");
	//local port and ipv4 mode(1)
	strcat(data,local_port);
	strcat(data,",");
	//direct push mode,buffer access mode must set '1' to '0'
	strcat(data,tcp_buffer_mode);
	strcat(data,"\r");
  
	BC20_UART_SEND((uint8_t*)data,strlen(data));
	while(counter < 100)
	{
		if(bc20_CheckRxOk()==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}
/**********************************************************
*
*  关闭TCP链接
*  direct push modes
**********************************************************/
char bc20_CloseTcp(char connectID)
{
	uint32_t counter = 0;
 	char data[64]={"AT+QICLOSE="};
	char temp[32]={0};
	sprintf(temp,"%d",connectID);
	strcat(data,temp);
	strcat(data,"\r");

	while(counter < 100)
	{
		if(bc20_CheckRxOk()==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}


/**********************************************************
*
*  查询TCP链接状态
*
**********************************************************/
char bc20_GetTcpStatus(char connectID,const  char*ip_port,const char*local_port,const char*tcp_buffer_mode,char*buffer)
{
	uint32_t counter = 0;
 	char data[64]={"AT+QISTATE=1"};
	char temp[32]={0};
	char temp1[32]={0};
	strcat(data,",");
	sprintf(temp1,"%d",connectID);
	strcat(data,temp1);
	strcat(data,"\r");

	BC20_UART_SEND((uint8_t*)data,strlen(data));
	
	while(counter < 100)
	{
		if(bc20_CheckRxBuffer(temp,"+QISTATE: ",BC20_CMD_FCS)==1)
		{
				memset(temp,0,sizeof(temp));
				strcat(temp,ip_port);
				strcat(temp,",");
				strcat(temp,local_port);
				strcat(temp,",");
				//direct push mode,buffer access mode must set '1' to '0'
				strcat(temp1,",");
				strcat(temp1,tcp_buffer_mode);
				bc20_CheckRxBuffer(buffer,temp,",");
				BC20_UART_CLEAR_BUFFER();
				return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
	
}
/**********************************************************
*
*  获取最后一条的错误信息
*
**********************************************************/
char bc20_GetError(char* error)
{
	uint32_t counter = 0;
 	char data[64]={"AT+QIGETERROR\r"};
	memset(bc20.ERROR,0,sizeof(bc20.ERROR));
	BC20_UART_SEND((uint8_t*)data,strlen(data));
	
	while(counter < 100)
	{
		if(bc20_CheckRxBuffer(error,"+QIGETERROR: ",BC20_CMD_FCS)==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}
/**********************************************************
*
*  查询网络状态，回复1为网络已经激活
*
**********************************************************/
char bc20_GetGATT(char*buffer)
{
	uint32_t counter = 0;
 	char data[64]={"AT+CGATT?\r\n"};

	BC20_UART_SEND((uint8_t*)data,strlen(data));
	while(counter < 100)
	{
		if(bc20_CheckRxBuffer(buffer,"+CGATT: ",BC20_CMD_FCS)==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;

}
/**********************************************************
*
*  设置网络附着，激活网络
*
**********************************************************/
char bc20_SetGATT(void)
{
	uint32_t counter = 0;
 	char data[64]={"AT+CGATT=1\r\n"};

	BC20_UART_SEND((uint8_t*)data,strlen(data));
	while(counter < 500)
	{
		if(bc20_CheckRxOk()==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}

/**********************************************************
*
* 查询APN列表
*
**********************************************************/
char bc20_GetApnList(char* buffer)
{
	
	uint32_t counter = 0;
	char  temp[64]={"AT+CGDCONT?\r\n"};
	
	BC20_UART_SEND((uint8_t*)temp,strlen(temp));
	
	while(counter < 100)   
	{
		if(bc20_CheckRxOk()==1)
		{
			strcpy(buffer,(const char*)BC20_UART_BUFFER);
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	return 0;
	
}


/**********************************************************
*
* 设置APN，设置完成需要实用rst指令重启生效
*
**********************************************************/
char bc20_SetAPN(char* pdp_type, char* apn, char* username, char* passwd)
{
	uint32_t counter = 0;
	char  temp[64]={"AT+QCGDEFCONT="};
	char  temp1[64]={0};
	//pdp type
	strcat(temp,"\"");
	strcat(temp,pdp_type);
	strcat(temp,"\"");
	
	strcat(temp,",");
	
	//apn
	strcat(temp,"\"");
	strcat(temp,apn);
	strcat(temp,"\"");
	
	
	//username & passwd
	if(username != NULL )
	{
		strcat(temp,",");
		strcat(temp,"\"");
		strcat(temp,username);
		strcat(temp,"\"");
		if(passwd != NULL)
		{
			strcat(temp,",");
			strcat(temp,"\"");
			strcat(temp,passwd);
			strcat(temp,"\"");
		}
	}
	strcat(temp,"\r\n");
	
	BC20_UART_SEND((uint8_t*)temp,strlen(temp));
	
	while(counter < 500)   
	{
		if(bc20_CheckRxOk()==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}

/**********************************************************
*
* 重启指令
*
**********************************************************/
char bc20_SetRST(void)
{
	char  temp[32]={"AT+QRST=1\r\n"};
	
	BC20_UART_SEND((uint8_t*)temp,strlen(temp));
	
	return 1;
}

/**********************************************************
*
*  配置数据发送模式
 <send_data_format>      
 Integer type. Sending data format.  
 0 Text mode 
 1  Hex mode 
 <recv_data_format>    
 Integer type. Receiving data format.  
 0 Text mode         
 1  Hex mode 
*
**********************************************************/
char bc20_SetDataFormat(char sendformat, char revformat)
{
	uint32_t counter = 0;
	char data[64]={"AT+QICFG=\"dataformat\","};
	char temp[32]={0};
	sprintf(temp,"%d",sendformat);
	strcat(data,temp);
	strcat(data,",");
	sprintf(temp,"%d",revformat);
	strcat(data,temp);
	strcat(data,"\r");

	BC20_UART_SEND((uint8_t*)data,strlen(data));
	while(counter < 100)
	{
		if(bc20_CheckRxOk()==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}
/**********************************************************
*
*  配置数据输出模式
*  指的是串口输出到MCU的数据格式
<view_mode>     
Integer type. 
Received data output format.          
0  Received data output format: 
data header\r\ndata         
1  Received data output format: 
data header,data 
**********************************************************/
char bc20_SetDataOutputFormat(char format)
{
	uint32_t counter = 0;
	char  data[64]={"AT+QICFG=\"viewmode\","};
	char  temp[32]={0};
	sprintf(temp,"%d",format);
	strcat(data,temp);
	strcat(data,"\r");

	BC20_UART_SEND((uint8_t*)data,strlen(data));
	while(counter < 100)
	{
		if(bc20_CheckRxOk()==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}

/**********************************************************
*配置显示数据长度模式
<show_length_mode>   
Integer type. 
Whether to show the optional length in buffer access mode.         
0  Do not show the optional length in buffer access mode         
1  Show the optional length in buffer access mode 
**********************************************************/

char bc20_ShowLengthMode(char mode)
{
	uint32_t counter = 0;
	char  data[64]={"AT+QICFG=\"showlength\","};
	char  temp[32]={0};
	sprintf(temp,"%d",mode);
	strcat(data,temp);
	strcat(data,"\r");

	BC20_UART_SEND((uint8_t*)data,strlen(data));
	while(counter < 100)
	{
		if(bc20_CheckRxOk()==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}

/**********************************************************
*获取配置状态
*buffer里装了回复的配置状态
*
**********************************************************/
char bc20_GetConfig(char*dataformat,char*viewmode,char*showlength)
{
	
	uint32_t counter = 0;
 	char data[64]={"AT+QICFG=?\r"};

	BC20_UART_SEND((uint8_t*)data,strlen(data));
	
	while(counter < 100)
	{
		if(bc20_CheckRxBuffer(dataformat,"+QICFG: \"dataformat\",","\r\n")==1)
		{
			if(bc20_CheckRxBuffer(viewmode,"+QICFG: \"viewmode\",","\r\n")==1)
			{
				if(bc20_CheckRxBuffer(showlength,"+QICFG: \"showlength\",","\r\n")==1)
				{
					BC20_UART_CLEAR_BUFFER();
					return 1;
				}
			}
		}
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}
/**********************************************************
*
*  发送数据
*
**********************************************************/
char bc20_SendData(char connectID, char* data)
{
	uint32_t counter = 0;
	char  temp[BC20_BUFFER_SIZE]={"AT+QISEND="};
	char  temp1[64]={0};
	//data length not inclue two " length
	sprintf(temp1,"%d,%d,",connectID,strlen(data));
	strcat(temp,temp1);
	strcat(temp,"\"");
	strcat(temp,data);
	strcat(temp,"\"");
	strcat(temp,"\r");

	BC20_UART_SEND((uint8_t*)temp,strlen(temp));
	while(counter < 100)
	{
		if(bc20_CheckRxOk()==1)
		{
			BC20_UART_CLEAR_BUFFER();
			return 1;
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}
/**********************************************************
*
*  获取IMEI,最少需要16字节
*
**********************************************************/
char bc20_CopyIMEI(char* dest, uint32_t maxlength)
{
	if(maxlength >= strlen(bc20.IMEI))
	{
		memcpy(dest,bc20.IMEI,strlen(bc20.IMEI));
		return 1;
	}
	return 0;
}


/**********************************************************
*
*  查找buffer中的IP消息
*
**********************************************************/
char bc20_CheckIP(char* ipbuff)
{
	return bc20_CheckRxBuffer(ipbuff,BC20_IP_CHAR,BC20_AT_RSP_END_CHAR);
}

/**********************************************************
*
*  查找buffer中的IP消息
*  默认cid=1，ipv4，cid=2，ipv6
**********************************************************/
char bc20_GetIP(char* cid, char* ip)
{
	 uint32_t counter = 0;
	char  temp[BC20_BUFFER_SIZE]={"AT+CGPADDR="};
	char  temp1[64]={0};
	strcat(temp,cid);
	strcat(temp,"\r\n");
	BC20_UART_SEND((uint8_t*)temp,strlen(temp));
	
	sprintf(temp1,"+CGPADDR: %s,",cid);
	
	
	while(counter < 1000)
	{
		if(bc20_CheckRxOk()==1)
		{
			if(bc20_CheckRxBuffer(ip,temp1,"\r\n\r\nOK")==1)
			{
				BC20_UART_CLEAR_BUFFER();
				return 1;
			}
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}

/**********************************************************
*
*  查找buffer中的rece消息
**********************************************************/
char bc20_CheckURC_Rev(char* connectID, char* length)
{
	char temp[BC20_BUFFER_SIZE]={0};
	char* p;
	if(bc20_CheckRxBuffer(temp,BC20_REV_CHAR,BC20_AT_RSP_END_CHAR)==1)
	{
		p=strchr(temp,',');
		if(p!=NULL)
		{
		  memcpy(connectID,temp,(p-temp));
		  strcpy(length,(p+1));
			BC20_UART_CLEAR_BUFFER();
		  return 1;
		}
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}

/*********************************************************
*
*  NB 初始化
*
*********************************************************/
void bc20_Init(void)
{
	uint8_t status = 0;
	bc20_PowerOn();
	// is at command line ready?
	while(bc20_CheckNB()!=1){BC20_DELAY(100);}
	//
	//查询APN
	for(int i = 0; i < 3; i++)
	{
		if(bc20_GetApnList(bc20.APN_LIST)==1)
		{
			break;
		}
		BC20_DELAY(100);
	}
	//
	//设置APN,APN中含有cmiot1则不设置
	if(strstr(bc20.APN_LIST,"cmiot1")==NULL)
	{
		for(int i = 0; i < 3; i++)
		{
			if(bc20_SetAPN("IP","cmnbiot1",NULL,NULL)==1)
			{
				break;
			}
			BC20_DELAY(1000);
		}
		bc20_SetRST();
	}
	// 等待重启
	while(bc20_CheckNB()!=1){BC20_DELAY(100);}
	//
	//重新查询APN
	for(int i = 0; i < 3; i++)
	{
		if(bc20_GetApnList(bc20.APN_LIST)==1)
		{
			break;
		}
		BC20_DELAY(100);
	}
	//set echo mode 
	while(bc20_SetEcho(1)==0)
	{
		BC20_DELAY(10);
	}
	//
	//配置数据格式
	while(bc20_SetDataFormat(0,0)==0)
	{
		BC20_DELAY(10);
	}
	while(bc20_SetDataOutputFormat(1)==0)
	{
		BC20_DELAY(10);
	}
	//
	//配置不休眠模式
	while(bc20_SetSleepMode(0)==0)
	{
		BC20_DELAY(100);
	}
	//获取网络相关信息
	while(bc20_GetIMEI(bc20.IMEI)==0)
	{
		BC20_DELAY(10);
	}
	while(bc20_GetIMSI(bc20.IMSI)==0)
	{
		BC20_DELAY(10);
	}	
	while(bc20_GetCSQ(bc20.CSQ)==0)
	{
		BC20_DELAY(10);
	}
	//激活网络，根据网络状态，可能需要75s
  bc20_SetGATT();
	for(int i = 0; i < 100; i++)
	{
		bc20_GetGATT(&bc20.GATT);
		if(bc20.GATT == '1')
		{
			break;
		}
		else
		{
			if(i%10==0)
			{
				bc20_SetGATT();
			}
		}
		BC20_DELAY(100);
	}
	//注册到网络，可需要数秒的时间，因此也需要循环查询
  bc20_SetReg();
	for(int i = 0; i < 100; i++)
	{
		bc20_GetReg(&bc20.REGOK);
		if(bc20.REGOK == '1')
		{
			break;
		}
		else
		{
			if(i%10==0)
			{
				bc20_SetReg();
			}
		}
		BC20_DELAY(100);
	}
	//
	//获取频段
	while(bc20_GetBand(&bc20.BAND)==0)
	{
		BC20_DELAY(10);
	}
	//
	//获取IP
	while(strstr(bc20.IP,".")==NULL)
	{
		bc20_GetIP("1",bc20.IP);
		BC20_DELAY(100);
	}
}

/********************************************************
需要一直获取的网络状态

********************************************************/
void bc20_GetNetStatus(void)
{
	bc20_GetCSQ(bc20.CSQ);
	bc20_GetRSSI(&bc20.RSSI);
}
/**********************************************************
*
* 返回接收的内容buffer的指针
*
**********************************************************/
char* bc20_ReceiveBuffer(void)
{
	return bc20.REV_MSG;
}

/**********************************************************
*
*  打开MQTT客户端网络
*
**********************************************************/
char bc20_mqtt_Open(char* tcpid, char* ip, char* port)
{
	uint32_t counter = 0;
	char  temp[BC20_BUFFER_SIZE]={"AT+QMTOPEN="};
	char  temp1[64]={0};
	strcat(temp,tcpid);
	strcat(temp,",");
	strcat(temp,"\"");
	strcat(temp,ip);
	strcat(temp,"\"");
	strcat(temp,",");
	strcat(temp,port);
	strcat(temp,"\r\n");
	BC20_UART_SEND((uint8_t*)temp,strlen(temp));
	
	sprintf(temp1,"+QMTOPEN: %s,0",tcpid);
	
	
	while(counter < 1000)
	{
		if(bc20_CheckRxOk()==1)
		{
			if(strstr((const char*)BC20_UART_BUFFER,temp1)!=NULL)
			{
				BC20_UART_CLEAR_BUFFER();
				return 1;
			}
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}
/**********************************************************
*
*  连接登录MQTT服务器
*
**********************************************************/
char bc20_mqtt_Connect(char* tcpid,char* clientID, char* username, char*passwd)
{
	uint32_t counter = 0;
	char  temp[BC20_BUFFER_SIZE]={"AT+QMTCONN="};
	char  temp1[64]={0};
	strcat(temp,tcpid);
	strcat(temp,",");
	strcat(temp,"\"");
	strcat(temp,clientID);
	strcat(temp,"\"");
	if(username != NULL)
	{
		strcat(temp,",");

		strcat(temp,"\"");
		strcat(temp,username);
		strcat(temp,"\"");
		if(passwd != NULL)
		{
			strcat(temp,",");
			strcat(temp,"\"");
			strcat(temp,passwd);
			strcat(temp,"\"");
		}
	}
	strcat(temp,"\r\n");
	BC20_UART_SEND((uint8_t*)temp,strlen(temp));
	
	sprintf(temp1,"+QMTCONN: %s,0",tcpid);
	
	while(counter < 1000)
	{
		if(bc20_CheckRxOk()==1)
		{
			if(strstr((const char*)BC20_UART_BUFFER,temp1)!=NULL)
			{
				BC20_UART_CLEAR_BUFFER();
				return 1;
			}
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}
/**********************************************************
*
*  断开MQTT连接
*
**********************************************************/
char bc20_mqtt_Disconnect(char* tcpid)
{
	uint32_t counter = 0;
	char  temp[64]={"AT+QMTDISC="};
	char  temp1[64]={0};
	strcat(temp,tcpid);
	strcat(temp,"\r\n");
	BC20_UART_SEND((uint8_t*)temp,strlen(temp));
	
	sprintf(temp1,"+QMTDISC: %s,0",tcpid);
	
	while(counter < 300)
	{
		if(bc20_CheckRxOk()==1)
		{
			if(strstr((const char*)BC20_UART_BUFFER,temp1)!=NULL)
			{
				BC20_UART_CLEAR_BUFFER();
				return 1;
			}
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}

/**********************************************************
*
* MQTT订阅消息
*
**********************************************************/
char bc20_mqtt_Subscribe(char* tcpid, char* msgid, char* topic, char*qos)
{
	uint32_t counter = 0;
	uint32_t counter1 = 0;
	char* index = NULL;
	char  temp[BC20_BUFFER_SIZE]={"AT+QMTSUB="};
	char  temp1[64]={0};
	strcat(temp,tcpid);
	strcat(temp,",");
	strcat(temp,msgid);
	strcat(temp,",");
	strcat(temp,"\"");
	strcat(temp,topic);
	strcat(temp,"\"");
	strcat(temp,",");
	strcat(temp,qos);
	strcat(temp,"\r\n");
	BC20_UART_SEND((uint8_t*)temp,strlen(temp));
	
	sprintf(temp1,"+QMTSUB: %s,%s,0",tcpid,msgid);
	
	while(counter < 400)   //40s determing by network
	{
		if(bc20_CheckRxOk()==1)
		{
			if(strstr((const char*)BC20_UART_BUFFER,temp1)!=NULL)
			{
				while(index ==NULL && counter1 < 300)
				{
					BC20_DELAY(10);
					index = strstr((const char*)BC20_UART_BUFFER,"+QMTRECV: ");
					counter++;
				}
				if(index != NULL)
				{
					memset(bc20.REV_MSG,0,sizeof bc20.REV_MSG);
					memcpy(bc20.REV_MSG,index,(strstr(index,"\r\n\0")-index));
				}
				BC20_UART_CLEAR_BUFFER();
				return 1;
			}
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}


/**********************************************************
*
* MQTT发布消息
*
**********************************************************/
char bc20_mqtt_Publish(char* tcpid, char* msgid, char*qos, char* retain, char* topic, char* msg)
{
	uint32_t counter = 0;
	char  temp[BC20_BUFFER_SIZE]={"AT+QMTPUB="};
	char  temp1[64]={0};
	strcat(temp,tcpid);
	strcat(temp,",");
	strcat(temp,msgid);
	strcat(temp,",");
	strcat(temp,qos);
	strcat(temp,",");
	strcat(temp,retain);
	strcat(temp,",");
	strcat(temp,"\"");
	strcat(temp,topic);
	strcat(temp,"\"");
	strcat(temp,",");
	strcat(temp,"\"");
	strcat(temp,msg);
	strcat(temp,"\"");
	strcat(temp,"\r\n");
	BC20_UART_SEND((uint8_t*)temp,strlen(temp));
	
	sprintf(temp1,"+QMTPUB: %s,%s,0",tcpid,msgid);
	
	while(counter < 400)   //40s determing by network
	{
		if(bc20_CheckRxOk()==1)
		{
			if(strstr((const char*)BC20_UART_BUFFER,temp1)!=NULL)
			{
				BC20_UART_CLEAR_BUFFER();
				return 1;
			}
		}
		BC20_DELAY(10);
		counter++;
	}
	BC20_UART_CLEAR_BUFFER();
	return 0;
}