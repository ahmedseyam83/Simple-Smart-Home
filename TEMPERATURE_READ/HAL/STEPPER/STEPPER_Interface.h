/*
 * STEPPER_Interface.h
 *
 *  Created on: 21 Mar 2024
 *      Author: User
 */

#ifndef HAL_STEPPER_STEPPER_INTERFACE_H_
#define HAL_STEPPER_STEPPER_INTERFACE_H_


/****************************LIB***************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_Types.h"

/********************** User Macros **********************/
#define	NORTH			0

#define	EASTERN_NORTH	1
#define EAST			2
#define EASTERN_SOUTH	3

#define SOUTH			4

#define WESTERN_SOUTH	5
#define WEST			6
#define WESTERN_NORTH	7



/********************** Functions Prototypes *************/

void STEPPER_voidInit(void);
void STEPPER_voidRotate(u8 copy_u8Direction);



#endif /* HAL_STEPPER_STEPPER_INTERFACE_H_ */
