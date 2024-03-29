/*
 * ADC_Private.h
 *
 *  Created on: Mar 26, 2024
 *      Author: sakr3
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

/****************** ADMUX - ADC Multiplexer Selection Register ******************/
#define ADMUX 				(*((volatile u8*) 0x27))
/* MUX4:0: Analog Channel and Gain Selection Bits */
#define MUX0 				0
#define MUX1 				1
#define MUX2 				2
#define MUX3 				3
#define MUX4 				4
/* ADLAR: ADC Left Adjust Result */
#define ADLAR 				5
/* REFS1:0: Reference Selection Bits */
#define REFS0 				6
#define REFS1 				7

/****************** ADCSRA - ADC Control and Status Register A ******************/
#define ADCSRA 				(*((volatile u8*) 0x26))
/* ADPS2:0: ADC Prescaler Select Bits */
#define ADPS0 		0
#define ADPS1 		1
#define ADPS2 		2
/* ADIE: ADC Interrupt Enable */
#define ADIE 		3
/* ADIF: ADC Interrupt Flag */
#define ADIF 		4
/* ADATE: ADC Auto Trigger Enable */
#define ADATE 		5
/* ADSC: ADC Start Conversion */
#define ADSC 		6
/* ADEN: ADC Enable */
#define ADEN 		7

/****************** The ADC Data Register – ADCL and ADCH ******************/
#define ADCH 			(*((volatile u8*) 0x25))
#define ADCL 			(*((volatile u8*) 0x24))

/****************** SFIOR - Special FunctionIO Register ******************/
#define SFIOR 				(*((volatile u8*) 0x50))
/* ADTS2:0: ADC Auto Trigger Source */
#define ADTS0 		5
#define ADTS1			6
#define ADTS2			7

/* adc selection */
#define AREFF 				1
#define AVCC				2
#define VOLT_2_56			3

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
