#include "lcd.h"



/**********************************************************
 * lcd 复位控制信号
 *
 */
void LCD_Reset(void)
{
	HAL_GPIO_WritePin(LCD_RST,(GPIO_PinState)1);
	osDelay(2);
	HAL_GPIO_WritePin(LCD_RST,(GPIO_PinState)0);
	osDelay(2);
	HAL_GPIO_WritePin(LCD_RST,(GPIO_PinState)1);
}


/* *********************************************
 *0~100
 * 
*/
void lcd_SetBacklight(uint8_t brightness)
{
	if(brightness > 100)
	{
		return;
	}
	TIM8->CCR1 = brightness*10;
}

/**********************************************************
 * 背光控制
 *
 */
void lcd_BacklightInit(void)
{
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
	lcd_SetBacklight(0);
}


uint32_t DFT_SCAN_DIR;

				 
//TFT的画笔颜色和背景色	   
uint16_t POINT_COLOR=0x0000;	//画笔颜色
uint16_t BACK_COLOR=0xFFFF;  //背景色 

//管理TFT重要参数
//默认为竖屏
LCD_t tftdev;



uint8_t lcd_RD_DATA(void)
{
	return LCD_RAM;
}


		   
//写寄存器函数
//regval:寄存器值
void lcd_WR_REG(uint32_t regval)
{ 

	LCD_REG = (regval&0XFF); 

}
//写TFT数据
//data:要写入的值
void lcd_WR_DATA(uint16_t data)
{										    	   
	LCD_RAM = (data&0XFF);
}					   
//写寄存器
//lcd_Reg:寄存器地址
//lcd_RegValue:要写入的数据
void lcd_WriteReg(uint32_t lcd_Reg, uint16_t lcd_RegValue)
{	
	lcd_WR_REG(lcd_Reg);
	lcd_WR_DATA(lcd_RegValue);
}	      
//开始写GRAM
void lcd_WriteRAM_Prepare(void)
{
 	lcd_WR_REG(tftdev.wramcmd);
}	 
//TFT写GRAM
//RGB_Code:颜色值
void lcd_WriteRAM(uint16_t RGB_Code)
{							    

	LCD_RAM = ((RGB_Code>>8));
	LCD_RAM = (RGB_Code&0XFF);

}

 
//设置窗口
void lcd_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{   
	width=sx+width-1;
	height=sy+height-1;

	lcd_WR_REG(tftdev.setxcmd);
	lcd_WR_DATA(sx>>8);  
	lcd_WR_DATA(sx&0XFF);	  
	lcd_WR_DATA(width>>8);   
	lcd_WR_DATA(width&0XFF);   
	lcd_WR_REG(tftdev.setycmd);
	lcd_WR_DATA(sy>>8);   
	lcd_WR_DATA(sy&0XFF);  
	lcd_WR_DATA(height>>8);   
	lcd_WR_DATA(height&0XFF);  
}

//设置光标位置
//Xpos:横坐标
//Ypos:纵坐标
void lcd_SetCursor(uint16_t Xpos, uint16_t Ypos)
{	 
	lcd_WR_REG(tftdev.setxcmd); 
	lcd_WR_DATA(Xpos>>8); 
	lcd_WR_DATA(Xpos&0XFF);	
  	
	lcd_WR_REG(tftdev.setycmd); 
	lcd_WR_DATA(Ypos>>8); 
	lcd_WR_DATA(Ypos&0XFF);
} 		 
//设置TFT的自动扫描方向
//注意:其他函数可能会受到此函数设置的影响(尤其是9341/6804这两个奇葩),
//所以,一般设置为L2R_U2D即可,如果设置为其他扫描方式,可能导致显示不正常.
//dir:0~7,代表8个方向(具体定义见tft.h)
//9320/9325/9328/4531/4535/1505/b505/8989/5408/9341等IC已经实际测试	   	   
void lcd_Scan_Dir(uint32_t dir)
{
	uint16_t regval=0;
	uint32_t dirreg=0;
//	uint16_t temp;  
	switch(dir)//方向转换
	{
		case 0:dir=6;break;
		case 1:dir=7;break;
		case 2:dir=4;break;
		case 3:dir=5;break;
		case 4:dir=1;break;
		case 5:dir=0;break;
		case 6:dir=3;break;
		case 7:dir=2;break;	     
	}
	switch(dir)
	{
		case L2R_U2D://从左到右,从上到下
			regval|=(0<<7)|(0<<6)|(0<<5); 
			break;
		case L2R_D2U://从左到右,从下到上
			regval|=(1<<7)|(0<<6)|(0<<5); 
			break;
		case R2L_U2D://从右到左,从上到下
			regval|=(0<<7)|(1<<6)|(0<<5); 
			break;
		case R2L_D2U://从右到左,从下到上
			regval|=(1<<7)|(1<<6)|(0<<5); 
			break;	 
		case U2D_L2R://从上到下,从左到右
			regval|=(0<<7)|(0<<6)|(1<<5); 
			break;
		case U2D_R2L://从上到下,从右到左
			regval|=(0<<7)|(1<<6)|(1<<5); 
			break;
		case D2U_L2R://从下到上,从左到右
			regval|=(1<<7)|(0<<6)|(1<<5); 
			break;
		case D2U_R2L://从下到上,从右到左
			regval|=(1<<7)|(1<<6)|(1<<5); 
			break;	 
	}
	dirreg=0X36; 
  regval|=0x08;	
	lcd_WriteReg(dirreg,regval);
			
	lcd_WR_REG(tftdev.setxcmd); 
	lcd_WR_DATA(0);lcd_WR_DATA(0);
	lcd_WR_DATA((tftdev.width-1)>>8);lcd_WR_DATA((tftdev.width-1)&0XFF);
	lcd_WR_REG(tftdev.setycmd); 
	lcd_WR_DATA(0);lcd_WR_DATA(0);
	lcd_WR_DATA((tftdev.height-1)>>8);lcd_WR_DATA((tftdev.height-1)&0XFF);  
}    



