/*
 * DCMOTOR_Interface.h
 *
 *  Created on: 21 Mar 2024
 *      Author: User
 */

#ifndef HAL_DCMOTOR_DCMOTOR_INTERFACE_H_
#define HAL_DCMOTOR_DCMOTOR_INTERFACE_H_


/****************************LIB***************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_Types.h"



/******************** Function Prototypes **************/

void MOTOR_voidInit(void);
void MOTOR_voidCounterClockWise(void);
void MOTOR_voidClockWise(void);
void MOTOR_voidStop(void);




#endif /* HAL_DCMOTOR_DCMOTOR_INTERFACE_H_ */
