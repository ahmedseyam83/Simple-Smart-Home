/*
 * ADC_Program.c
 *
 *  Created on: 26 Mar 2024
 *      Author: User
 */

/***************************** File Inclusion *****************************************************/
/*************** Library Inclusions ***************/

#include "../../LIB/BIT_Math.h"
#include "../../LIB/Std_Types.h"





#include "ADC_Config.h"
#include "ADC_Private.h"
#include "ADC_Interface.h"

/********************* FUNCTION IMPLEMENTATION ******************/

void ADC_voidInit(void)
{
	#if ADC_REF_SELECTION == AREFF
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);

	#elif ADC_REF_SELECTION == AVCC
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);

	#elif ADC_REF_SELECTION == VOLT_2_56
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
	#else
		#error "ADC_REF_SELECTION error Configuration Parameter"
	#endif

	#if ADC_ADJUSMENT == LEFT_ADJUSMENT
		SET_BIT(ADMUX,ADLAR);
	#elif ADC_ADJUSMENT == RIGHT_ADJUSMENT
		CLR_BIT(ADMUX,ADLAR);
	#else
		#error "ADC_ADJUSMENT error Configuration Parameter"
	#endif

	#if AUTO_TRIGGER == DISABLE
		CLR_BIT(ADCSRA,ADATE);
	#elif AUTO_TRIGGER == ENABLE
		SET_BIT(ADCSRA,ADATE);
	#else
		#error "AUTO_TRIGGER error Configuration Parameter"
	#endif

	#if ADC_INTERRUPT == DISABLE
		CLR_BIT(ADCSRA,ADIE);
	#elif ADC_INTERRUPT == ENABLE
		SET_BIT(ADCSRA,ADIE);
	#else
		#error "ADC_INTERRUPT error Configuration Parameter"
	#endif

	#if	ADC_PRESCALER == PRESCALER_2
		CLR_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#elif ADC_PRESCALER == PRESCALER_4
		CLR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
	#elif ADC_PRESCALER == PRESCALER_8
		CLR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#elif ADC_PRESCALER == PRESCALER_16
		SET_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
	#elif ADC_PRESCALER == PRESCALER_32
		SET_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#elif ADC_PRESCALER == PRESCALER_64
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
	#elif ADC_PRESCALER == PRESCALER_128
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#else
		#error "ADC_PRESCALER error Configuration Parameter"
	#endif

	SET_BIT(ADCSRA,ADEN);

}

u16 ADC_u16GetConversionReading(u8 copy_u8Channel)
{
	u16 ADC_data =0;

	if (copy_u8Channel == CHANNEL0)
	{
		/** Select input channel to pin PA0 */
		CLR_BIT(ADMUX,MUX0);
		CLR_BIT(ADMUX,MUX1);
		CLR_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
	}
	else if(copy_u8Channel == CHANNEL1)
	{
		/** Select input channel to pin PA1 */
		SET_BIT(ADMUX,MUX0);
		CLR_BIT(ADMUX,MUX1);
		CLR_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
	}
	else if(copy_u8Channel == CHANNEL2)
	{
		/** Select input channel to pin PA2 */
		CLR_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		CLR_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
	}
	else if(copy_u8Channel == CHANNEL3)
	{
		/** Select input channel to pin PA3 */
		SET_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		CLR_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
	}
	else if(copy_u8Channel == CHANNEL4)
	{
		/** Select input channel to pin PA4 */
		CLR_BIT(ADMUX,MUX0);
		CLR_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
	}
	else if(copy_u8Channel == CHANNEL5)
	{
		/** Select input channel to pin PA5 */
		SET_BIT(ADMUX,MUX0);
		CLR_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
	}
	else if(copy_u8Channel == CHANNEL6)
	{
		/** Select input channel to pin PA6 */
		CLR_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
	}
	else if(copy_u8Channel == CHANNEL7)
	{
		/** Select input channel to pin PA7 */
		SET_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
	}
	else
	{

	}

	/* Start Converstion */
	SET_BIT(ADCSRA,ADSC);

	/* Wait until conversion complete */
	while(GET_BIT(ADCSRA,ADSC));


	#if ADC_ADJUSMENT == RIGHT_ADJUSMENT
	/* After Conversion is finished Read data from ADCL then ADCH */
		ADC_data = ADCL;
		ADC_data |= (ADCH << 8);
	#elif ADC_ADJUSMENT == LEFT_ADJUSMENT
		ADC_data = (ADCL>>6);
		ADC_data |= (ADCH << 2);
	#endif

	return ADC_data;
}


