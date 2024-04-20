/*
 * LM35_Interface.h
 *
 *  Created on: 26 Mar 2024
 *      Author: User
 */

#ifndef HAL_LM35_LM35_INTERFACE_H_
#define HAL_LM35_LM35_INTERFACE_H_



/********************* FUNCTION PROTOTYPES ******************/
void LM35_voidInit(void);

u16 LM35_u16GetTempReading(u8 copy_u8Channel);



#endif /* HAL_LM35_LM35_INTERFACE_H_ */
