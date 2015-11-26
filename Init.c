/*************************************************************
 * @file      : Init.c
 * @brief     : Peripheral Init Functions
 * @version   : 1.2.4
 * @date      : 11/25/2015  12:41 
 * @author    : Created by CoSmart 1.2.4
**************************************************************/
#include "DrvGPIO.h"
#include "DrvSPI.h"
#include "DrvADC.h"
#include "DrvPWM.h"
#include "DrvSYS.h"
#include "DrvUART.h"

/*************************************************************
 * GPIOA Initialization
**************************************************************/
void GPIOA_Init()
{
   //
   // Set PA0 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 0, E_IO_QUASI);
   //
   // Set PA1 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 1, E_IO_QUASI);
   //
   // Set PA2 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 2, E_IO_QUASI);
   //
   // Set PA3 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 3, E_IO_QUASI);
   //
   // Set PA4 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 4, E_IO_QUASI);
   //
   // Set PA5 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 5, E_IO_QUASI);

}

/*************************************************************
* PWM Initialization Code Template
**************************************************************/
void PWM_Init()
{
    S_DRVPWM_TIME_DATA_T sPt_0;
    uint8_t u8Timer_0;
    S_DRVPWM_TIME_DATA_T sPt_1;
    uint8_t u8Timer_1;
    /* Enable PWM clock */
    DrvPWM_Open();

    /* Set PWM0 Pin */
    outpw(&SYS->GPAMFP, inpw(&SYS->GPAMFP) | (0x1<<(12)));

    /* Selcect pwm0 clock source */
    DrvPWM_SelectClockSource(DRVPWM_TIMER0, DRVPWM_EXT_12M);

    /* PWM Timer property */
    sPt_0.u8Mode = DRVPWM_ONE_SHOT_MODE;
    sPt_0.u32Frequency = 0;
    sPt_0.u8PreScale = 0;
    sPt_0.u8ClockSelector = DRVPWM_CLOCK_DIV_1;
    sPt_0.u8HighPulseRatio = 0;
    sPt_0.i32Inverter = FALSE;
    sPt_0.u32Duty = 0;
    u8Timer_0 = DRVPWM_TIMER0;

    /* PWM Timer0 Configuration */
    DrvPWM_SetTimerClk(DRVPWM_TIMER0, &sPt_0);

    /* Enable in/out for PWM Timer0 */
    DrvPWM_SetTimerIO(DRVPWM_TIMER0, 1);

    /* Enable the PWM Timer 0 */
    DrvPWM_Enable(DRVPWM_TIMER0, 1);

    /* Set PWM1 Pin */
    outpw(&SYS->GPAMFP, inpw(&SYS->GPAMFP) | (0x1<<13));

    /* Enable PWM clock */
    DrvPWM_SelectClockSource(DRVPWM_TIMER1, DRVPWM_EXT_12M);

    /* PWM1 Timer property */
    sPt_1.u8Mode = DRVPWM_ONE_SHOT_MODE;
    sPt_1.u32Frequency = 0;
    sPt_1.u8PreScale = 0;
    sPt_1.u8ClockSelector = DRVPWM_CLOCK_DIV_1;
    sPt_1.u8HighPulseRatio = 0;
    sPt_1.i32Inverter = FALSE;
    sPt_1.u32Duty = 0;
    u8Timer_1 = DRVPWM_TIMER1;

    /* Set PWM Timer1 Configuration */
    DrvPWM_SetTimerClk(DRVPWM_TIMER1, &sPt_1);

    /* Enable in/out for PWM Timer1 */
    DrvPWM_SetTimerIO(DRVPWM_TIMER1, 1);

    /* Enable the PWM Timer 1 */
    DrvPWM_Enable(DRVPWM_TIMER1, 1);
}

/*************************************************************
 * GPIOD Initialization
**************************************************************/
void GPIOD_Init()
{
   //
   // Set PD14 Pin Mode
   //
   DrvGPIO_Open(E_GPD, 14, E_IO_OUTPUT);

}

/*************************************************************
 * SPI Initialization Code Template
**************************************************************/
void SPI3_Init()
{
    E_DRVSPI_PORT eSpiPort;

    /* Get which port to be used */
    eSpiPort = eDRVSPI_PORT3;
    DrvGPIO_InitFunction(E_FUNC_SPI3);

    /* Slave mode; clock parity, transmit and receive edge(eType) */
    DrvSPI_Open(eSpiPort, eDRVSPI_SLAVE, eDRVSPI_TYPE0, 32);

    /* Slave Select Trigger Mode */
    DrvSPI_SetTriggerMode(eSpiPort, eDRVSPI_EDGE_TRIGGER);

    /* Slave Selcet Active Level */
    DrvSPI_SetSlaveSelectActiveLevel(eSpiPort, eDRVSPI_ACTIVE_LOW_FALLING);

    /* LSB or MSB */
    DrvSPI_SetEndian(eSpiPort, eDRVSPI_MSB_FIRST);
}

/*************************************************************
 * ADC Initialization
**************************************************************/
void ADC_Init()
{
    //
    // Configure the relative pins for ADC function
    //
    DrvGPIO_InitFunction(E_FUNC_ADC0);
    //
    // Config clock, input mode, operate mode and convert channel for ADC
    //
    DrvADC_Open(ADC_SINGLE_END,ADC_SINGLE_OP,0x01,INTERNAL_RC22MHZ,2);
}

/*************************************************************
 * UART0 Initialization
**************************************************************/
void UART0_Init()
{
    STR_UART_T UartParam;
    E_DRVGPIO_FUNC FuncNum = E_FUNC_UART0;
    E_UART_PORT UartNum = UART_PORT0;

    /* Uart Pin Config */
    DrvGPIO_InitFunction(E_FUNC_UART0);

    /* Uart Config */
    UartParam.u32BaudRate = 9600;
    UartParam.u8cDataBits = DRVUART_DATABITS_8;
    UartParam.u8cStopBits = DRVUART_STOPBITS_1;
    UartParam.u8cParity = DRVUART_PARITY_NONE;
    UartParam.u8cRxTriggerLevel = DRVUART_FIFO_1BYTES;
    UartParam.u8TimeOut = 0;

    /* Uart Open */
    DrvUART_Open(UartNum, &UartParam);
}

/*************************************************************
 * GPIOC Initialization
**************************************************************/
void GPIOC_Init()
{
   //
   // Set PC0 Pin Mode
   //
   DrvGPIO_Open(E_GPC, 0, E_IO_OUTPUT);

}

void Init()
{
	GPIOC_Init();
    GPIOD_Init();
    SPI3_Init();
    ADC_Init();
    GPIOA_Init();
    PWM_Init();
    UART0_Init();
}
