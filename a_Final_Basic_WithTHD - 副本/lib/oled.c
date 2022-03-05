#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "oled.h"
#include "oledfont.h"

#define  u8 unsigned char
#define  u32 unsigned int

#define OLED_CS_Clr()  MAP_GPIOPinWrite(GPIO_OLED_CS_PORT_BASE,GPIO_OLED_CS_PIN,0)    //OLED_CS=0
#define OLED_CS_Set()  MAP_GPIOPinWrite(GPIO_OLED_CS_PORT_BASE,GPIO_OLED_CS_PIN,0xFF) //OLED_CS=1

#define OLED_RST_Clr() MAP_GPIOPinWrite(GPIO_OLED_RES_PORT_BASE,GPIO_OLED_RES_PIN,0)   //OLED_RST=0
#define OLED_RST_Set() MAP_GPIOPinWrite(GPIO_OLED_RES_PORT_BASE,GPIO_OLED_RES_PIN,0xFF)//OLED_RST=1

#define OLED_DC_Clr()  MAP_GPIOPinWrite(GPIO_OLED_DC_PORT_BASE,GPIO_OLED_DC_PIN,0)     //OLED_DC=0
#define OLED_DC_Set()  MAP_GPIOPinWrite(GPIO_OLED_DC_PORT_BASE,GPIO_OLED_DC_PIN,0xFF)  //OLED_DC=1

#define OLED_SCLK_Clr()  MAP_GPIOPinWrite(GPIO_OLED_SCLK_PORT_BASE,GPIO_OLED_SCLK_PIN,0)    //OLED_SCL=0
#define OLED_SCLK_Set()  MAP_GPIOPinWrite(GPIO_OLED_SCLK_PORT_BASE,GPIO_OLED_SCLK_PIN,0xFF) //OLED_SCL=1

#define OLED_SDIN_Clr()  MAP_GPIOPinWrite(GPIO_OLED_DAT_PORT_BASE,GPIO_OLED_DAT_PIN,0)     //OLED_SDIN=0
#define OLED_SDIN_Set()  MAP_GPIOPinWrite(GPIO_OLED_DAT_PORT_BASE,GPIO_OLED_DAT_PIN,0xFF) //OLED_SDIN=1;

#define  x_leng  127

#define M_number 100

int middle_number = 0;

uint32_t AD_DATA[x_leng] = 
{
21,22,23,24,25,26,27,28,29,29,30,31,32,33,34,34,35,36,36,37,
37,38,38,39,39,39,39,40,40,40,40,40,40,40,40,40,39,39,39,38,
38,37,37,36,36,35,35,34,33,32,32,31,30,29,28,27,26,25,24,23,
22,21,20,20,19,18,17,16,15,14,13,12,11,10,9,8,8,7,6,5,
5,4,4,3,3,2,2,1,1,1,0,0,0,0,0,0,0,0,0,1,
1,1,1,2,2,3,3,4,4,5,6,6,7,8,9,10,11,11,12,13,
14,15,16,17,18,19,20
};

u8 OLED_GRAM[127][8] = {0};



void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}


void OLED_Wave_showing(uint32_t* Data_Addr,uint32_t Jmp_Step)
{
	u8 count = 0;
	u8 i;
	u8 j;
	while(count<=127)
	{
		OLED_DrawPoint(count,(Data_Addr[ (int)(count*Jmp_Step) ])/64,1);
		count++;
	}
    OLED_Set_Pos(0,0);
	for(j = 0;j<8;j++)
	{
		OLED_Set_Pos(0,j);
		for(i = 0;i<128;i++)
		{
			OLED_WR_Byte(OLED_GRAM[i][j], OLED_DATA);
		}
	}
	
	
}

