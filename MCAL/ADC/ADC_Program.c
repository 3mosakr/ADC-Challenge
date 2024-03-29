/*
 * ADC_Program.c
 *
 *  Created on: Mar 26, 2024
 *      Author: sakr3
 */

/****************************LIB***************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_Types.h"

/****************************MCAL**************************/
#include "ADC_Config.h"
#include "ADC_Interface.h"
#include "ADC_Private.h"


/*Inclusions*/
//#include "avr/delay.h"


/***************Functions Definitions********************/
void ADC_Init(){

	/* SELECT VREF */
#if ADC_REF_SELECTION == AREFF
	CLR_BIT(ADMUX, REFS0);
	CLR_BIT(ADMUX, REFS1);

#elif ADC_REF_SELECTION == AVCC
	SET_BIT(ADMUX, REFS0);
	CLR_BIT(ADMUX, REFS1);

#elif ADC_REF_SELECTION == VOLT_2_56
	SET_BIT(ADMUX, REFS0);
	SET_BIT(ADMUX, REFS1);
#else
#error "ADC_REF_SELECTION error configuration parameter"
#endif

	/* challenge make configuration for adjustment  */
	/* left Adjustment bit (ADLAR) , 1-> left adj, 0-> right adj  */
	CLR_BIT(ADMUX, ADLAR);

	/* clear auto trigger bit (ADATE), so adc conversion will start when you call ADC_u16GetConversionReading() */
	CLR_BIT(ADMUX, ADATE);

	/* sync or async Disable adc interrupt */
	CLR_BIT(ADCSRA, ADIE);

	/* set pre-scaller to /64 */
	CLR_BIT(ADCSRA, ADPS0);
	SET_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS2);

	/* Enable ADC */
	SET_BIT(ADCSRA, ADEN);


}

/* select channel */
u16 ADC_u16GetConversionReading(u8 copy_u8Channel){
	u16 ADC_data = 0;
	/*validate channel in range [CHANNEL0, CHANNEL7]*/
	if((copy_u8Channel >= CHANNEL0) && (copy_u8Channel <= CHANNEL7)){
		/* select channel */
		if(copy_u8Channel == CHANNEL0)
		{
			/* Select input channel to pin PA0 */
			CLR_BIT(ADMUX, MUX0);
			CLR_BIT(ADMUX, MUX1);
			CLR_BIT(ADMUX, MUX2);
			CLR_BIT(ADMUX, MUX3);
			CLR_BIT(ADMUX, MUX4);
		}
		else if(copy_u8Channel == CHANNEL1)
		{
			/* Select input channel to pin PA1 */
			SET_BIT(ADMUX, MUX0);
			CLR_BIT(ADMUX, MUX1);
			CLR_BIT(ADMUX, MUX2);
			CLR_BIT(ADMUX, MUX3);
			CLR_BIT(ADMUX, MUX4);
		}
		else if(copy_u8Channel == CHANNEL2)
		{
			/* Select input channel to pin PA2 */
			CLR_BIT(ADMUX, MUX0);
			SET_BIT(ADMUX, MUX1);
			CLR_BIT(ADMUX, MUX2);
			CLR_BIT(ADMUX, MUX3);
			CLR_BIT(ADMUX, MUX4);
		}
		else if(copy_u8Channel == CHANNEL3)
		{
			/* Select input channel to pin PA3 */
			SET_BIT(ADMUX, MUX0);
			SET_BIT(ADMUX, MUX1);
			CLR_BIT(ADMUX, MUX2);
			CLR_BIT(ADMUX, MUX3);
			CLR_BIT(ADMUX, MUX4);
		}
		else if(copy_u8Channel == CHANNEL4)
		{
			/* Select input channel to pin PA4 */
			CLR_BIT(ADMUX, MUX0);
			CLR_BIT(ADMUX, MUX1);
			SET_BIT(ADMUX, MUX2);
			CLR_BIT(ADMUX, MUX3);
			CLR_BIT(ADMUX, MUX4);
		}
		else if(copy_u8Channel == CHANNEL5)
		{
			/* Select input channel to pin PA5 */
			SET_BIT(ADMUX, MUX0);
			CLR_BIT(ADMUX, MUX1);
			SET_BIT(ADMUX, MUX2);
			CLR_BIT(ADMUX, MUX3);
			CLR_BIT(ADMUX, MUX4);
		}
		else if(copy_u8Channel == CHANNEL6)
		{
			/* Select input channel to pin PA6 */
			CLR_BIT(ADMUX, MUX0);
			SET_BIT(ADMUX, MUX1);
			SET_BIT(ADMUX, MUX2);
			CLR_BIT(ADMUX, MUX3);
			CLR_BIT(ADMUX, MUX4);
		}
		else if(copy_u8Channel == CHANNEL7)
		{
			/* Select input channel to pin PA7 */
			SET_BIT(ADMUX, MUX0);
			SET_BIT(ADMUX, MUX1);
			SET_BIT(ADMUX, MUX2);
			CLR_BIT(ADMUX, MUX3);
			CLR_BIT(ADMUX, MUX4);
		}
		else { /* NOTHING */ }
		/* Start conversion */
		SET_BIT(ADCSRA, ADSC);

		/* wait until conversion complete */
		while(GET_BIT(ADCSRA, ADSC) == 1);

		/* After  conversion is finished read data (result) from ADCL then ADCH */
		ADC_data = ADCL;
		ADC_data |= (ADCH<<8);

	}else{
		/* invalid channel */
		ADC_data = 0;
	}

	return ADC_data;
}
