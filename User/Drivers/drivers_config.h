#ifndef __DRIVERS_CONFIG__
#define __DRIVERS_CONFIG__

/******************************************
显示驱动配置，最大的ID需要小于下方的定义
这个定义可以在GUI_Config.h里设置
并且需要从小到大，不能跨越，
例如，如果不使用OLED,但是使用ST7789,
那么7789必须是1，不能为2
#define GUI_NUM_LAYERS            3 
******************************************/
#define ID_GUI_LCD        0
#define ID_GUI_OLED       2
#define ID_GUI_LCD_ST7789 1

#endif