void OLED_Value_One_Page(float  Now_THD,float  Now_Fre,float  Now_1th,float  Now_2nd)
{

        OLED_Clear();
		OLED_ShowString(8,0,"THD = ");
		middle_number = (int)Now_THD;
		//OLED_ShowNum(56, 0 , middle_number,2, 16);
		//OLED_ShowString(72,0,".");
        middle_number = Now_THD*100 - middle_number*100; 
        OLED_ShowNum(80, 0 , middle_number,2, 16);
		OLED_ShowString(96,0,"%");
	
        OLED_ShowString(8,2,"Fre = ");
		middle_number = (int)Now_Fre;
		OLED_ShowNum(56, 2 , middle_number,2, 16);
		OLED_ShowString(72,2,".");
        middle_number = Now_Fre*100 - middle_number*100; 
        OLED_ShowNum(80, 2 , middle_number,2, 16);
		OLED_ShowString(96,2,"kHz");

        OLED_ShowString(8,4,"1st = ");
		middle_number = (int)Now_1th;
		//OLED_ShowNum(56, 4 , middle_number,2, 16);
		//OLED_ShowString(72,4,".");
        middle_number = Now_1th*100 - middle_number*100; 
        OLED_ShowNum(80, 4 , middle_number,2, 16);
		OLED_ShowString(96,4,"%");

        OLED_ShowString(8,6,"2nd = ");
		middle_number = (int)Now_2nd;
		OLED_ShowNum(56, 6 , middle_number,2, 16);
		OLED_ShowString(72,6,".");
        middle_number = Now_2nd*100 - middle_number*100; 
        OLED_ShowNum(80, 6 , middle_number,2, 16);
		OLED_ShowString(96, 6 ,"%");
}

void OLED_Value_Two_Page(float  Now_3rd,float  Now_4th,float  Now_5th)
{
        OLED_Clear();
        OLED_ShowString(8,0,"3rd = ");
		middle_number = (int)Now_3rd;
		OLED_ShowNum(56, 0, middle_number,2, 16);
		OLED_ShowString(72,0,".");
        middle_number = Now_3rd*100 - middle_number*100; 
        OLED_ShowNum(80, 0 , middle_number,2, 16);
		OLED_ShowString(96, 0 ,"%");

        OLED_ShowString(8,2,"4th = ");
		middle_number = (int)Now_4th;
		OLED_ShowNum(56, 2 , middle_number,2, 16);
		OLED_ShowString(72,2,".");
        middle_number = Now_4th*100 - middle_number*100; 
        OLED_ShowNum(80, 2 , middle_number,2, 16);
		OLED_ShowString(96, 2 ,"%");

        OLED_ShowString(8,4,"5th = ");
		middle_number = (int)Now_5th;
		OLED_ShowNum(56, 4 , middle_number,2, 16);
		OLED_ShowString(72,4,".");
        middle_number = Now_5th*100 - middle_number*100; 
        OLED_ShowNum(80, 4 , middle_number,2, 16);
		OLED_ShowString(96, 4 ,"%");
}

void delay_ms(unsigned int ms)
{
    unsigned int a;
    while (ms)
    {
        a = 1800;
        while (a--)
            ;
        ms--;
    }

}
#if OLED_MODE==1

void OLED_WR_Byte(u8 dat,u8 cmd)
{
    DATAOUT(dat);
    if(cmd)
      OLED_DC_Set();
    else
      OLED_DC_Clr();
    OLED_CS_Clr();
    OLED_WR_Clr();
    OLED_WR_Set();
    OLED_CS_Set();
    OLED_DC_Set();
}
#else

void OLED_WR_Byte(u8 dat, u8 cmd)
{
    u8 i;
    if (cmd)
    {
        OLED_DC_Set();
    }
    else
    {
        OLED_DC_Clr();
    }
    OLED_CS_Clr();
    for (i = 0; i < 8; i++)
    {
        OLED_SCLK_Clr();
        if (dat & 0x80)
        {
            OLED_SDIN_Set();
        }
        else
            OLED_SDIN_Clr();
        OLED_SCLK_Set();
        dat <<= 1;
    }
    OLED_CS_Set();
    OLED_DC_Set();
}
#endif
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0 + y, OLED_CMD);
    OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
    OLED_WR_Byte((x & 0x0f) | 0x01, OLED_CMD);
}

void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D, OLED_CMD);  
    OLED_WR_Byte(0X14, OLED_CMD); 
    OLED_WR_Byte(0XAF, OLED_CMD);  
}

void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D, OLED_CMD); 
    OLED_WR_Byte(0X10, OLED_CMD);  
    OLED_WR_Byte(0XAE, OLED_CMD);  
}

