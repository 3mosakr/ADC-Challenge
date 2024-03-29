/*
 * main.c
 *
 *  Created on: Mar 18, 2024
 *      Author: sakr3
 */

//#include <avr/io.h>
#include <util/delay.h>
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/EXTI/EXTI_Interface.h"
#include "MCAL/GIE/GIE_Interface.h"
#include "MCAL/ADC/ADC_Interface.h"

#include "HAL/LCD/LCD_Interface.h"
//#include "HAL/KPD/KPD_Interface.h"
//#include "HAL/DCMOTOR/DCMOTOR_Interface.h"
//#include "HAL/STEPPER/STEPPER_Interface.h"
#include "HAL/LM35/LM35_Interface.h"


//#define F_CPU 8000000UL

void APP_INIT(void);
/*******************************************************************/
void mode_0(void);
void mode_1(void);
void mode_2(void);
void mode_3(void);

void EXTI0_mode1_ISR(void);
void EXTI0_mode2_ISR(void);
void EXTI0_mode3_ISR(void);

void EXTI1_mode2_ISR(void);
void EXTI1_mode3_ISR(void);
/*******************************************************************/

void lcd_welcome_msg(void);


int main(void) {

	u8 Local_u8Mode_S = 0;

	APP_INIT();

	/*Print welcome message*/
	lcd_welcome_msg();

	/************************/
	LCD_voidSendString((u8*)"Select Mode...");

	while(1)
	{
		/* range
		 * 2
		 * 20
		 * 167
		 * 200
		 * */
		Local_u8Mode_S = ADC_u16GetConversionReading(CHANNEL0);

		if(Local_u8Mode_S == 2){
			mode_0();
		}
		else if(Local_u8Mode_S == 20){
			mode_1();
		}
		else if(Local_u8Mode_S == 167){
			mode_2();
		}
		else if(Local_u8Mode_S == 200){
			mode_3();
		}
		else
		{
			Local_u8Mode_S = 0;
			/* NOTHING */
		}

//		LCD_voidClearScreen();
//		LCD_voidSendNumber(Local_u8Mode_S);

	}
	return 0;
}

void APP_INIT(){
	/* configure the Mode sector pins as input */
	DIO_u8SetPinDirection(DIO_PORTA, DIO_PIN0, DIO_PIN_INPUT);

	/* configure LED0, LED1 pins as output */
	DIO_u8SetPinDirection(DIO_PORTA, DIO_PIN6, DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PORTA, DIO_PIN7, DIO_PIN_OUTPUT);

	/* configure External interrupt (EXTI1, EXTI2) pins */
	DIO_u8SetPinDirection(DIO_PORTD, DIO_PIN3, DIO_PIN_INPUT);
	DIO_u8SetPinDirection(DIO_PORTB, DIO_PIN2, DIO_PIN_INPUT);

	/* initialize using modules (ADC, LCD) */
	ADC_Init();
	LCD_voidInit();

}
/*******************************************************************/
/* Modes */

void mode_0(){
	/*  System has no interrupt (Maskable interrupt).
	 *  LCD display Mode0 in first line, No Maskable in second line. */

	/* enable global interrupt */
	GIE_voidDisable();

	LCD_voidClearScreen();
	LCD_voidSendString((u8*)"Mode 0");
	LCD_voidSetPosition(LCD_ROW1, LCD_COLUMN1);
	LCD_voidSendString((u8*)" No Maskable");
	//	_delay_ms(1500);
}

void mode_1(){
	/*  System has interrupt (Maskable interrupt).
	 *  EXTI0 is enabled.
	 *  LCD display Mode1 in first line, E: EXTI0 in second line.
	 *  EXTI0 toggle LED0.
	 *  */

	/* enable global interrupt */
	GIE_voidEnable();
	/* enable external interrupt */
	EXTI_voidInit();
	/* set ISR for EXT_INT0 */
	EXTI_u8Int0SetCallBack(EXTI0_mode1_ISR);

	LCD_voidClearScreen();
	LCD_voidSendString((u8*)"Mode 1");
	LCD_voidSetPosition(LCD_ROW1, LCD_COLUMN1);
	LCD_voidSendString((u8*)" EXTI 0");

}

void mode_2(){
	/* System has interrupt (Maskable interrupt).
	 *  EXTI0,EXTI1 is enabled.
	 *  LCD display Mode2 in first line, E: EXTI0,EXTI1 in second line.
	 *  EXTI0 set LED0.
	 *  EXTI1 clear LED0. */

	/* enable global interrupt */
	GIE_voidEnable();
	/* enable external interrupt */
	EXTI_voidInit();
	/* set ISR for EXT_INT0, EXT_INT1 */
	EXTI_u8Int0SetCallBack(EXTI0_mode2_ISR);
	EXTI_u8Int1SetCallBack(EXTI1_mode2_ISR);

	LCD_voidClearScreen();
	LCD_voidSendString((u8*)"Mode 2");
	LCD_voidSetPosition(LCD_ROW1, LCD_COLUMN1);
	LCD_voidSendString((u8*)" EXTI 0, EXTI 1");
}

void mode_3(){
	/* System has interrupt (Maskable interrupt).
	 *  EXTI0,EXTI1 is enabled.
	 *  LCD display Mode3 in first line, E: EXTI0,EXTI1 in second line.
	 *  EXTI0 toggle LED0.
	 *  EXTI1 toggle LED1.
	 *  */

	/* enable global interrupt */
	GIE_voidEnable();
	/* enable external interrupt */
	EXTI_voidInit();
	/* set ISR for EXT_INT0, EXT_INT1 */
	EXTI_u8Int0SetCallBack(EXTI0_mode3_ISR);
	EXTI_u8Int1SetCallBack(EXTI1_mode3_ISR);

	LCD_voidClearScreen();
	LCD_voidSendString((u8*)"Mode 3");
	LCD_voidSetPosition(LCD_ROW1, LCD_COLUMN1);
	LCD_voidSendString((u8*)" EXTI 0, EXTI 1");

}

/******************************************************************/
/* Modes ISR */

/* Mode 1 ISRs */
void EXTI0_mode1_ISR(){
	/* EXTI0 toggle LED0. */
	DIO_u8SetPinToggle(DIO_PORTA, DIO_PIN6);
}

/* Mode 2 ISRs */
void EXTI0_mode2_ISR(){
	/* EXTI0 set LED0. */
	DIO_u8SetPinValue(DIO_PORTA, DIO_PIN6,DIO_PIN_HIGH);
}

void EXTI1_mode2_ISR(){
	/* EXTI0 clear LED0. */
	DIO_u8SetPinValue(DIO_PORTA, DIO_PIN6,DIO_PIN_LOW);
}

/* Mode 3 ISRs */
void EXTI0_mode3_ISR(){
	/* EXTI0 toggle LED0. */
	DIO_u8SetPinToggle(DIO_PORTA, DIO_PIN6);
}

void EXTI1_mode3_ISR(){
	/* EXTI0 toggle LED1. */
	DIO_u8SetPinToggle(DIO_PORTA, DIO_PIN7);

}

/******************************************************************/
void lcd_welcome_msg(){
	LCD_voidClearScreen();
	LCD_voidSendString((u8*)"Welcome");
	LCD_voidSetPosition(LCD_ROW1, LCD_COLUMN1);
	LCD_voidSendString((u8*)"Challenge ADC.");
	_delay_ms(1000);
	LCD_voidClearScreen();
}

