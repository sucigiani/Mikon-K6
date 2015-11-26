#include "DrvGPIO.h"
#include "DrvSYS.h"
#include "LCD_Driver.h"
#include "DrvADC.h"
#include "PWM.h"
#include "DrvUART.h"

//#define  SERVO_CYCTIME        2000 // 20ms = 50Hz
#define  SERVO_HITIME_MIN       50 // minimum Hi width = 0.5ms
#define  SERVO_HITIME_MAX      250 // maximum Hi width = 2.5ms
#define  STEPTIME               10 // incremental time = 1.0ms
int state;
state = 1;
void Init();


	//---------------------------

void read_ldr(int x, char y) {

	int nilai;
	char tul;
	nilai = x;
	tul = y;

	clr_all_pannal();
	print_lcd(0,"LDR = ");

	Show_Word(0,7,nilai/1000+'0');
	Show_Word(0,8,nilai%1000/100+'0');
	Show_Word(0,9,nilai%100/10+'0');
	Show_Word(0,10,nilai%10+'0');
	Show_Word(1,1,tul);
	DrvSYS_Delay(100000);
}

//inisialisasi variabel PWM
    	//uint8_t i;
        uint8_t hitime;
    	//char TEXT0[16],TEXT1[16],TEXT2[16],TEXT3[16];
    	uint32_t Clock;
    	uint32_t Frequency;
    	uint8_t  PreScaler;
    	uint8_t  ClockDivider;
    	uint8_t  DutyCycle;
    	uint16_t CNR, CMR;
    	//-------------------------
    	void servo_buka(){
    			//Assignment variabel PWM
    			UNLOCKREG();
    			SYSCLK->PWRCON.XTL12M_EN=1;
    			DrvSYS_Delay(5000);					// Waiting for 12M Xtal stalble
    			SYSCLK->CLKSEL0.HCLK_S=0;
    			LOCKREG();

    			//init_LCD();
    			//clear_LCD();

    			// PWM_No = PWM channel number
    			// PWM_CLKSRC_SEL   = 0: 12M, 1:32K, 2:HCLK, 3:22M
    			// PWM_PreScaler    : PWM clock is divided by (PreScaler + 1)
    			// PWM_ClockDivider = 0: 1/2, 1: 1/4, 2: 1/8, 3: 1/16, 4: 1
    			init_PWM(0, 0, 130, 4); // initialize PWM0(GPA12) to output 1MHz square wave
    			Clock = 12000000;
    			PreScaler = 130;
    			ClockDivider = 1;
    			Frequency = 50;

    			//hitime = SERVO_HITIME_MIN;
    			//--------------------------------------

    			//----------Kodingan inti microservo
    			//hitime=hitime + (SERVO_HITIME_MAX - SERVO_HITIME_MIN)/10;
    			hitime = 125;
    			if (hitime>SERVO_HITIME_MAX) hitime = SERVO_HITIME_MIN;
    			//PWM_FreqOut = PWM_Clock / (PWM_PreScaler + 1) / PWM_ClockDivider / (PWM_CNR + 1)
    			CNR = Clock / Frequency / (PreScaler + 1) / ClockDivider - 1;
    			// Duty Cycle = (CMR0+1) / (CNR0+1)
    			CMR = hitime  - 1;
    			//CMR = 20;
    			PWM_Out(0, CNR, CMR);
    		}
    	void servo_tutup(){
    			//Assignment variabel PWM
    			UNLOCKREG();
    			SYSCLK->PWRCON.XTL12M_EN=1;
    			DrvSYS_Delay(5000);					// Waiting for 12M Xtal stalble
    			SYSCLK->CLKSEL0.HCLK_S=0;
    			LOCKREG();

    			//init_LCD();
    			//clear_LCD();

    			// PWM_No = PWM channel number
    			// PWM_CLKSRC_SEL   = 0: 12M, 1:32K, 2:HCLK, 3:22M
    			// PWM_PreScaler    : PWM clock is divided by (PreScaler + 1)
    			// PWM_ClockDivider = 0: 1/2, 1: 1/4, 2: 1/8, 3: 1/16, 4: 1
    			init_PWM(0, 0, 60, 4); // initialize PWM0(GPA12) to output 1MHz square wave
    			Clock = 12000000;
    			PreScaler = 60;
    			ClockDivider = 1;
    			Frequency = 50;

    		//	hitime = SERVO_HITIME_MIN;

    			//----------Kodingan inti microservo
    			//hitime=hitime + (SERVO_HITIME_MAX - SERVO_HITIME_MIN)/10;
    			hitime = 125;
    			if (hitime>SERVO_HITIME_MAX) hitime = SERVO_HITIME_MIN;
    			//PWM_FreqOut = PWM_Clock / (PWM_PreScaler + 1) / PWM_ClockDivider / (PWM_CNR + 1)
    			CNR = Clock / Frequency / (PreScaler + 1) / ClockDivider - 1;
    			// Duty Cycle = (CMR0+1) / (CNR0+1)
    			CMR = hitime  - 1;
    			//CMR = 20;
    			PWM_Out(0, CNR, CMR);
    		}

int main(void)
{
    Init();
    int adc;
	char kirim;
    Initial_pannel();
    DrvGPIO_ClrBit(E_GPD,14);
    while(1) {
    	kirim = DrvUART_Read(0,0,0);
    	DrvADC_StartConvert();
    	adc=DrvADC_GetConversionData(0);
    	read_ldr(adc,kirim);
		DrvSYS_Delay(3000000);
    	if ( (adc>3000) || (adc<800) && (state == 1) ) {
    		state = 0;
    		servo_tutup();
    	} else if ( (adc>=800) && (adc<=3000) && (state == 0) ) {
    		state = 1;
    		servo_buka();
    	}
    	DrvSYS_Delay(10000);
    }
}
