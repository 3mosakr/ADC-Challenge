/*
 * EXTI_Program.c
 *
 *  Created on: Mar 24, 2024
 *      Author: sakr3
 */


/********************************* LIB *********************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "EXTI_Config.h"
#include "EXTI_Interface.h"
#include "EXTI_Private.h"

/*GLOBAL POINTER TO FUNCTION */
static void (*Global_ptrToFuncEXTI0)(void) = NULL;
static void (*Global_ptrToFuncEXTI1)(void) = NULL;
static void (*Global_ptrToFuncEXTI2)(void) = NULL;

/*ISR*/
void __vector_1 (void) __attribute__((signal));
void __vector_2 (void) __attribute__((signal));
void __vector_3 (void) __attribute__((signal));

/** FUNCTIONS PROTOTYPES */

void EXTI_voidInit(void){
//		EXTI_INT0
#if EXTI_INT0_ENABLE==ENABLE
	SET_BIT(GICR, GICR_INT0);
	// Sense control
	#if EXTI_INT0_SENSE_CONTROL==FALLING_EDGE
		CLR_BIT(MCUCR, MCUCR_ISC00);
		SET_BIT(MCUCR, MCUCR_ISC01);
	#elif EXTI_INT0_SENSE_CONTROL==RISSING_EDGE
		SET_BIT(MCUCR, MCUCR_ISC00);
		SET_BIT(MCUCR, MCUCR_ISC01);
	#elif EXTI_INT0_SENSE_CONTROL==LOW_LEVEL
		CLR_BIT(MCUCR, MCUCR_ISC00);
		CLR_BIT(MCUCR, MCUCR_ISC01);
	#elif EXTI_INT0_SENSE_CONTROL==ON_CHANGE
		SET_BIT(MCUCR, MCUCR_ISC00);
		CLR_BIT(MCUCR, MCUCR_ISC01);
	#else
	#error "EXTI_INT0_ENABLE Error configuration parameter!"
	#endif

#elif EXTI_INT0_ENABLE==DISABLE
		CLR_BIT(GICR, GICR_INT0);
#else
#error "EXTI_INT0_ENABLE Error configuration parameter!"
#endif

//		EXTI_INT1
#if EXTI_INT1_ENABLE==ENABLE
	SET_BIT(GICR, GICR_INT1);
	// Sense control
	#if EXTI_INT1_SENSE_CONTROL==FALLING_EDGE
		CLR_BIT(MCUCR, MCUCR_ISC10);
		SET_BIT(MCUCR, MCUCR_ISC11);
	#elif EXTI_INT1_SENSE_CONTROL==RISSING_EDGE
		SET_BIT(MCUCR, MCUCR_ISC10);
		SET_BIT(MCUCR, MCUCR_ISC11);
	#elif EXTI_INT1_SENSE_CONTROL==LOW_LEVEL
		CLR_BIT(MCUCR, MCUCR_ISC10);
		CLR_BIT(MCUCR, MCUCR_ISC11);
	#elif EXTI_INT1_SENSE_CONTROL==ON_CHANGE
		SET_BIT(MCUCR, MCUCR_ISC10);
		CLR_BIT(MCUCR, MCUCR_ISC11);
	#else
	#error "EXTI_INT1_ENABLE Error configuration parameter!"
	#endif

#elif EXTI_INT1_ENABLE==DISABLE
		CLR_BIT(GICR, GICR_INT1);
#else
#error "EXTI_INT1_ENABLE Error configuration parameter!"
#endif

//
#if EXTI_INT2_ENABLE==ENABLE
	SET_BIT(GICR, GICR_INT2);
	// Sense control
	#if EXTI_INT2_SENSE_CONTROL==FALLING_EDGE
	CLR_BIT(MCUCSR, MCUCSR_ISC2);
	#elif EXTI_INT2_SENSE_CONTROL==RISSING_EDGE
	SET_BIT(MCUCSR, MCUCSR_ISC2);
	#else
	#error "EXTI_INT2_ENABLE Error configuration parameter!"
	#endif

#elif EXTI_INT2_ENABLE==DISABLE
		CLR_BIT(GICR, GICR_INT2);
#else
#error "EXTI_INT2_ENABLE Error configuration parameter!"
#endif


}

