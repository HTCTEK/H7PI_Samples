#include "quadspi.h"
#include "qspiflash.h"

extern QSPI_HandleTypeDef hqspi;
QSPI_CommandTypeDef s_command;
//===============================================================//
//W25Q64 QSPI�ӿڳ�ʼ��
//===============================================================//
void W25Q64_QSPI_Init(void)
{
	MX_QUADSPI_Init();
}

//===============================================================//
//W25Q64 ʹ�ܸ�λ
//===============================================================//
void W25Q64_QSPI_ResetEnable(void)
{
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction       = W25X_ResetEnable;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_NONE;
	s_command.DummyCycles       = 0;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}	  
}
//===============================================================//
//W25Q64 ��λ
//===============================================================//
void W25Q64_QSPI_Reset(void)
{
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction       = W25X_Reset;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_NONE;
	s_command.DummyCycles       = 0;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}	  
}

//===============================================================//
//W25Q64 QSPIдʹ��
//===============================================================//
void W25Q64_QSPI_WriteEnable(void)
{
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction       = W25X_WriteEnable;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_NONE;
	s_command.DummyCycles       = 0;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}	      
}

//===============================================================//
//W25Q64 QSPIд��ֹ
//===============================================================//
void W25Q64_QSPI_WriteDisable(void)
{
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction       = W25X_WriteDisable;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_NONE;
	s_command.DummyCycles       = 0;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}	      
}

unsigned char W25Q64_QSPI_ReadSR(unsigned char SR)
{
	unsigned char byte=0;
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction       = SR;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.Address           = 0x0;
	s_command.AddressSize       = QSPI_ADDRESS_24_BITS;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_1_LINE;
	s_command.DummyCycles       = 0;
	s_command.NbData            = 1;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
	if (HAL_QSPI_Command(&hqspi, &s_command,0xffff) != HAL_OK)
	{
		
	}
	if (HAL_QSPI_Receive(&hqspi,&byte,0xffff) != HAL_OK)
	{
		
	}
    return byte;
}

void W25Q64_QSPI_WaitBusy(void)
{
	while((W25Q64_QSPI_ReadSR(W25X_ReadStatusReg1)&0x01)==0x01);
}

void W25Q64_QSPI_WriteSR(unsigned char *SR,unsigned char NumSR)
{
	W25Q64_QSPI_WriteEnable();                  
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction       = W25X_WriteStatusReg;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.Address           = W25X_WriteStatusReg;
	s_command.AddressSize       = QSPI_ADDRESS_24_BITS;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_1_LINE;
	s_command.DummyCycles       = 0;
	s_command.NbData            = NumSR;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
	if (HAL_QSPI_Command(&hqspi, &s_command,0xffff) != HAL_OK)
	{

	}
	if (HAL_QSPI_Transmit(&hqspi,SR,0xffff) != HAL_OK)
	{
		
	}
	W25Q64_QSPI_WaitBusy();				  
}

void W25Q64_QSPI_QuadWriteEnable(void)
{
	unsigned char temp[2];
	temp[0]=W25Q64_QSPI_ReadSR(W25X_ReadStatusReg1);
	temp[1]=W25Q64_QSPI_ReadSR(W25X_ReadStatusReg2);
	if((temp[1]&0x02) != 0x02)
	{		
		temp[1] = 0x02;
		W25Q64_QSPI_WriteEnable();
		W25Q64_QSPI_WriteSR(temp,2);
	}
}

void W25Q64_QSPI_QuadWriteDisable(void)
{
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction       = W25X_WriteDisable;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_NONE;
	s_command.DummyCycles       = 0;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Error_Handler();
	}	  
}

//===============================================================//
//W25Q64 QSPI ��������(Sector = 4KB)�ӿ�
//===============================================================//
void W25Q64_QSPI_EraseSector(unsigned long SectorAddress)
{
	SectorAddress*=4096;
	W25Q64_QSPI_WriteEnable();                  
	W25Q64_QSPI_WaitBusy();   
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction       = W25X_SectorErase;
	s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
	s_command.Address           = SectorAddress;
	s_command.AddressSize       = QSPI_ADDRESS_24_BITS;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_NONE;
	s_command.DummyCycles       = 0;
	s_command.NbData            = 0;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
	if (HAL_QSPI_Command(&hqspi, &s_command,0xffff) != HAL_OK)
	{

	}
	W25Q64_QSPI_WaitBusy();   				   	//�ȴ��������
}