void OLED_Clear(void)
{
    u8 i, n;
    for (i = 0; i < 8; i++)
    {
        OLED_WR_Byte(0xb0 + i, OLED_CMD);    
        OLED_WR_Byte(0x00, OLED_CMD);      
        OLED_WR_Byte(0x10, OLED_CMD);     
        for (n = 0; n < 128; n++)
            OLED_WR_Byte(0, OLED_DATA);
    } 
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            OLED_GRAM[i][j] = 0;
        }
    }
    
}


void OLED_ShowChar(u8 x, u8 y, u8 chr)
{
    unsigned char c = 0, i = 0;
    c = chr - ' '; 
    if (x > Max_Column - 1)
    {
        x = 0;
        y = y + 2;
    }
    if (SIZE == 16)
    {
        OLED_Set_Pos(x, y);
        for (i = 0; i < 8; i++)
            OLED_WR_Byte(F8X16[c * 16 + i], OLED_DATA);
        OLED_Set_Pos(x, y + 1);
        for (i = 0; i < 8; i++)
            OLED_WR_Byte(F8X16[c * 16 + i + 8], OLED_DATA);
    }
    else
    {
        OLED_Set_Pos(x, y + 1);
        for (i = 0; i < 6; i++)
            OLED_WR_Byte(F6x8[c][i], OLED_DATA);

    }
}

u32 oled_pow(u8 m, u8 n)
{
    u32 result = 1;
    while (n--)
        result *= m;
    return result;
}

void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size2)
{
    u8 t, temp;
    u8 enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / oled_pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                OLED_ShowChar(x + (size2 / 2) * t, y, ' ');
                continue;
            }
            else
                enshow = 1;

        }
        OLED_ShowChar(x + (size2 / 2) * t, y, temp + '0');
    }
}

void OLED_ShowString(u8 x, u8 y, u8 *chr)
{
    unsigned char j = 0;
    while (chr[j] != '\0')
    {
        OLED_ShowChar(x, y, chr[j]);
        x += 8;
        if (x > 120)
        {
            x = 0;
            y += 2;
        }
        j++;
    }
}

void OLED_ShowCHinese(u8 x, u8 y, u8 no)
{
    u8 t, adder = 0;
    OLED_Set_Pos(x, y);
    for (t = 0; t < 16; t++)
    {
        OLED_WR_Byte(Hzk[2 * no][t], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1);
    for (t = 0; t < 16; t++)
    {
        OLED_WR_Byte(Hzk[2 * no + 1][t], OLED_DATA);
        adder += 1;
    }
}

void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1,
                  unsigned char y1, const unsigned char BMP[])
{
    unsigned int j = 0;
    unsigned char x, y;

    if (y1 % 8 == 0)
        y = y1 / 8;
    else
        y = y1 / 8 + 1;
    for (y = y0; y < y1; y++)
    {
        OLED_Set_Pos(x0, y);
        for (x = x0; x < x1; x++)
        {
            OLED_WR_Byte(BMP[j++], OLED_DATA);
        }
    }
}






