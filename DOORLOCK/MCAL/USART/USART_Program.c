/*
 * USART_Program.c
 *
 *  Created on: 1 Apr 2024
 *      Author: User
 */



/******************LIB**********************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_Types.h"

/******************MCAL*********************/
#include "USART_Config.h"
#include "USART_Interface.h"
#include "USART_Private.h"

/*******************Global Variables***************/
/*Global variable to carry the send Data*/
static const u8 * USART_pu8SendData = NULL ;

/*Global variable to carry the Receive Data*/
static u8 * USART_pu8ReceiveData = NULL ;

/*Global variable to carry the buffer size*/
static u8 USART_u8BufferSize ;

/*Global variable to indicate for the current Data index of the buffer*/
static u8 USART_u8Index ;

/*Global pointer to function to carry the notification function called by ISR*/
static void (* USART_pvNotificationFunc)(void)= NULL;

/*Global flag for the USART Busy State*/
static u8 USART_u8State= IDLE ;


void USART_voidInit(void)
{
	u8 Local_u8UCSRC = 0;

	/* Calculate the baud rate from the equation*/
	u16 Local_u16UBR= (u16)(SYSTEM_FREQUENCY / (16*USART_BAUD_RATE) - 1);

	/* Set Baud Rate */
	/* Write in UBRRH then UBRRL */
	UBRRH = (u8)(Local_u16UBR>>8);
	UBRRL = (u8)(Local_u16UBR);

	/************* Check 3 Modes ***************/
	#if ( (USART_MODE == ASYNCHRONOUS) && (USART_SYSTEM_SPEED == USART_X1))
		CLR_BIT(UCSRA,UCSRA_U2X);
	#elif ( (USART_MODE == ASYNCHRONOUS) && (USART_SYSTEM_SPEED == USART_X2))
		SET_BIT(UCSRA,UCSRA_U2X);
	#elif (USART_MODE == SYNCHRONOUS)
		Local_u16UBR/=8;
	#else
		#error "WRONG USART_MODE or USART_SYSTEM_SPEED configuration parameters"
	#endif


	/* Multi_processor Mode */
	#if USART_MPCM	== DISABLE
			CLR_BIT(UCSRA,UCSRA_MPCM);
	#elif USART_MPCM	== ENABLE
			CLR_BIT(UCSRA,UCSRA_MPCM);
	#else
		#error "WRONG USART_MPCM configuration parameters"
	#endif

	/*Set USART_MODE*/
	#if USART_MODE == ASYNCHRONOUS
			CLR_BIT(Local_u8UCSRC,UCSRC_UMSEL);
	#elif USART_MODE == SYNCHRONOUS
			SET_BIT(Local_u8UCSRC,UCSRC_UMSEL);
	#else
		#error "WRONG USART_MODE configuration parameters"
	#endif

	/*Set Parity mode*/
	#if USART_PARITY_MODE == DISABLE
			CLR_BIT(Local_u8UCSRC,UCSRC_UPM0);
			CLR_BIT(Local_u8UCSRC,UCSRC_UPM1);
	#elif USART_PARITY_MODE == EVEN_PARITY
			CLR_BIT(Local_u8UCSRC,UCSRC_UPM0);
			SET_BIT(Local_u8UCSRC,UCSRC_UPM1);
	#elif USART_PARITY_MODE == ODD_PARITY
			SET_BIT(Local_u8UCSRC,UCSRC_UPM0);
			SET_BIT(Local_u8UCSRC,UCSRC_UPM1);
	#else
		#error "WRONG USART_PARITY_MODE configuration parameters"
	#endif

	/*Set Stop Bits*/
	#if	UART_STOP_BIT == STOP_BIT_1
			CLR_BIT(Local_u8UCSRC,UCSRC_USBS);
	#elif UART_STOP_BIT == STOP_BIT_2
			SET_BIT(Local_u8UCSRC,UCSRC_USBS);
	#else
		#error "WRONG UART_STOP_BIT configuration parameters"
	#endif

	/*Set Data Size*/
	#if	UART_DATA_SIZE == DATA_SIZE_5_BIT
			CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
			CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
			CLR_BIT(UCSRB,UCSRB_UCSZ2);
	#elif UART_DATA_SIZE == DATA_SIZE_6_BIT
			SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
			CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
			CLR_BIT(UCSRB,UCSRB_UCSZ2);

	#elif UART_DATA_SIZE == DATA_SIZE_7_BIT
			CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
			SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
			CLR_BIT(UCSRB,UCSRB_UCSZ2);

	#elif UART_DATA_SIZE == DATA_SIZE_8_BIT
			SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
			SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
			CLR_BIT(UCSRB,UCSRB_UCSZ2);

	#elif UART_DATA_SIZE == DATA_SIZE_9_BIT
			SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
			SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
			SET_BIT(UCSRB,UCSRB_UCSZ2);

	#else
		#error "WRONG UART_DATA_SIZE configuration parameters"
	#endif

	/*Set CPOL*/
	#if	USART_CLOCK_POLARITY == XCK_RISING_TX_XCH_FALLING_RX
			CLR_BIT(Local_u8UCSRC,UCSRC_UCPOL);
	#elif USART_CLOCK_POLARITY == XCK_RISING_RX_XCH_FALLING_TX
			SET_BIT(Local_u8UCSRC,UCSRC_UCPOL);
	#else
		#error "WRONG USART_CLOCK_POLARITY configuration parameters"
	#endif

	/* Store the local variable in UCSRC Register*/
	UCSRC = Local_u8UCSRC;

	#if USART_TX_COMPLETE_INTERRUPT == DISABLE
			CLR_BIT(UCSRB,UCSRB_TXCIE);
	#elif USART_TX_COMPLETE_INTERRUPT == ENABLE
			SET_BIT(UCSRB,UCSRB_TXCIE);
	#else
		#error "WRONG USART_TX_COMPLETE_INTERRUPT configuration parameters"
	#endif

	#if USART_RX_COMPLETE_INTERRUPT == DISABLE
			CLR_BIT(UCSRB,UCSRB_RXCIE);
	#elif USART_RX_COMPLETE_INTERRUPT == ENABLE
			SET_BIT(UCSRB,UCSRB_RXCIE);
	#else
		#error "WRONG USART_RX_COMPLETE_INTERRUPT configuration parameters"
	#endif

	#if USART_UDR_EMPTY_INTERRUPT == DISABLE
			CLR_BIT(UCSRB,UCSRB_UDRIE);
	#elif USART_UDR_EMPTY_INTERRUPT == ENABLE
			SET_BIT(UCSRB,UCSRB_UDRIE);
	#else
		#error "WRONG USART_UDR_EMPTY_INTERRUPT configuration parameters"
	#endif

	#if USART_RECEIVER_ENABLE == DISABLE
			CLR_BIT(UCSRB,UCSRB_RXEN);
	#elif USART_RECEIVER_ENABLE == ENABLE
			SET_BIT(UCSRB,UCSRB_RXEN);
	#else
		#error "WRONG USART_RECEIVER_ENABLE configuration parameters"
	#endif

	#if USART_TRANSMITTER_ENABLE == DISABLE
			CLR_BIT(UCSRB,UCSRB_TXEN);
	#elif USART_TRANSMITTER_ENABLE == ENABLE
			SET_BIT(UCSRB,UCSRB_TXEN);
	#else
		#error "WRONG USART_TRANSMITTER_ENABLE configuration parameters"
	#endif

}

