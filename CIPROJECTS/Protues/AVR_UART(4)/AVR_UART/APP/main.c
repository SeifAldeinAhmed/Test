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
u8 Global_u8Signal[100];
void main (void)
{
	DIO_voidSetPortDirection(DIO_PORTA,DIO_INPUT);
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
	while (1)
	{
		Global_u8Signal[Local_u8Counter]=PINA_REG;
		LCD_void4bitDisplayNumber(Global_u8Signal[Local_u8Counter]);
		LCD_voidSend_4bitData(44); //  ' , '
		{
			UART_TransmitData(Start_Bit);
			UART_voidSendNumber((u32)Global_u8Signal[Local_u8Counter]);
			UART_TransmitData(Comma);
			UART_voidSendNumber((u32)Local_u8Counter);
			UART_TransmitData(End_Bit);
		}

		Local_u8Counter++;
		_delay_ms(1);
	}

}
