/*
 * ADC_Interface.h
 *
 *  Created on: Mar 26, 2024
 *      Author: sakr3
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

/****************** GENERAL MACROS ******************/
/* ADC working channels */
#define CHANNEL0 		0
#define CHANNEL1 		1
#define CHANNEL2 		2
#define CHANNEL3 		3
#define CHANNEL4 		4
#define CHANNEL5 		5
#define CHANNEL6 		6
#define CHANNEL7 		7

/***************Functions Prototypes********************/
void ADC_Init(void);

/* select channel */
u16 ADC_u16GetConversionReading(u8 copy_u8Channel);

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