//画点
//x,y:坐标
//POINT_COLOR:此点的颜色
void lcd_DrawPoint(uint16_t x,uint16_t y)
{
	lcd_SetCursor(x,y);		//设置光标位置 
	lcd_WriteRAM_Prepare();	//开始写入GRAM
	lcd_WriteRAM(POINT_COLOR); 
}

//设置TFT显示方向（6804不支持横屏显示）
//dir:1,竖屏；0,横屏
void lcd_Display_Dir(uint32_t dir)
{
	if(dir==0)			
	{
		tftdev.dir=0;
		tftdev.width=320;
		tftdev.height=240;

		tftdev.wramcmd=0X2C;
		tftdev.setxcmd=0X2A;
		tftdev.setycmd=0X2B;  
    DFT_SCAN_DIR=L2R_U2D;		

	}else 				
	{	  				
		tftdev.dir=1;	
		tftdev.width=240;
		tftdev.height=320;

		tftdev.wramcmd=0X2C;
		tftdev.setxcmd=0X2A;
		tftdev.setycmd=0X2B;  
    DFT_SCAN_DIR=U2D_R2L;		
		
	} 
	
	lcd_Scan_Dir(DFT_SCAN_DIR);	//默认扫描方向
  //lcd_Set_Window(0,0,tftdev.width,tftdev.height);
}


//初始化tft
//该初始化函数可以初始化各种ILI93XX液晶,但是其他函数是基于ILI9320的!!!
//在其他型号的驱动芯片上没有测试! 

