/*
 * KPD.c
 *
 *  Created on: 20 Mar 2024
 *      Author: User
 */
/***************************** File Inclusion *****************************************************/
/*************** Library Inclusions ***************/



#include "KPD_Config.h"
#include "KPD_Interface.h"
#include "KPD_Private.h"
#include "avr/delay.h"


void KPD_Init(void)
{
	//Connect pull up for the rows pins

	DIO_u8ConnectPullUP(KPD_PORT,KPD_R0,DIO_PIN_HIGH);
	DIO_u8ConnectPullUP(KPD_PORT,KPD_R1,DIO_PIN_HIGH);
	DIO_u8ConnectPullUP(KPD_PORT,KPD_R2,DIO_PIN_HIGH);
	DIO_u8ConnectPullUP(KPD_PORT,KPD_R3,DIO_PIN_HIGH);

	//Make the Direction of Column pins Output
	DIO_u8SetPinDirection(KPD_PORT,KPD_C0,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT,KPD_C1,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT,KPD_C2,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT,KPD_C3,DIO_PIN_OUTPUT);

	//Make the Value of Column pins High
	DIO_u8SetPinValue(KPD_PORT,KPD_C0,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT,KPD_C1,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT,KPD_C2,DIO_PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT,KPD_C3,DIO_PIN_HIGH);
}


u8	KPD_u8GetPressed(void)
{
	u8 Local_u8Col , Local_u8Row , Local_u8ReturnData = NOTPRESSED , LocaL_u8GetPressed=1 ;

	for( Local_u8Col= KPD_COL_INIT ; Local_u8Col < KPD_COL_END +1 ; Local_u8Col++ )
	{
		DIO_u8SetPinValue(KPD_PORT,Local_u8Col,DIO_PIN_LOW);
		for( Local_u8Row= KPD_ROW_INIT ; Local_u8Row <KPD_ROW_END +1 ; Local_u8Row ++ )
		{
			DIO_u8GetPinValue(KPD_PORT,Local_u8Row,&LocaL_u8GetPressed);
			if( LocaL_u8GetPressed == DIO_PIN_LOW )
			{
				_delay_ms(50);

				DIO_u8GetPinValue(KPD_PORT,Local_u8Row,&LocaL_u8GetPressed);
				if(LocaL_u8GetPressed == DIO_PIN_LOW)
				{
					Local_u8ReturnData = KPD_u8Buttons[Local_u8Row - KPD_ROW_INIT][Local_u8Col - KPD_COL_INIT];

					while(LocaL_u8GetPressed == 0)
					{
						DIO_u8GetPinValue(KPD_PORT,Local_u8Row,&LocaL_u8GetPressed);
					}
					break;
				}
			}
		}
		DIO_u8SetPinValue(KPD_PORT,Local_u8Col,DIO_PIN_HIGH);
	}
	return Local_u8ReturnData;
}
