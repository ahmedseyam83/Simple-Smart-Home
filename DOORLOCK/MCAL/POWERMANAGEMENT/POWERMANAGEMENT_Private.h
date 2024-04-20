/*
 * POWERMANAGEMENT_Private.h
 *
 *  Created on: 8 Apr 2024
 *      Author: User
 */

#ifndef MCAL_POWERMANAGEMENT_POWERMANAGEMENT_PRIVATE_H_
#define MCAL_POWERMANAGEMENT_POWERMANAGEMENT_PRIVATE_H_



/* POWER MANAGEMENT */
/* MCUCR */

#define MCUCR   (*(volatile unsigned char*)0x55)

#define SE      7
#define SM2     6
#define SM1     5
#define SM0     4

# define sei()  __asm__ __volatile__ ("sei" ::)
# define cli()  __asm__ __volatile__ ("cli" ::)
# define sleep() __asm__ __volatile__ ( "sleep" "\n\t" :: )

#endif /* MCAL_POWERMANAGEMENT_POWERMANAGEMENT_PRIVATE_H_ */