void lcd_Init(void)
{ 				
	lcd_BacklightInit();			
  //TFT复位 
	LCD_RST_SET;
	HAL_Delay(10);
	LCD_RST_RESET;
	HAL_Delay(20);
	LCD_RST_SET;
	HAL_Delay(20);
	
	lcd_WR_REG(0xCF);  
	lcd_WR_DATA(0x00); 
	lcd_WR_DATA(0x81); 
	lcd_WR_DATA(0X30); 
	lcd_WR_REG(0xED);  
	lcd_WR_DATA(0x64); 
	lcd_WR_DATA(0x03); 
	lcd_WR_DATA(0X12); 
	lcd_WR_DATA(0X81); 
	lcd_WR_REG(0xE8);  
	lcd_WR_DATA(0x85); 
	lcd_WR_DATA(0x10); 
	lcd_WR_DATA(0x78); 
	lcd_WR_REG(0xCB);  
	lcd_WR_DATA(0x39); 
	lcd_WR_DATA(0x2C); 
	lcd_WR_DATA(0x00); 
	lcd_WR_DATA(0x34); 
	lcd_WR_DATA(0x02); 
	lcd_WR_REG(0xF7);  
	lcd_WR_DATA(0x20); 
	lcd_WR_REG(0xEA);  
	lcd_WR_DATA(0x00); 
	lcd_WR_DATA(0x00); 
	lcd_WR_REG(0xB1);   
	lcd_WR_DATA(0x00);   
	lcd_WR_DATA(0x1B); 
	lcd_WR_REG(0xB6);     // Display Function Control 
	lcd_WR_DATA(0x0A); 
	lcd_WR_DATA(0xA2); 
	lcd_WR_REG(0xC0);     //Power control 
	lcd_WR_DATA(0x21);    //VRH[5:0] 
	lcd_WR_REG(0xC1);     //Power control 
	lcd_WR_DATA(0x11);    //SAP[2:0];BT[3:0]
	lcd_WR_REG(0xC5);     //VCM control 
	lcd_WR_DATA(0x3F); 
	lcd_WR_DATA(0x3C); 
	lcd_WR_REG(0xC7);     //VCM control2 
	lcd_WR_DATA(0Xb5); 
	lcd_WR_REG(0x36);    // Memory Access Control 
	lcd_WR_DATA(0x48); 
	lcd_WR_REG(0x3A);      
	lcd_WR_DATA(0x55); 
	lcd_WR_REG(0xF2);     // 3Gamma Function Disable 
	lcd_WR_DATA(0x00); 
	lcd_WR_REG(0x26);     //Gamma curve selected 
	lcd_WR_DATA(0x01); 
	lcd_WR_REG(0xE0);     //Set Gamma 
	lcd_WR_DATA(0x0F); 
	lcd_WR_DATA(0x26); 
	lcd_WR_DATA(0x24); 
	lcd_WR_DATA(0x0B); 
	lcd_WR_DATA(0x0E); 
	lcd_WR_DATA(0x09); 
	lcd_WR_DATA(0x54); 
	lcd_WR_DATA(0XA8); 
	lcd_WR_DATA(0x46); 
	lcd_WR_DATA(0x0C); 
	lcd_WR_DATA(0x17); 
	lcd_WR_DATA(0x09); 
	lcd_WR_DATA(0x0F); 
	lcd_WR_DATA(0x07); 
	lcd_WR_DATA(0x00); 
	lcd_WR_REG(0XE1);     //Set Gamma 
	lcd_WR_DATA(0x00); 
	lcd_WR_DATA(0x19); 
	lcd_WR_DATA(0x1B); 
	lcd_WR_DATA(0x04); 
	lcd_WR_DATA(0x10); 
	lcd_WR_DATA(0x07); 
	lcd_WR_DATA(0x2A); 
	lcd_WR_DATA(0x47); 
	lcd_WR_DATA(0x39); 
	lcd_WR_DATA(0x03); 
	lcd_WR_DATA(0x06); 
	lcd_WR_DATA(0x06); 
	lcd_WR_DATA(0x30); 
	lcd_WR_DATA(0x38); 
	lcd_WR_DATA(0x0F); 
	lcd_WR_REG(0x11);     //Exit Sleep  Sleep
	osDelay(20);
	lcd_WR_REG(0x29); //display on	
	lcd_Display_Dir(0);		 
	lcd_Clear(BLACK);
	//lcd_SetBacklight(50);
}  

//清屏函数
//color:要清屏的填充色
void lcd_Clear(uint16_t color)
{
	uint32_t index=0;      
	uint32_t totalpoint=tftdev.width;
	totalpoint*=tftdev.height; 	//得到总点数
  lcd_SetCursor(0x00,0x0000);	//设置光标位置
	lcd_WriteRAM_Prepare();     //开始写入GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		lcd_WriteRAM(color);	   
	}
}  
//在指定区域内填充单个颜色
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void lcd_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
	uint16_t i,j;
	uint16_t xlen=0;
	xlen=ex-sx+1;	   
	for(i=sy;i<=ey;i++)
	{
	 	lcd_SetCursor(sx,i);      				//设置光标位置 
		lcd_WriteRAM_Prepare();     			//开始写入GRAM	  
		for(j=0;j<xlen;j++)lcd_WriteRAM(color);	//设置光标位置 	    
	}
}  
//在指定区域内填充指定颜色块			 
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void lcd_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{  
	uint16_t height,width;
	uint16_t i,j;
	width=ex-sx+1; 		//得到填充的宽度
	height=ey-sy+1;		//高度
 	for(i=0;i<height;i++)
	{
 		lcd_SetCursor(sx,sy+i);   	//设置光标位置 
		lcd_WriteRAM_Prepare();     //开始写入GRAM
		for(j=0;j<width;j++)lcd_WriteRAM(color[i*height+j]);//写入数据 
	}	  
}  
//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void lcd_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		lcd_DrawPoint(uRow,uCol);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//画矩形	  
//(x1,y1),(x2,y2):矩形的对角坐标
void lcd_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	lcd_DrawLine(x1,y1,x2,y1);
	lcd_DrawLine(x1,y1,x1,y2);
	lcd_DrawLine(x1,y2,x2,y2);
	lcd_DrawLine(x2,y1,x2,y2);
}
//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void lcd_DrawCircle(uint16_t x0,uint16_t y0,uint32_t r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		lcd_DrawPoint(x0+a,y0-b);             //5
 		lcd_DrawPoint(x0+b,y0-a);             //0           
		lcd_DrawPoint(x0+b,y0+a);             //4               
		lcd_DrawPoint(x0+a,y0+b);             //6 
		lcd_DrawPoint(x0-a,y0+b);             //1       
 		lcd_DrawPoint(x0-b,y0+a);             
		lcd_DrawPoint(x0-a,y0-b);             //2             
  		lcd_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  

