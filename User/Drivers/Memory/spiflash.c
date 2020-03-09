#include "spiflash.h"


/*********************************************************************
�ڲ���������


*********************************************************************/
static void W25Q64_SPI_CS_ENABLE(void);
static void W25Q64_SPI_CS_DISABLE(void);
void HAL_SPI_Send_Byte(uint8_t byte);
uint8_t HAL_SPI_Receive_Byte(void);
void W25Q64_SPI_Wait_Busy(void);



/*********************************************************************
CS��������


*********************************************************************/
static void W25Q64_SPI_CS_ENABLE(void)
{
	HAL_GPIO_WritePin(W25Q64_CS_GPIO_Port,W25Q64_CS_Pin, GPIO_PIN_RESET);
}

static void W25Q64_SPI_CS_DISABLE(void)
{
	HAL_GPIO_WritePin(W25Q64_CS_GPIO_Port,W25Q64_CS_Pin, GPIO_PIN_SET);
}



/*********************************************************************
���͵����ֽ�


*********************************************************************/
void HAL_SPI_Send_Byte(uint8_t byte)
{
	HAL_SPI_Transmit(&hspi,&byte,1,0xffff);
}


/*********************************************************************
���յ����ֽ�


*********************************************************************/
uint8_t HAL_SPI_Receive_Byte(void)
{
	uint8_t data = 0xFF;
	HAL_SPI_Receive(&hspi,&data,1,0xffff);
	return data;
}

/*********************************************************************
��ȡоƬID
����ֵ����:				   
0XEF13,��ʾоƬ�ͺ�ΪW25Q80  
0XEF14,��ʾоƬ�ͺ�ΪW25Q16    
0XEF15,��ʾоƬ�ͺ�ΪW25Q32  
0XEF16,��ʾоƬ�ͺ�ΪW25Q64 
0XEF17,��ʾоƬ�ͺ�ΪW25Q128 	  
0XEF18,��ʾоƬ�ͺ�ΪW25Q256
*********************************************************************/
uint32_t Temp = 0;
uint32_t W25Q64_SPI_ReadID(void)
{
  /* ѡ����FLASH: CS�͵�ƽ */
  W25Q64_SPI_CS_ENABLE();
  /* ���������ȡоƬ�ͺ�ID */
  HAL_SPI_Send_Byte(W25X_ManufactDeviceID);
	HAL_SPI_Send_Byte(0x00);
	HAL_SPI_Send_Byte(0x00);
	HAL_SPI_Send_Byte(0x00);
  Temp |= HAL_SPI_Receive_Byte()<<8;
  Temp |= HAL_SPI_Receive_Byte();
  W25Q64_SPI_CS_DISABLE();
  return Temp;
}

/*********************************************************************
����
*********************************************************************/
void W25Q64_SPI_Wake_Up(void)   
{  
  	W25Q64_SPI_CS_ENABLE();                                //ʹ������   
    HAL_SPI_Send_Byte(W25X_ReleasePowerDown);  //  send W25X_PowerDown command 0xAB    
		W25Q64_SPI_CS_DISABLE();                               //ȡ��Ƭѡ     	      
    HAL_Delay(1);                                //�ȴ�TRES1 �˴���ʱλ1ms
} 


/*********************************************************************
��ʼ��


*********************************************************************/
uint8_t W25Q64_SPI_Init(void)
{
	
	W25Q64_SPI_Wake_Up();
	if(W25Q64_SPI_ReadID() == SPI_FLASH_TYPE)
	{
		return 1;
	}
	else return 0;
}
/*********************************************************************
��ȡW25QXX��״̬�Ĵ�����W25QXXһ����3��״̬�Ĵ���
״̬�Ĵ���1��
BIT7  6   5   4   3   2   1   0
SPR   RV  TB BP2 BP1 BP0 WEL BUSY
SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
TB,BP2,BP1,BP0:FLASH����д��������
WEL:дʹ������
BUSY:æ���λ(1,æ;0,����)
Ĭ��:0x00
״̬�Ĵ���2��
BIT7  6   5   4   3   2   1   0
SUS   CMP LB3 LB2 LB1 (R) QE  SRP1
״̬�Ĵ���3��
BIT7      6    5    4   3   2   1   0
HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
regno:״̬�Ĵ����ţ���:1~3
����ֵ:״̬�Ĵ���ֵ
*********************************************************************/
uint8_t W25Q64_SPI_Read_SR(uint8_t regno)
{
	uint8_t byte=0,command=0; 
	switch(regno)
	{
		case 1:
			command=W25X_ReadStatusReg1;    //��״̬�Ĵ���1ָ��
			break;
		case 2:
			command=W25X_ReadStatusReg2;    //��״̬�Ĵ���2ָ��
			break;
		case 3:
			command=W25X_ReadStatusReg3;    //��״̬�Ĵ���3ָ��
			break;
		default:
			command=W25X_ReadStatusReg1;    
			break;
	}    
	W25Q64_SPI_CS_ENABLE();                            //ʹ������   
	HAL_SPI_Send_Byte(command);            //���Ͷ�ȡ״̬�Ĵ�������    
	byte=HAL_SPI_Receive_Byte();          //��ȡһ���ֽ�  
	W25Q64_SPI_CS_DISABLE();                            //ȡ��Ƭѡ     
	return byte;   
}

