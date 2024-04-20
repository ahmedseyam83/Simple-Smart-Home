/*
 * ADC_Interface.h
 *
 *  Created on: 26 Mar 2024
 *      Author: User
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

/******************** MACROS ***********************/

#define CHANNEL0	0
#define CHANNEL1	1
#define CHANNEL2	2
#define CHANNEL3	3
#define CHANNEL4	4
#define CHANNEL5	5
#define CHANNEL6	6
#define CHANNEL7	7




/********************* FUNCTION PROTOTYPES ******************/
void ADC_voidInit(void);

u16 ADC_u16GetConversionReading(u8 copy_u8Channel);



#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
