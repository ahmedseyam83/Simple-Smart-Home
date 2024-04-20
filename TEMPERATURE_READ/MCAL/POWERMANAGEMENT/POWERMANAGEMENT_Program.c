/*
 * POWERMANAGEMENT_Program.c
 *
 *  Created on: 8 Apr 2024
 *      Author: User
 */


/******************LIB**********************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_Types.h"

/******************MCAL*********************/
#include "POWERMANAGEMENT_Config.h"
#include "POWERMANAGEMENT_Interface.h"
#include "POWERMANAGEMENT_Private.h"

void Set_SleepMode(void)
{
	#if POWER_MANAGEMENT_MODE == IDLE_MODE
			CLR_BIT(MCUCR,SM0);
			CLR_BIT(MCUCR,SM1);
			CLR_BIT(MCUCR,SM2);

	#elif POWER_MANAGEMENT_MODE == ADC_NR_MODE
			SET_BIT(MCUCR,SM0);
			CLR_BIT(MCUCR,SM1);
			CLR_BIT(MCUCR,SM2);

	#elif POWER_MANAGEMENT_MODE == PWR_DOWN_MODE
			CLR_BIT(MCUCR,SM0);
			SET_BIT(MCUCR,SM1);
			CLR_BIT(MCUCR,SM2);

	#elif POWER_MANAGEMENT_MODE == PWR_SAVE_MODE
			SET_BIT(MCUCR,SM0);
			SET_BIT(MCUCR,SM1);
			CLR_BIT(MCUCR,SM2);

	#elif POWER_MANAGEMENT_MODE == RESERVED_MODE
			CLR_BIT(MCUCR,SM0);
			CLR_BIT(MCUCR,SM1);
			SET_BIT(MCUCR,SM2);

	#elif POWER_MANAGEMENT_MODE == STANDBY_MODE
			CLR_BIT(MCUCR,SM0);
			SET_BIT(MCUCR,SM1);
			SET_BIT(MCUCR,SM2);

	#elif POWER_MANAGEMENT_MODE == EXT_STANDBY_MODE
			SET_BIT(MCUCR,SM0);
			SET_BIT(MCUCR,SM1);
			SET_BIT(MCUCR,SM2);
	#else
		#error "wrong POWER_MANAGEMENT_MODE Configuration Parameter"
	#endif

}


void Change_SleepMode(u8 SleepMode)
{
	switch(SleepMode)
		{
			case IDLE_MODE:
			CLR_BIT(MCUCR,SM0);
			CLR_BIT(MCUCR,SM1);
			CLR_BIT(MCUCR,SM2);
			break;
			case ADC_NR_MODE:
			SET_BIT(MCUCR,SM0);
			CLR_BIT(MCUCR,SM1);
			CLR_BIT(MCUCR,SM2);
			break;
			case PWR_DOWN_MODE:
			CLR_BIT(MCUCR,SM0);
			SET_BIT(MCUCR,SM1);
			CLR_BIT(MCUCR,SM2);
			break;
			case PWR_SAVE_MODE:
			SET_BIT(MCUCR,SM0);
			SET_BIT(MCUCR,SM1);
			CLR_BIT(MCUCR,SM2);
			break;
			case RESERVED_MODE:
			CLR_BIT(MCUCR,SM0);
			CLR_BIT(MCUCR,SM1);
			SET_BIT(MCUCR,SM2);
			break;
			case STANDBY_MODE:
			CLR_BIT(MCUCR,SM0);
			SET_BIT(MCUCR,SM1);
			SET_BIT(MCUCR,SM2);
			break;
			case EXT_STANDBY_MODE:
			SET_BIT(MCUCR,SM0);
			SET_BIT(MCUCR,SM1);
			SET_BIT(MCUCR,SM2);
			break;
		}
}
void CPU_SleepEnable(void)
{
	SET_BIT(MCUCR,SE);
}

void CPU_SleepDisable(void)
{
	CLR_BIT(MCUCR,SE);
}

void Sleep_CPU(void)
{
	do
	{
		sleep();
	} while (0);
}

void CPU_Sleep(void)
{
	Set_SleepMode();
	cli();
	CPU_SleepEnable();
	sei();
	Sleep_CPU();
	CPU_SleepDisable();
}

