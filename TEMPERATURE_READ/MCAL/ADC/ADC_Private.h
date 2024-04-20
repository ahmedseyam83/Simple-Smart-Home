/*
 * ADC_Private.h
 *
 *  Created on: 26 Mar 2024
 *      Author: User
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

/****************REGISTERS****************************/
#define ADMUX   	  (*((volatile u8*)0x27))
#define ADCSRA   	  (*((volatile u8*)0x26))
#define ADCL    	  (*((volatile u8*)0x24))
#define ADCH	      (*((volatile u8*)0x25))

// ADMUX_REG BITS
#define REFS1              7
#define REFS0              6
#define ADLAR              5
#define MUX4               4
#define MUX3               3
#define MUX2               2
#define MUX1               1
#define MUX0               0

// ADCSRA_REG BITS
#define ADEN               7
#define ADSC               6
#define ADATE              5
#define ADIF               4
#define ADIE			   3
#define ADPS2              2
#define ADPS1              1
#define ADPS0              0

/*****************PRIVATE MACROS************************/
#define AREFF		1
#define	AVCC		2
#define	VOLT_2_56	3

#define LEFT_ADJUSMENT	1
#define RIGH_ADJUSMENT	2

#define ENABLE		1
#define DISABLE		2

#define PRESCALER_2		1
#define PRESCALER_4		2
#define PRESCALER_8		3
#define PRESCALER_16	4
#define PRESCALER_32	5
#define PRESCALER_64	6
#define PRESCALER_128	7

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
