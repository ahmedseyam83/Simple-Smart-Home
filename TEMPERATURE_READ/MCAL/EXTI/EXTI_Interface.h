/*
 * EXTI_Interface.h
 *
 *  Created on: 24 Mar 2024
 *      Author: User
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

/*************** General MACROS *******************/

#define FALLING_EDGE	1
#define	RISING_EDGE		2
#define	LOW_LEVEL		3
#define	ON_CHANGE		4


/*************** Function Prototypes **************/
void EXTI_voidInit(void);

u8 EXTI_u8SetInt0SC(u8 copy_u8SenseControl);
u8 EXTI_u8SetInt1SC(u8 copy_u8SenseControl);
u8 EXTI_u8SetInt2SC(u8 copy_u8SenseControl);

u8 EXTI_u8INT0SetCallBack(void(*copy_ptrToFunction)(void));
u8 EXTI_u8INT1SetCallBack(void(*copy_ptrToFunction)(void));
u8 EXTI_u8INT2SetCallBack(void(*copy_ptrToFunction)(void));

void EXTI_voidClearInt0Flag(void);
void EXTI_voidClearInt1Flag(void);
void EXTI_voidClearInt2Flag(void);




#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