void OLED_Init(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while (!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)))
        ;
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)))
        ;
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    while (!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)))
        ;


    MAP_SysCtlPeripheralEnable(GPIO_OLED_CS_PORT_SYSCTL);
    while (!(SysCtlPeripheralReady(GPIO_OLED_CS_PORT_SYSCTL)))
        ;

    MAP_SysCtlPeripheralEnable(GPIO_OLED_DC_PORT_SYSCTL);
    while (!(SysCtlPeripheralReady(GPIO_OLED_DC_PORT_SYSCTL)))
        ;

    MAP_SysCtlPeripheralEnable(GPIO_OLED_RES_PORT_SYSCTL);
    while (!(SysCtlPeripheralReady(GPIO_OLED_RES_PORT_SYSCTL)))
        ;

    MAP_SysCtlPeripheralEnable(GPIO_OLED_DAT_PORT_SYSCTL);
    while (!(SysCtlPeripheralReady(GPIO_OLED_DAT_PORT_SYSCTL)))
        ;

    MAP_SysCtlPeripheralEnable(GPIO_OLED_SCLK_PORT_SYSCTL);
    while (!(SysCtlPeripheralReady(GPIO_OLED_SCLK_PORT_SYSCTL)))
        ;

   


    MAP_GPIOPinTypeGPIOOutput(GPIO_OLED_CS_PORT_BASE, GPIO_OLED_CS_PIN);
    MAP_GPIOPinWrite(GPIO_OLED_CS_PORT_BASE, GPIO_OLED_CS_PIN, 0);

    MAP_GPIOPinTypeGPIOOutput(GPIO_OLED_DC_PORT_BASE, GPIO_OLED_DC_PIN);
    MAP_GPIOPinWrite(GPIO_OLED_DC_PORT_BASE, GPIO_OLED_DC_PIN, 0);

    MAP_GPIOPinTypeGPIOOutput(GPIO_OLED_RES_PORT_BASE, GPIO_OLED_RES_PIN);
    MAP_GPIOPinWrite(GPIO_OLED_RES_PORT_BASE, GPIO_OLED_RES_PIN, 0);

    MAP_GPIOPinTypeGPIOOutput(GPIO_OLED_DAT_PORT_BASE, GPIO_OLED_DAT_PIN);
    MAP_GPIOPinWrite(GPIO_OLED_DAT_PORT_BASE, GPIO_OLED_DAT_PIN, 0);

    MAP_GPIOPinTypeGPIOOutput(GPIO_OLED_SCLK_PORT_BASE, GPIO_OLED_SCLK_PIN);
    MAP_GPIOPinWrite(GPIO_OLED_SCLK_PORT_BASE, GPIO_OLED_SCLK_PIN, 0);

    MAP_GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, (GPIO_PIN_0 | GPIO_PIN_1));
    OLED_RST_Set();
    delay_ms(100);
    OLED_RST_Clr();
    delay_ms(100);
    OLED_RST_Set();
    /*
     OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
     OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
     OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
     OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
     OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
     OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
     OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
     OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
     OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
     OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
     OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
     OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset   Shift Mapping RAM Counter (0x00~0x3F)
     OLED_WR_Byte(0x00,OLED_CMD);//-not offset
     OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
     OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
     OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
     OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
     OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
     OLED_WR_Byte(0x12,OLED_CMD);
     OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
     OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
     OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
     OLED_WR_Byte(0x02,OLED_CMD);//
     OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
     OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
     OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
     OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7)
     OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
     */

    OLED_WR_Byte(0xAE, OLED_CMD); //--turn off oled panel
    OLED_WR_Byte(0x00, OLED_CMD); //---set low column address
    OLED_WR_Byte(0x10, OLED_CMD); //---set high column address
    OLED_WR_Byte(0x40, OLED_CMD); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_Byte(0x81, OLED_CMD); //--set contrast control register
    OLED_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
    OLED_WR_Byte(0xA1, OLED_CMD); //--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
    OLED_WR_Byte(0xC8, OLED_CMD); //Set COM/Row Scan Direction   0xc0���·��� 0xc8����
    OLED_WR_Byte(0xA6, OLED_CMD); //--set normal display
    OLED_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3f, OLED_CMD); //--1/64 duty
    OLED_WR_Byte(0xD3, OLED_CMD); //-set display offset   Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_Byte(0x00, OLED_CMD); //-not offset
    OLED_WR_Byte(0xd5, OLED_CMD); //--set display clock divide ratio/oscillator frequency
    OLED_WR_Byte(0x80, OLED_CMD); //--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_Byte(0xD9, OLED_CMD); //--set pre-charge period
    OLED_WR_Byte(0xF1, OLED_CMD); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_Byte(0xDA, OLED_CMD); //--set com pins hardware configuration
    OLED_WR_Byte(0x12, OLED_CMD);
    OLED_WR_Byte(0xDB, OLED_CMD); //--set vcomh
    OLED_WR_Byte(0x40, OLED_CMD); //Set VCOM Deselect Level
    OLED_WR_Byte(0x20, OLED_CMD); //-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WR_Byte(0x02, OLED_CMD); //
    OLED_WR_Byte(0x8D, OLED_CMD); //--set Charge Pump enable/disable
    OLED_WR_Byte(0x14, OLED_CMD); //--set(0x10) disable
    OLED_WR_Byte(0xA4, OLED_CMD); // Disable Entire Display On (0xa4/0xa5)
    OLED_WR_Byte(0xA6, OLED_CMD); // Disable Inverse Display On (0xa6/a7)
    OLED_WR_Byte(0xAF, OLED_CMD); //--turn on oled panel

    OLED_WR_Byte(0xAF, OLED_CMD); /*display ON*/
    OLED_Clear();
    OLED_Set_Pos(0, 0);
}

