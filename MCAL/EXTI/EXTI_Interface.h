/*
 * EXTI_Interface.h
 *
 *  Created on: Mar 24, 2024
 *      Author: sakr3
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

/** GENERAL MACROS */
#define FALLING_EDGE 	1
#define RISSING_EDGE 	2
#define LOW_LEVEL 		3
#define ON_CHANGE 		4


/** FUNCTIONS PROTOTYPES */

void EXTI_voidInit(void);

//change sense control while runtime
u8 EXTI_u8SetInt0SenseControl(u8 copy_u8SenseControl);
u8 EXTI_u8SetInt1SenseControl(u8 copy_u8SenseControl);
u8 EXTI_u8SetInt2SenseControl(u8 copy_u8SenseControl);

u8 EXTI_u8Int0SetCallBack(void(*copy_ptrToFunction)(void));
u8 EXTI_u8Int1SetCallBack(void(*copy_ptrToFunction)(void));
u8 EXTI_u8Int2SetCallBack(void(*copy_ptrToFunction)(void));

#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