//change sense control while runtime
u8 EXTI_u8SetInt0SenseControl(u8 copy_u8SenseControl){
	u8 Local_u8ErrorStatus = E_OK;
	switch (copy_u8SenseControl){
	case FALLING_EDGE:
		CLR_BIT(MCUCR, MCUCR_ISC00);
		SET_BIT(MCUCR, MCUCR_ISC01);
		break;
	case RISSING_EDGE:
		SET_BIT(MCUCR, MCUCR_ISC00);
		SET_BIT(MCUCR, MCUCR_ISC01);
		break;
	case LOW_LEVEL:
		CLR_BIT(MCUCR, MCUCR_ISC00);
		CLR_BIT(MCUCR, MCUCR_ISC01);
		break;
	case ON_CHANGE:
		SET_BIT(MCUCR, MCUCR_ISC00);
		CLR_BIT(MCUCR, MCUCR_ISC01);
		break;
	default:
		Local_u8ErrorStatus = E_NOT_OK;
		break;
	}
	SET_BIT(GICR, GICR_INT0);
	return Local_u8ErrorStatus;
}
u8 EXTI_u8SetInt1SenseControl(u8 copy_u8SenseControl){
	u8 Local_u8ErrorStatus = E_OK;
	switch (copy_u8SenseControl){
	case FALLING_EDGE:
		CLR_BIT(MCUCR, MCUCR_ISC10);
		SET_BIT(MCUCR, MCUCR_ISC11);
		break;
	case RISSING_EDGE:
		SET_BIT(MCUCR, MCUCR_ISC10);
		SET_BIT(MCUCR, MCUCR_ISC11);
		break;
	case LOW_LEVEL:
		CLR_BIT(MCUCR, MCUCR_ISC10);
		CLR_BIT(MCUCR, MCUCR_ISC11);
		break;
	case ON_CHANGE:
		SET_BIT(MCUCR, MCUCR_ISC10);
		CLR_BIT(MCUCR, MCUCR_ISC11);
		break;
	default:
		Local_u8ErrorStatus = E_NOT_OK;
		break;
	}
	SET_BIT(GICR, GICR_INT1);
	return Local_u8ErrorStatus;
}
u8 EXTI_u8SetInt2SenseControl(u8 copy_u8SenseControl){
	u8 Local_u8ErrorStatus = E_OK;
	switch (copy_u8SenseControl){
	case FALLING_EDGE:
		CLR_BIT(MCUCSR, MCUCSR_ISC2);
		break;
	case RISSING_EDGE:
		SET_BIT(MCUCSR, MCUCSR_ISC2);
		break;
	default:
		Local_u8ErrorStatus = E_NOT_OK;
		break;
	}
	SET_BIT(GICR, GICR_INT2);
	return Local_u8ErrorStatus;
}

// Set callback from user
u8 EXTI_u8Int0SetCallBack(void(*copy_ptrToFunction)(void)){
	u8 Local_u8ErrorStatus = E_OK;
	if(copy_ptrToFunction != NULL)
	{
		Global_ptrToFuncEXTI0 = copy_ptrToFunction;
		Local_u8ErrorStatus = E_OK;
	}
	else
	{
		Local_u8ErrorStatus = E_NOT_OK;
	}
	return Local_u8ErrorStatus;
}
u8 EXTI_u8Int1SetCallBack(void(*copy_ptrToFunction)(void)){
	u8 Local_u8ErrorStatus = E_OK;
	if(copy_ptrToFunction != NULL)
	{
		Global_ptrToFuncEXTI1 = copy_ptrToFunction;
		Local_u8ErrorStatus = E_OK;
	}
	else
	{
		Local_u8ErrorStatus = E_NOT_OK;
	}
	return Local_u8ErrorStatus;
}
u8 EXTI_u8Int2SetCallBack(void(*copy_ptrToFunction)(void)){
	u8 Local_u8ErrorStatus = E_OK;
	if(copy_ptrToFunction != NULL)
	{
		Global_ptrToFuncEXTI2 = copy_ptrToFunction;
		Local_u8ErrorStatus = E_OK;
	}
	else
	{
		Local_u8ErrorStatus = E_NOT_OK;
	}
	return Local_u8ErrorStatus;
}


/* ISR */

/* ISR FOR EXTI0 */
void __vector_1 (void){
	if(Global_ptrToFuncEXTI0 != NULL){
		Global_ptrToFuncEXTI0();
	}
	else
	{

	}
}

/* ISR FOR EXTI1 */
void __vector_2 (void){
	if(Global_ptrToFuncEXTI1 != NULL){
		Global_ptrToFuncEXTI1();
	}
	else
	{

	}
}

/* ISR FOR EXTI2 */
void __vector_3 (void){
	if(Global_ptrToFuncEXTI2 != NULL){
		Global_ptrToFuncEXTI2();
	}
	else
	{

	}
}




