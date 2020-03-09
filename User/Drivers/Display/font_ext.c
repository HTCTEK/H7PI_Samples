#include "font_ext.h"




uint8_t font_ReadFont(uint8_t* buffer, char* font, uint32_t offset, uint32_t size)
{
	FRESULT  res = FR_OK;
	FIL      fontfile;
	DIR      fontdir;
	uint32_t index = 0;
	char     path[32]={FONT_PATH};
	char*    fontbuff=NULL;
	
	res = f_opendir(&fontdir,path);
	if (res == FR_NO_PATH)
	{
		f_mkdir(FONT_PATH);
		return 0;
	}
	strcat(path,"/");
	strcat(path,font);
	res = f_open(&fontfile,(const TCHAR*)path, FA_READ);
	if(res == FR_OK)
	{
		res = f_lseek(&fontfile,offset);
		if(res == FR_OK)
		{
			res = f_read(&fontfile,buffer,size,&index);
			if(res == FR_OK)
			{
				f_close(&fontfile);
				return 1;
			}
		}
	}
	f_closedir(&fontdir);
	f_close(&fontfile);
	return 0;
}