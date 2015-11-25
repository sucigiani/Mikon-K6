#include "DrvGPIO.h"
#include "DrvSYS.h"
#include "LCD_Driver.h"
#include "DrvADC.h"
void Init();
int main(void)
{
	int nilai;
    Init();
    Initial_pannel();
    DrvGPIO_ClrBit(E_GPD,14);
    while(1)
    {
    	clr_all_pannal();
    	print_lcd(0,"LDR = ");
    	DrvADC_StartConvert();
    	nilai=DrvADC_GetConversionData(0);

    	Show_Word(0,7,nilai/1000+'0');
    	Show_Word(0,8,nilai%1000/100+'0');
    	Show_Word(0,9,nilai%100/10+'0');
    	Show_Word(0,10,nilai%10+'0');
    	DrvSYS_Delay(100000);
    }
}