u8 USART_u8SendData(u8 copy_u8Data)
{
	u8 Local_u8ErrorState = E_OK;
	u32 Local_u32TimeoutCounter = 0;

	if(USART_u8State == IDLE )
	{
		USART_u8State = BUSY;

		while( (Local_u32TimeoutCounter != USART_TIMEOUT) && (GET_BIT(UCSRA,UCSRA_UDRE) == 0) )
		{
			Local_u32TimeoutCounter++;
		}

		if(Local_u32TimeoutCounter == USART_TIMEOUT)
		{
			Local_u8ErrorState= E_NOK;
		}
		else
		{
			UDR = copy_u8Data;
			while(GET_BIT(UCSRA,UCSRA_TXC) == 0);
		}

		USART_u8State = IDLE;

	}
	else
	{
		Local_u8ErrorState = E_NOK_BUSY;
	}

	return Local_u8ErrorState;

}

u8 USART_u8RecevieData(u8 * Copy_u8ReceviedData)
{
	u8 Local_u8ErrorState = E_OK;
		u32 Local_u32TimeoutCounter = 0;

		if(USART_u8State == IDLE )
		{
			USART_u8State = BUSY;

			while( (Local_u32TimeoutCounter != USART_TIMEOUT) && (GET_BIT(UCSRA,UCSRA_RXC) == 0) )
			{
				Local_u32TimeoutCounter++;
			}

			if(Local_u32TimeoutCounter == USART_TIMEOUT)
			{
				Local_u8ErrorState= E_NOK;
			}
			else
			{
				*Copy_u8ReceviedData = UDR;
			}

			USART_u8State = IDLE;

		}
		else
		{
			Local_u8ErrorState = E_NOK_BUSY;
		}

		return Local_u8ErrorState;

}
u8 USART_u8SendStringSynch(const u8 * Copy_pchString)
{
	u8 Local_u8ErrorState = E_OK ;

	u32 Local_u32Index = 0 ;

	if (Copy_pchString != NULL)
	{
		while (Copy_pchString[Local_u32Index] != '\0')
		{
			Local_u8ErrorState = USART_u8SendData(Copy_pchString[Local_u32Index]) ;
			Local_u32Index++ ;
			if (Local_u8ErrorState != E_OK)
			{
				return Local_u8ErrorState ;
			}
		}
	}
	else
	{
		Local_u8ErrorState = E_NOK_NULL_PTR ;
	}

	return Local_u8ErrorState ;
}


