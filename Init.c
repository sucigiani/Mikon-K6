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

void Init()
{
    GPIOD_Init();
    SPI3_Init();
    ADC_Init();
}
