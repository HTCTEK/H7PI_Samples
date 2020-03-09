/*
*---------------------------------------------------------------
*                        emWin字体工具                           
*                                                               
* 注:支持unicode/GBK编码切换,支持抗锯齿                             
* 注:本字体文件由emWin字体工具 V0.4 生成                             
* 作者:阿里(qq:617622104)                                         
*---------------------------------------------------------------
*/


#include "GUI.h"


#include "GUI_Private.h"
#include <string.h>
#include <stdint.h>





typedef struct{
    U16 min;
    U16 max;
    U8 reserved[4];
}x_header_t;//头
typedef struct{
    U16 size;
    U8 pos[4];
}x_table_t;//位置信息
typedef struct{
    U8 XSize;
    U8 XDist;
    U16 bpl;
}x_info_t;//字体信息


static x_header_t x_header;
static unsigned char g_font_buf[61];//软件已计算好BUFF大小，无需更改BUFF大小

//用户实现函数，用来读取字模数据
//offset：地址偏移
//size：读取的字节大小
static unsigned char *heiti14_getData(int offset, int size){
    //字模保存在SPIFLASH示例 SPIFLASH_Read(g_font_buf,pFontAddr+offset,size);
    //字模已加载到SDRAM示例  memcpy(g_font_buf,pFontAddr+offset,size);
    extern uint8_t font_ReadFont(uint8_t* buffer,const char* font, uint32_t offset, uint32_t size);
		font_ReadFont(g_font_buf,"heiti14.bin",offset,size);
    return g_font_buf;
}

static x_table_t* heiti14_GetTable(U16P c) {
    x_table_t *pTable = (x_table_t *)heiti14_getData((c-x_header.min)*sizeof(x_table_t)+sizeof(x_header_t),sizeof(x_table_t));
    return pTable;
}

static void heiti14_DispChar(U16P c) {
    int BytesPerLine;
    GUI_DRAWMODE DrawMode = GUI_pContext->TextMode;
    x_table_t *pTable = heiti14_GetTable(c);

    if ( pTable->size ) {
        GUI_DRAWMODE OldDrawMode;
        int pos = 0;
        memcpy(&pos, pTable->pos, 4);
        U8 *pMapData = heiti14_getData(pos,pTable->size);
        x_info_t *pInfo = (x_info_t *)pMapData;
        U8 *pData = pMapData+sizeof(x_info_t);
        BytesPerLine = pInfo->bpl;
        OldDrawMode  = LCD_SetDrawMode(DrawMode);

        LCD_DrawBitmap( GUI_pContext->DispPosX, GUI_pContext->DispPosY,
                        pInfo->XSize,
                        GUI_pContext->pAFont->YSize,
                        GUI_pContext->pAFont->XMag,
                        GUI_pContext->pAFont->YMag,
                        1,
                        BytesPerLine,
                        pData,
                        &LCD_BKCOLORINDEX);

        if (GUI_pContext->pAFont->YDist > GUI_pContext->pAFont->YSize) {
            int YMag = GUI_pContext->pAFont->YMag;
            int YDist = GUI_pContext->pAFont->YDist * YMag;
            int YSize = GUI_pContext->pAFont->YSize * YMag;
            if (DrawMode != LCD_DRAWMODE_TRANS) {
                LCD_COLOR OldColor = GUI_GetColor();
                GUI_SetColor(GUI_GetBkColor());
                LCD_FillRect(GUI_pContext->DispPosX,
                GUI_pContext->DispPosY + YSize,
                GUI_pContext->DispPosX + pInfo->XSize,
                GUI_pContext->DispPosY + YDist);
                GUI_SetColor(OldColor);
            }
        }
        LCD_SetDrawMode(OldDrawMode);
        GUI_pContext->DispPosX += pInfo->XDist * GUI_pContext->pAFont->XMag;
    }
}

static int heiti14_GetCharDistX(U16P c, int * pSizeX) {
    static char x_header_once = 1;
    if(x_header_once){
        x_header_once = 0;
        x_header_t *pHeader = (x_header_t *)heiti14_getData(0,sizeof(x_header_t));
        memcpy(&x_header, pHeader, sizeof(x_header_t));
    }
    static int sizeX = 0;
    if ( *pSizeX!=0 ){
        x_table_t *pTable = heiti14_GetTable(c);
        if ( pTable->size )
        {
            int pos = 0;
            memcpy(&pos, pTable->pos, 4);
            x_info_t *pInfo = (x_info_t *)heiti14_getData(pos,sizeof(x_info_t));
            sizeX += pInfo->XSize;
        }
    }
    else {
        *pSizeX = sizeX;
        sizeX = 0;
    }
    return 0;
}

static void heiti14_GetFontInfo(const GUI_FONT * pFont, GUI_FONTINFO* pfi) {
    pfi->Flags = GUI_FONTINFO_FLAG_PROP | GUI_FONTINFO_FLAG_AA4;
}

static char heiti14_IsInFont(const GUI_FONT * pFont, U16 c) {
    return 1;
}


//字体类型：外部字体,类似XBF,最优
//黑体,Regular,14
//字模高度：24,垂直偏移：0
GUI_CONST_STORAGE GUI_FONT heiti14 = {
heiti14_DispChar,
heiti14_GetCharDistX,
heiti14_GetFontInfo,
heiti14_IsInFont,
(GUI_GETCHARINFO  *)0,
(tGUI_ENC_APIList *)0,
19, /* height of font  */
19, /* space of font y */
1,
1,
(void*)0,
};
