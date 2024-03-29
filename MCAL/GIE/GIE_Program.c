/*
 * GIE_Program.c
 *
 *  Created on: Mar 24, 2024
 *      Author: sakr3
 */

#ifndef MCAL_GIE_GIE_PROGRAM_C_
#define MCAL_GIE_GIE_PROGRAM_C_

/********************************* LIB *********************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

/********************************* MCAL *********************************/
#include "GIE_Interface.h"
#include "GIE_private.h"

void GIE_voidEnable(void){
	SET_BIT(SREG, SREG_I_BIT);
}
void GIE_voidDisable(void){
	CLR_BIT(SREG, SREG_I_BIT);
}

#endif /* MCAL_GIE_GIE_PROGRAM_C_ */
