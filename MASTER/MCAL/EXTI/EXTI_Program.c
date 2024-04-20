
#include "../../LIB/BIT_Math.h"
#include "../../LIB/Std_Types.h"



#include "EXTI_Config.h"
#include "EXTI_Private.h"
#include "EXTI_Interface.h"



/*********** GLOBAL POINTER TO FUNCTIONS ********/
static void (*GLOBAL_ptrToFuncEXTI0)(void) = NULL;
static void (*GLOBAL_ptrToFuncEXTI1)(void) = NULL;
static void (*GLOBAL_ptrToFuncEXTI2)(void) = NULL;


/************ Functions Implementation ************/

void EXTI_voidInit(void)
{
/***************** EXTI 0 *******************/
	#if	EXTI_INT0_ENABLE == ENABLE

		SET_BIT(GICR,GICR_INT0);

		#if EXTI_INT0_SC == FALLING_EDGE
			CLR_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);

		#elif EXTI_INT0_SC == RISING_EDGE
			SET_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);

		#elif EXTI_INT0_SC == ON_CHANGE
			SET_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);

		#elif EXTI_INT0_SC == LOW_LEVEL
			CLR_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);

		#else
			#error "EXTI_INT0_SC Error Configuration Parameter"

		#endif

	#elif EXTI_INT0_ENABLE == DISABLE

			CLR_BIT(GICR,GICR_INT0);

	#else
		#error "EXTI_INT0_ENABLE Error Configuration Parameter"
	#endif

/***************** EXTI 1 *******************/
	#if	EXTI_INT1_ENABLE == ENABLE
		SET_BIT(GICR,GICR_INT1);
		#if EXTI_INT1_SC == FALLING_EDGE
			CLR_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);

		#elif EXTI_INT1_SC == RISING_EDGE
			SET_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);

		#elif EXTI_INT1_SC == ON_CHANGE
			SET_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);

		#elif EXTI_INT1_SC == LOW_LEVEL
			CLR_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);

		#else
			#error "EXTI_INT1_SC Error Configuration Parameter"

		#endif

	#elif EXTI_INT1_ENABLE == DISABLE
			CLR_BIT(GICR,GICR_INT1);
	#else
		#error "EXTI_INT1_ENABLE Error Configuration Parameter"
	#endif

/***************** EXTI 2 *******************/
	#if	EXTI_INT2_ENABLE == ENABLE
		SET_BIT(GICR,GICR_INT2);
		#if EXTI_INT2_SC == FALLING_EDGE
			CLR_BIT(MCUCSR,MCUCSR_ISC2);

		#elif EXTI_INT2_SC == RISING_EDGE
			SET_BIT(MCUCSR,MCUCSR_ISC2);

		#else
			#error "EXTI_INT2_SC Error Configuration Parameter"

		#endif

	#elif EXTI_INT2_ENABLE == DISABLE
			CLR_BIT(GICR,GICR_INT2);
	#else
		#error "EXTI_INT2_ENABLE Error Configuration Parameter"
	#endif

}

u8 EXTI_u8SetInt0SC(u8 copy_u8SenseControl)
{
	u8 Local_u8ErrorStatus = E_OK;
	switch(copy_u8SenseControl)
	{
		case FALLING_EDGE:
			CLR_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
		case ON_CHANGE:
			SET_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		case LOW_LEVEL:
			CLR_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		default:
			Local_u8ErrorStatus = E_NOK;
			break;
	}
	SET_BIT(GICR,GICR_INT0);
	return Local_u8ErrorStatus;
}

u8 EXTI_u8SetInt1SC(u8 copy_u8SenseControl)
{
	u8 Local_u8ErrorStatus = E_OK;
	switch(copy_u8SenseControl)
	{
		case FALLING_EDGE:
			CLR_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			break;
		case ON_CHANGE:
			SET_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
		case LOW_LEVEL:
			CLR_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
		default:
			Local_u8ErrorStatus = E_NOK;
			break;
	}
	SET_BIT(GICR,GICR_INT1);
	return Local_u8ErrorStatus;


}

u8 EXTI_u8SetInt2SC(u8 copy_u8SenseControl)
{
	u8 Local_u8ErrorStatus = E_OK;
	switch(copy_u8SenseControl)
	{
		case FALLING_EDGE:
			CLR_BIT(MCUCSR,MCUCSR_ISC2);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCSR,MCUCSR_ISC2);
			break;
		default:
			Local_u8ErrorStatus = E_NOK;
			break;
	}
	SET_BIT(GICR,GICR_INT2);
	return Local_u8ErrorStatus;
}

u8 EXTI_u8INT0SetCallBack(void(*copy_ptrToFunction)(void))
{
	u8 Local_u8ErrorStatus = E_OK;
	if(copy_ptrToFunction != NULL)
	{
		GLOBAL_ptrToFuncEXTI0 = copy_ptrToFunction;
	}
	else
	{
		Local_u8ErrorStatus = E_NOK;
	}
	return Local_u8ErrorStatus;
}

void EXTI_voidClearInt0Flag(void)
{
	SET_BIT(GIFR,GIFR_INTF0);

}
void EXTI_voidClearInt1Flag(void)
{
	SET_BIT(GIFR,GIFR_INTF1);
}
void EXTI_voidClearInt2Flag(void)
{
	SET_BIT(GIFR,GIFR_INTF2);
}

u8 EXTI_u8INT1SetCallBack(void(*copy_ptrToFunction)(void))
{
	u8 Local_u8ErrorStatus = E_OK;
	if(copy_ptrToFunction != NULL)
	{
		GLOBAL_ptrToFuncEXTI1 = copy_ptrToFunction;
	}
	else
	{
		Local_u8ErrorStatus = E_NOK;
	}
	return Local_u8ErrorStatus;
}

u8 EXTI_u8INT2SetCallBack(void(*copy_ptrToFunction)(void))
{
	u8 Local_u8ErrorStatus = E_OK;
	if(copy_ptrToFunction != NULL)
	{
		GLOBAL_ptrToFuncEXTI2 = copy_ptrToFunction;
	}
	else
	{
		Local_u8ErrorStatus = E_NOK;
	}
	return Local_u8ErrorStatus;
}


/*********** ISR **************************/
/****ISR EXTI0*****/
void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if(GLOBAL_ptrToFuncEXTI0 != NULL)
	{
		GLOBAL_ptrToFuncEXTI0();
	}
	else
	{

	}

}

/****ISR EXTI1*****/
void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	if(GLOBAL_ptrToFuncEXTI1 != NULL)
	{
		GLOBAL_ptrToFuncEXTI1();
	}
	else
	{

	}

}

/****ISR EXTI2*****/
void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	if(GLOBAL_ptrToFuncEXTI2 != NULL)
	{
		GLOBAL_ptrToFuncEXTI2();
	}
	else
	{

	}

}