//===============================================================//
//W25Q64 QSPI �����(Block32KB = 32KB)�ӿ�
//===============================================================//
void W25Q64_QSPI_EraseBlock32KB(unsigned long Block32KBAddress)
{

}

//===============================================================//
//W25Q64 QSPI �����(Block64KB = 64KB)�ӿ�
//===============================================================//
void W25Q64_QSPI_EraseBlock64KB(unsigned long Block64KBAddress)
{
	
}


void W25Q64_QSPI_EraseChip(void)
{
	W25Q64_QSPI_WriteEnable();                  //SET WEL 
	W25Q64_QSPI_WaitBusy();   
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction       = W25X_ChipErase;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.Address           = 0;
	s_command.AddressSize       = QSPI_ADDRESS_24_BITS;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_NONE;
	s_command.DummyCycles       = 0;
	s_command.NbData            = 0;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
	if (HAL_QSPI_Command(&hqspi, &s_command,0xffff) != HAL_OK)
	{

	} 
	W25Q64_QSPI_WaitBusy();   				   	//�ȴ�оƬ��������
}
//===============================================================//
//W25Q64 QSPI ������ģʽ�ӿ�
//===============================================================//
void W25Q64_QSPI_ReadMode(unsigned char ReadModeCmd)
{
	
}

//===============================================================//
//W25Q64 QSPI �����ݽӿ�
//===============================================================//
void W25Q64_QSPI_ReadData(unsigned long Address,unsigned char *buff,unsigned long NumBytes)
{
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction       = W25X_FastReadQuad;
	s_command.AddressMode       = QSPI_ADDRESS_4_LINES;

	s_command.Address           = Address;
	s_command.AddressSize       = QSPI_ADDRESS_24_BITS;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_4_LINES;
	s_command.AlternateBytes 		= 0x00;
	s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTES_32_BITS;
	s_command.DataMode          = QSPI_DATA_4_LINES;
	s_command.DummyCycles       = 4;
	s_command.NbData            = NumBytes;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &s_command,0xffff) != HAL_OK)
	{

	}
	if (HAL_QSPI_Receive(&hqspi,buff,0xffff) != HAL_OK)
	{

	}
	W25Q64_QSPI_WaitBusy();
}

//===============================================================//
//W25Q64 QSPI ��ҳ����(Page = 256Bytes)�ӿ�
//===============================================================//
void W25Q64_QSPI_WritePage(unsigned long Address,unsigned char *buff,unsigned long NumBytes)
{
	W25Q64_QSPI_WriteEnable();            
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction       = W25X_PageProgramQuad;
	s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
	s_command.Address           = Address;
	s_command.AddressSize       = QSPI_ADDRESS_24_BITS;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_4_LINES;
	s_command.DummyCycles       = 0;
	s_command.NbData            = NumBytes;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
	if (HAL_QSPI_Command(&hqspi, &s_command,0xffff) != HAL_OK)
	{

	}
	if (HAL_QSPI_Transmit(&hqspi,buff,0xffff) != HAL_OK)
	{
		
	}
	W25Q64_QSPI_WaitBusy();						//�ȴ�д�����
}

void W25Q64_QSPI_WriteNoCheck(unsigned long Address,unsigned char *buff,unsigned long NumBytes)
{
	unsigned short pageremain;	   
	pageremain=256-Address%256; 				//��ҳʣ����ֽ���		 	    
	if(NumBytes<=pageremain)pageremain=NumBytes;//������256���ֽ�
	while(1)
	{	   
		W25Q64_QSPI_WritePage(Address,buff,pageremain);
		if(NumBytes==pageremain)break;			//д�������
	 	else 									//NumByteToWrite>pageremain
		{
			buff+=pageremain;
			Address+=pageremain;	
			NumBytes-=pageremain;			  	//��ȥ�Ѿ�д���˵��ֽ���
			if(NumBytes>256)pageremain=256; 	//һ�ο���д��256���ֽ�
			else pageremain=NumBytes; 	  		//����256���ֽ���
		}
	};	
}

