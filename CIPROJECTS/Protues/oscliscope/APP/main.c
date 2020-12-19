/****************************************************/
/*   AUTHOR      : Abdelrahman Hossam               */
/*   Description : Smart Home APP   		        */
/*   DATE        : 29 FEB 2020                      */
/*   VERSION     : V01                              */
/****************************************************/

/***************************************************/
/*              Library Directives                 */
/***************************************************/
#include "..\LIB\STD_TYPES.h"
#include "..\LIB\BIT_MATH.h"
#include "../LIB/Registers.h"
//#include <avr/io.h>
#include <util/delay.h>
/***************************************************/
/*                 DIO Directives                  */
/***************************************************/
#include "../MCAL/DIO/DIO_INT.h"

/***************************************************/
/*           		ADC Directives                 */
/***************************************************/

#include "../MCAL/ADC/ADC_INT.h"
#include "../MCAL/ADC/ADC_PRIV.h"
//#include "../MCAL/ADC/ADC_CONF.h"

#include "../MCAL/UART/UART_INT.h"
#include "../MCAL/UART/UART_CONF.h"

/***************************************************/
/*           EXT Interrupt Directives              */
/***************************************************/
#include "../MCAL/Interrupt/ExtInterrupt_INT.h"
#include "../MCAL/Interrupt/ExtInterrupt_PRIV.h"

/***************************************************/
/*           	  Timer0 Directives                */
/***************************************************/
#include "../MCAL/TIMER0/TIMER_INT.h"

/***************************************************/
/*           	   LCD Directives                  */
/***************************************************/
#include "../HAL/LCD/LCD_INT.h"
#include "../HAL/LCD/LCD_PRIV.h"

#define Start_Bit             64//@
#define Comma                 44//,
#define End_Bit               59//;

/* Global array for the signal values */
u32 Global_u16Signal[100];
u32 Global_u8timer[100];
void main (void)
{
	for (u8 i=0; i<100;i++)
	{
		 Global_u16Signal[i]=0;
		 Global_u8timer[i]=0;
	}
	f32 Local_f32Adc_value1 = 0;
	f32 Local_f32Adc_value2 = 0;
	f32 Local_f32Adc_volt1 = 0;
	f32 Local_f32Adc_volt2 = 0;
	f32 Local_f32Temp = 0;
	/* Initialize ADC */
	ADC_voidInitTEMP();
	/* Initialize the USART using the Pre-Configuration */
	UART_Init();
	/*
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_INPUT);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN1,DIO_INPUT);
	*/
	/* Initialize the LCD 16*2 Uing the 4 Bit Mode  */
	LCD_4bitIntialization();
	_delay_ms(200);
	/* Counter for samples number */
	u8 Local_u8Counter;
	Local_u8Counter=0;

	u8 Local_u8LCDCounter;
	   Local_u8LCDCounter=0;
	   Timer0_voidInit();
	while (1)
	{
		/* Read The ADC Values */
		Local_f32Adc_value1=ADC_u16GetRawData(ADCCH0);
		//Local_f32Adc_value2=ADC_u16GetRawData(ADCCH1);
		Global_u16Signal[Local_u8Counter]=Local_f32Adc_value1; //- Local_f32Adc_value2;

		/* Get the Local_f32Temperature value */
	//	Local_f32Temp = ((Global_u16Signal[Local_u8Counter]*500)/1023.0);
		Global_u8timer[Local_u8Counter]=TCNT0;
		LCD_void4bitDisplayNumber((Global_u16Signal[Local_u8Counter]));
		LCD_voidSend_4bitData(44); //  ' , '
		/* Frame Send Using UART */
		{
			UART_TransmitData(Start_Bit);
			UART_voidSendNumber( (Global_u16Signal[Local_u8Counter]));
			UART_TransmitData(Comma);
			UART_voidSendNumber((u32)Local_u8Counter);
			UART_TransmitData(Comma);
			UART_voidSendNumber(Global_u8timer[Local_u8Counter]);
//			UART_TransmitData(Global_u8timer[Local_u8Counter]);
			UART_TransmitData(End_Bit);

		}

		/******************************************************************************************************/
		/* Print on the LCD the Transmitted Number through the USART */
	/*	LCD_void4bitDisplayNumber(Local_f32Temp);
		Local_u8LCDCounter++;
		LCD_voidSend_4bitData(44); //  ' , '
		if (Local_u8LCDCounter==5)
		{
			LCD_voidSend_4bitCommand(0x01);	// Clear display screen
			Local_u8LCDCounter=0;
		}*/
		/* Increment Samples Counter */
		Local_u8Counter++;
		if (Local_u8Counter==100)
			Local_u8Counter=0;
		_delay_ms(1);
		/******************************************************************************************************/
		TCNT0=0;
	}

}
