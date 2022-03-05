

#ifndef OLED_H_
#define OLED_H_

#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>

#define GPIO_OLED_CS_PORT_BASE      GPIO_PORTE_BASE  
#define GPIO_OLED_CS_PORT_SYSCTL    SYSCTL_PERIPH_GPIOE
#define GPIO_OLED_CS_PIN            GPIO_PIN_5      

#define GPIO_OLED_DC_PORT_BASE      GPIO_PORTC_BASE  
#define GPIO_OLED_DC_PORT_SYSCTL    SYSCTL_PERIPH_GPIOC
#define GPIO_OLED_DC_PIN            GPIO_PIN_6

#define GPIO_OLED_RES_PORT_BASE     GPIO_PORTC_BASE  
#define GPIO_OLED_RES_PORT_SYSCTL   SYSCTL_PERIPH_GPIOC
#define GPIO_OLED_RES_PIN           GPIO_PIN_5

#define GPIO_OLED_DAT_PORT_BASE     GPIO_PORTC_BASE  
#define GPIO_OLED_DAT_PORT_SYSCTL   SYSCTL_PERIPH_GPIOC
#define GPIO_OLED_DAT_PIN           GPIO_PIN_4

#define GPIO_OLED_SCLK_PORT_BASE    GPIO_PORTE_BASE  
#define GPIO_OLED_SCLK_PORT_SYSCTL  SYSCTL_PERIPH_GPIOE
#define GPIO_OLED_SCLK_PIN          GPIO_PIN_4

#define  u8 unsigned char
#define  u32 unsigned int
#define OLED_CMD  0 
#define OLED_DATA 1 

#define OLED_MODE 0

#define SIZE 16
#define XLevelL     0x02
#define XLevelH     0x10
#define Max_Column  128
#define Max_Row     64
#define Brightness  0xFF
#define X_WIDTH     128
#define Y_WIDTH     64

void delay_ms(unsigned int ms);

void OLED_WR_Byte(u8 dat, u8 cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x, u8 y, u8 t);
void OLED_Fill(u8 x1, u8 y1, u8 x2, u8 y2, u8 dot);
void OLED_ShowChar(u8 x, u8 y, u8 chr);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size2);
void OLED_ShowString(u8 x, u8 y, u8 *p);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x, u8 y, u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1,
                  unsigned char y1, const unsigned char BMP[]);
void OLED_Wave_showing(uint32_t* Data_Addr,uint32_t Jmp_Step) ;
void OLED_Value_One_Page(float  Now_THD,float  Now_Fre,float  Now_1th,float  Now_2nd);
void OLED_Value_Two_Page(float  Now_3rd,float  Now_4th,float  Now_5th);

extern uint32_t AD_DATA[] ;
#endif 