/*********************************************************************
дW25QXX״̬�Ĵ���
*********************************************************************/
void W25Q64_SPI_Write_SR(uint8_t regno,uint8_t sr)   
{   
	uint8_t command=0;
	switch(regno)
	{
		case 1:
			command=W25X_WriteStatusReg1;    //д״̬�Ĵ���1ָ��
			break;
		case 2:
			command=W25X_WriteStatusReg2;    //д״̬�Ĵ���2ָ��
			break;
		case 3:
			command=W25X_WriteStatusReg3;    //д״̬�Ĵ���3ָ��
			break;
		default:
			command=W25X_WriteStatusReg1;    
			break;
	}   
	W25Q64_SPI_CS_ENABLE();                            //ʹ������   
	HAL_SPI_Send_Byte(command);            //����дȡ״̬�Ĵ�������    
	HAL_SPI_Send_Byte(sr);                 //д��һ���ֽ�  
	W25Q64_SPI_CS_DISABLE();                            //ȡ��Ƭѡ     	      
} 
/*********************************************************************
�ȴ�����
*********************************************************************/
void W25Q64_SPI_Wait_Busy(void)   
{   
	while((W25Q64_SPI_Read_SR(1)&0x01)==0x01);   // �ȴ�BUSYλ���
}

/*********************************************************************
W25QXXдʹ��	
��WEL��λ   
*********************************************************************/
void W25Q64_SPI_Write_Enable(void)   
{
	W25Q64_SPI_CS_ENABLE();                            //ʹ������   
  HAL_SPI_Send_Byte(W25X_WriteEnable);  				//����дʹ��  
	W25Q64_SPI_CS_DISABLE();                           //ȡ��Ƭѡ     	      
} 

/*********************************************************************
W25QXXдʹ��	
��WEL��λ   
*********************************************************************/
void W25Q64_SPI_Write_Disable(void)   
{
	W25Q64_SPI_CS_ENABLE();                            //ʹ������   
  HAL_SPI_Send_Byte(W25X_WriteDisable);  				  //����дʹ��  
	W25Q64_SPI_CS_DISABLE();                           //ȡ��Ƭѡ     	      
}

/*********************************************************************
��ȡSPI FLASH  
��ָ����ַ��ʼ��ȡָ�����ȵ�����
pBuffer:���ݴ洢��
ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
*********************************************************************/
uint8_t W25Q64_SPI_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead)   
{ 
 	uint16_t i;   										    
	W25Q64_SPI_CS_ENABLE();                          //ʹ������   
	HAL_SPI_Send_Byte(W25X_ReadData);      //���Ͷ�ȡ����  
	HAL_SPI_Send_Byte((uint8_t)((ReadAddr)>>16));   //����24bit��ַ    
	HAL_SPI_Send_Byte((uint8_t)((ReadAddr)>>8));   
	HAL_SPI_Send_Byte((uint8_t)ReadAddr);   
	for(i=0;i<NumByteToRead;i++)
	{ 
		pBuffer[i]=HAL_SPI_Receive_Byte();    //ѭ������  
	}
	W25Q64_SPI_CS_DISABLE();  		
	return 0;	
}  

/*********************************************************************
SPI��һҳ(0~65535)��д������256���ֽڵ�����
��ָ����ַ��ʼд�����256�ֽڵ�����
pBuffer:���ݴ洢��
WriteAddr:��ʼд��ĵ�ַ(24bit)
NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	 
*********************************************************************/
void W25Q64_SPI_Write_Page(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)
{
 	uint16_t i;  
  W25Q64_SPI_Write_Enable();                  //SET WEL 
	W25Q64_SPI_CS_ENABLE();                            //ʹ������   
	HAL_SPI_Send_Byte(W25X_PageProgram);   //����дҳ����   
	HAL_SPI_Send_Byte((uint8_t)((WriteAddr)>>16)); //����24bit��ַ    
	HAL_SPI_Send_Byte((uint8_t)((WriteAddr)>>8));   
	HAL_SPI_Send_Byte((uint8_t)WriteAddr);   
	for(i=0;i<NumByteToWrite;i++)
		HAL_SPI_Send_Byte(pBuffer[i]);//ѭ��д��  
	W25Q64_SPI_CS_DISABLE();                            //ȡ��Ƭѡ 
	W25Q64_SPI_Wait_Busy();					   //�ȴ�д�����
} 