unsigned char W25QxxCache[4096] = {0};
//===============================================================//
//W25Q64 QSPI д���ݽӿ�
//===============================================================//
void W25Q64_QSPI_WriteData(unsigned long Address,unsigned char *buff,unsigned long NumBytes)
{
	unsigned long secpos;
	unsigned short secoff;
	unsigned short secremain;	   
 	volatile unsigned short i;    
	unsigned char * W25QXX_BUF;	
    W25QXX_BUF=W25QxxCache; 
    
 	secpos=Address/4096;											//������ַ  
	secoff=Address%4096;											//�������ڵ�ƫ��
	secremain=4096-secoff;											//����ʣ��ռ��С   
 	if(NumBytes<=secremain)secremain=NumBytes;						//������4096���ֽ�
	while(1) 
	{	
		W25Q64_QSPI_ReadData(secpos*4096,W25QXX_BUF,4096);			//������������������
		for(i=0;i<secremain;i++)									//У������
		{
			if(W25QXX_BUF[secoff+i]!=buff[i])break;					//��֤�����Ƿ���Ҫ������д  	  
		}		
		if(i<secremain)												//��Ҫ����
		{
			W25Q64_QSPI_EraseSector(secpos);						//�����������
			for(i=0;i<secremain;i++)	  							//����
			{
				W25QXX_BUF[i+secoff]=buff[i];	  
			}
			W25Q64_QSPI_WriteNoCheck(secpos*4096,W25QXX_BUF,4096);	//д����������  
		}
		else if(NumBytes==secremain)break;							//д�������
		else														//д��δ����
		{
			secpos++;												//������ַ��1
			secoff=0;												//ƫ��λ��Ϊ0 	 
			buff+=secremain;  										//ָ��ƫ��
			Address+=secremain;										//д��ַƫ��	   
			NumBytes-=secremain;									//�ֽ����ݼ�
			if(NumBytes>4096)secremain=4096;						//��һ����������д����
			else secremain=NumBytes;								//��һ����������д����
		}	 
	}	
}

//===============================================================//
//W25Q64 QSPI дҳ����(Page = 256Bytes)�ӿ�
//===============================================================//
//void W25Q64_QSPI_WritePage(unsigned long Address,unsigned char *buff)
//{
//	
//}

//===============================================================//
//W25Q64 QSPI д������(Block = 256Bytes)�ӿ�
//===============================================================//
void W25Q64_QSPI_WriteBlock4KB(unsigned long Block4KBAdress,unsigned char *buff)
{
	
}

//===============================================================//
//W25Q64 QSPI ��������(Page = 256Bytes)�ӿ�
//===============================================================//
void W25Q64_QSPI_ReadBlock4KB(unsigned long Block4KBAdress,unsigned char *buff)
{
	
}

unsigned long W25Q64_QSPI_ReadID(void)
{
	uint8_t Temp[2];	
	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction       = W25X_ManufactDeviceID;
	s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
	s_command.Address           = 0;
	s_command.AddressSize       = QSPI_ADDRESS_24_BITS;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.AlternateBytes 		= 0x00;
	s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	s_command.DataMode          = QSPI_DATA_1_LINE;
	s_command.DummyCycles       = 0;
	s_command.NbData            = 2;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(&hqspi, &s_command,0xffff) != HAL_OK)
	{

	}
	if (HAL_QSPI_Receive(&hqspi,Temp,0xffff) != HAL_OK)
	{
		
	}		 
	return (Temp[0]<<8) + Temp[1];
}

void W25QXX_Memory_Mapped_Enable(void)   
{
	QSPI_MemoryMappedTypeDef sMemMappedCfg;

	sMemMappedCfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;

	s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command.Instruction       = W25X_FastReadQuad;
	s_command.AddressMode       = QSPI_ADDRESS_4_LINES;
	s_command.Address           = 0;
	s_command.AddressSize       = QSPI_ADDRESS_24_BITS;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_4_LINES;
	s_command.AlternateBytes 		= 0x00;
	s_command.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	s_command.DataMode          = QSPI_DATA_4_LINES;
	s_command.DummyCycles       = 4;
	s_command.NbData            = 0;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
//	s_command.SIOOMode          = QSPI_SIOO_INST_ONLY_FIRST_CMD;		//ֻ����һ��ָ��

	if (HAL_QSPI_MemoryMapped(&hqspi, &s_command, &sMemMappedCfg) != HAL_OK)
	{
		Error_Handler();
	} 
} 


