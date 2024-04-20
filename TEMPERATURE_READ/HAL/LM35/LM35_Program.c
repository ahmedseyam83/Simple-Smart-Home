/*
 * LM35_Program.c
 *
 *  Created on: 26 Mar 2024
 *      Author: User
 */

#include "../../LIB/BIT_Math.h"
#include "../../LIB/Std_Types.h"

#include "../../MCAL/ADC/ADC_Interface.h"

#include "LM35_Config.h"
#include "LM35_Private.h"
#include "LM35_Interface.h"


void LM35_voidInit(void)
{
	ADC_voidInit();
}

u16 LM35_u16GetTempReading(u8 copy_u8Channel)
{
	u16 Local_u16TempValueAnalog=0, Local_u16TempValueDigital=0;
	Local_u16TempValueDigital = ADC_u16GetConversionReading(copy_u8Channel);

	#if ADC_REF_SELECTION == AVCC
	Local_u16TempValueAnalog = (Local_u16TempValueDigital * 0.48828125);

	#elif ADC_REF_SELECTION == VOLT_2_56
	Local_u16TempValueAnalog = (Local_u16TempValueDigital * 0.25);

	#else
		#error "ADC_REF_SELECTION error Configuration Parameter"
	#endif

	return Local_u16TempValueAnalog;
}
