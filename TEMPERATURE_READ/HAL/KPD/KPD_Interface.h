/*
 * KPD.h
 *
 *  Created on: 20 Mar 2024
 *      Author: User
 */

#ifndef HAL_KPD_KPD_INTERFACE_H_
#define HAL_KPD_KPD_INTERFACE_H_

#include "../../LIB/BIT_Math.h"
#include "../../LIB/Std_Types.h"
#include "../../MCAL/DIO/DIO_Interface.h"

#define NOTPRESSED		0xFF


void KPD_Init(void);
u8	KPD_u8GetPressed(void);


#endif /* HAL_KPD_KPD_INTERFACE_H_ */