/*********************************************************************
�޼���дSPI FLASH 
����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
�����Զ���ҳ���� 
��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
pBuffer:���ݴ洢��
WriteAddr:��ʼд��ĵ�ַ(24bit)
NumByteToWrite:Ҫд����ֽ���(���65535)
CHECK OK
*********************************************************************/
void W25Q64_SPI_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 			 		 
	uint16_t pageremain;	   
	pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���		 	    
	if(NumByteToWrite<=pageremain)
		pageremain=NumByteToWrite;//������256���ֽ�
	while(1)
	{	   
		W25Q64_SPI_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)
			break;//д�������
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	
			NumByteToWrite-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
			if(NumByteToWrite>256)
				pageremain=256; //һ�ο���д��256���ֽ�
			else 
				pageremain=NumByteToWrite; 	  //����256���ֽ���
		}
	}    
} 

/*********************************************************************
дSPI FLASH  
��ָ����ַ��ʼд��ָ�����ȵ�����
�ú�������������!
pBuffer:���ݴ洢��
WriteAddr:��ʼд��ĵ�ַ(24bit)						
NumByteToWrite:Ҫд����ֽ���(���65535)   
*********************************************************************/
uint8_t W25QXX_BUFFER[4096];		 
uint8_t W25Q64_SPI_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
 	uint16_t i;    
	uint8_t* W25QXX_BUF;	  
  W25QXX_BUF=W25QXX_BUFFER;	     
 	secpos=WriteAddr/4096;//������ַ  
	secoff=WriteAddr%4096;//�������ڵ�ƫ��
	secremain=4096-secoff;//����ʣ��ռ��С   
 	//printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//������
 	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//������4096���ֽ�
	while(1) 
	{	
		W25Q64_SPI_Read(W25QXX_BUF,secpos*4096,4096);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(W25QXX_BUF[secoff+i]!=0XFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			W25Q64_SPI_Erase_Sector(secpos);//�����������
			for(i=0;i<secremain;i++)	   //����
			{
				W25QXX_BUF[i+secoff]=pBuffer[i];	  
			}
			W25Q64_SPI_Write_NoCheck(W25QXX_BUF,secpos*4096,4096);//д����������  
		}
		else 
			W25Q64_SPI_Write_NoCheck(pBuffer,WriteAddr,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumByteToWrite==secremain)
			break;//д�������
		else//д��δ����
		{
			secpos++;//������ַ��1
			secoff=0;//ƫ��λ��Ϊ0 	 

			pBuffer+=secremain;  //ָ��ƫ��
			WriteAddr+=secremain;//д��ַƫ��	   
			NumByteToWrite-=secremain;				//�ֽ����ݼ�
			if(NumByteToWrite>4096)secremain=4096;	//��һ����������д����
			else secremain=NumByteToWrite;			//��һ����������д����
		}	 
	};	
	return 0;	
}


/*********************************************************************
��������оƬ		  
�ȴ�ʱ�䳬��...
*********************************************************************/
void W25Q64_SPI_Erase_Chip(void)   
{                                   
	W25Q64_SPI_Write_Enable();                  //SET WEL 
	W25Q64_SPI_Wait_Busy();   
	W25Q64_SPI_CS_ENABLE();                            //ʹ������   
	HAL_SPI_Send_Byte(W25X_ChipErase);        //����Ƭ��������  
	W25Q64_SPI_CS_DISABLE();                            //ȡ��Ƭѡ     	      
	W25Q64_SPI_Wait_Busy();   				   //�ȴ�оƬ��������
}

/*********************************************************************
����һ������
Dst_Addr:������ַ ����ʵ����������
����һ������������ʱ��:150ms
*********************************************************************/
void W25Q64_SPI_Erase_Sector(uint32_t Dst_Addr)   
{  
	//����falsh�������,������   
 	//printf("fe:%x\r\n",Dst_Addr);	  
	Dst_Addr*=4096;
	W25Q64_SPI_Write_Enable();                  //SET WEL 	 
	W25Q64_SPI_Wait_Busy();   
	W25Q64_SPI_CS_ENABLE();                            //ʹ������   
	HAL_SPI_Send_Byte(W25X_SectorErase);   //������������ָ�� 
	HAL_SPI_Send_Byte((uint8_t)((Dst_Addr)>>16));  //����24bit��ַ    
	HAL_SPI_Send_Byte((uint8_t)((Dst_Addr)>>8));   
	HAL_SPI_Send_Byte((uint8_t)Dst_Addr);  
	W25Q64_SPI_CS_DISABLE();                            //ȡ��Ƭѡ     	      
	W25Q64_SPI_Wait_Busy();   				    //�ȴ��������
} 

/*********************************************************************
�������ģʽ
*********************************************************************/
void W25Q64_SPI_PowerDown(void)   
{ 
	W25Q64_SPI_CS_ENABLE();                            //ʹ������   
	HAL_SPI_Send_Byte(W25X_PowerDown);     //���͵�������  
	W25Q64_SPI_CS_DISABLE();                            //ȡ��Ƭѡ     	      
	HAL_Delay(1);                            //�ȴ�TPD  
} 

/**
  * @}
  */