//-------------------------------------------------------------------------------------------------------------------------------

u8 USART_u8SendStringAsynch(const u8 * Copy_pchString , void (* NotificationFunc)(void))
{
	u8 Local_u8ErrorState = E_OK ;

	if (USART_u8State == IDLE)
	{
		if ((Copy_pchString != NULL) && (NotificationFunc != NULL))
		{
			/*USART is now Busy*/
			USART_u8State = BUSY ;

			/*Assign the USART data globally*/
			USART_pu8SendData = Copy_pchString ;
			USART_pvNotificationFunc = NotificationFunc ;

			/*Set Index to first element*/
			USART_u8Index = 0 ;

			/*Send first Data */
			UDR = USART_pu8SendData[USART_u8Index] ;

			/*USART Transmit Interrupt Enable*/
			SET_BIT(UCSRB , UCSRB_TXCIE) ;
		}
		else
		{
			Local_u8ErrorState = E_NOK_NULL_PTR ;
		}
	}
	else
	{
		Local_u8ErrorState = E_NOK ;
	}

	return Local_u8ErrorState ;
}


//-------------------------------------------------------------------------------------------------------------------------------

u8 USART_u8ReceiveBufferSynch(u8 * Copy_pchString , u32 Copy_u32BufferSize)
{
	u8 Local_u8ErrorState = E_OK ;

	u32 Local_u32Index = 0 ;

	if (Copy_pchString != NULL)
	{
		while (Local_u32Index < Copy_u32BufferSize)
		{
			Local_u8ErrorState = USART_u8RecevieData(&Copy_pchString[Local_u32Index]) ;
			Local_u32Index++ ;

			if (Local_u8ErrorState != E_OK)
			{
				return Local_u8ErrorState ;
			}
		}
	}
	else
	{
		Local_u8ErrorState = E_NOK_NULL_PTR ;
	}

	return Local_u8ErrorState ;
}


//-------------------------------------------------------------------------------------------------------------------------------

u8 USART_u8ReceiveBufferAsynch(u8 * Copy_pchString , u32 Copy_u32BufferSize , void (* NotificationFunc)(void))
{
	u8 Local_u8ErrorState = E_OK ;

	if (USART_u8State == IDLE)
	{
		if ((Copy_pchString != NULL) && (NotificationFunc != NULL))
		{
			/*USART is now Busy*/
			USART_u8State = BUSY ;

			/*Assign the USART data globally*/
			USART_pu8ReceiveData = Copy_pchString ;
			USART_pvNotificationFunc = NotificationFunc ;
			USART_u8BufferSize = Copy_u32BufferSize;

			/*Set Index to first element*/
			USART_u8Index = 0 ;

			/*USART Recieve Interrupt Enable */
			SET_BIT(UCSRB , UCSRB_RXCIE) ;
		}
		else
		{
			Local_u8ErrorState = E_NOK_NULL_PTR ;
		}
	}
	else
	{
		Local_u8ErrorState = E_NOK ;
	}

	return Local_u8ErrorState ;
}




//-------------------------------------------------------------------------------------------------------------------------------
/* ISR for RX complete */
void __vector_13 (void)		__attribute__ ((signal)) ;
void __vector_13 (void)
{
		/*Receive next Data*/
		USART_pu8ReceiveData[USART_u8Index] = UDR ;

		/*Increment Data index of the buffer*/
		USART_u8Index++ ;

		if (USART_u8Index == USART_u8BufferSize)
		{
			/*Send Data Complete*/

			USART_u8Index=0;
			/*USART is now IDLE*/
			USART_u8State = IDLE ;

			/*Call Notification Function*/
			USART_pvNotificationFunc() ;

			/*USART Recieve Interrupt Disable*/
			CLR_BIT(UCSRB , UCSRB_RXCIE) ;
		}
		else
		{
			/*Do Noting*/
		}

}

//-------------------------------------------------------------------------------------------------------------------------------
/* ISR for TX complete */
void __vector_15 (void)		__attribute__ ((signal)) ;
void __vector_15 (void)
{

		/*Increment Data index of the buffer*/
		USART_u8Index++ ;

		if (USART_pu8SendData[USART_u8Index] == '\0')
		{
			/*Receive Data Complete*/
			USART_u8Index=0;

			/*USART is now IDLE*/
			USART_u8State = IDLE ;

			/*Call Notification Function*/
			USART_pvNotificationFunc() ;

			/*USART Transmit Interrupt Disable*/
			CLR_BIT(UCSRB , UCSRB_TXCIE) ;
		}
		else
		{
			/*Send Data not Complete*/
			/*Send next Data*/
			UDR = USART_pu8SendData[USART_u8Index] ;
		}

}


