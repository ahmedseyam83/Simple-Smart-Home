/*
 * SystemControl.c
 *
 *  Created on: 16 Apr 2024
 *      Author: User
 */

/******************LIB ***********************/
#include "../LIB/BIT_Math.h"
#include "../LIB/Std_Types.h"

#include <util/delay.h>

/******************MCAL**********************/
#include "../MCAL/GIE/GIE_Interface.h"
#include "../MCAL/TWI/TWI_Interface.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/USART/USART_Interface.h"

/*****************HAL***********************/
#include "../HAL/KPD/KPD_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/EEPROM/EEPROM_Interface.h"

/****************Services******************/
#include "SystemControl_Interface.h"
#include "SystemControl_Private.h"
#include "SystemControl_Config.h"

/*****************OS***********************/
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/semphr.h"


#define MAX_TIME 0xffff

/******************************** Global Variables Initialisation**************************************/
u8 Local_u8Pressed = NOTPRESSED ,Global_u8TryCounter=1,Global_u8RepPWReq=FIRST_TRY,Global_u8RepEnter = FIRST_NUMBER,Global_PWResult=0;
u8 COL=0;


extern xTaskHandle xEnterHandle;
extern xTaskHandle xKeyHandle;

extern xSemaphoreHandle LCD_Mutex;
extern xSemaphoreHandle PW_CheckSemaphore;
extern xSemaphoreHandle PW_EnterSemaphore;

extern xQueueHandle PW_Queue;







void Keypad_Task(void *ptr)
{
	while(1)
	{
		Local_u8Pressed = KPD_u8GetPressed();
		vTaskDelay(50);
	}
}

void PW_Set(void *ptr)
{
	static u16 Local_u16Password=2024;
	while(1)
	{
		EEPROM_voidSendDataByte(0x20,(u8)Local_u16Password);
		EEPROM_voidSendDataByte(0x21, ((u8)(Local_u16Password>>8)));
		xSemaphoreGive(PW_EnterSemaphore);
		vTaskDelete(NULL);
	}
}
void PW_Enter(void *ptr)
{

	static u8 Local_u8Number=0;
	static u16 Local_u16Password= 0;
	static u16* Local_pu16Password= &Local_u16Password;
	LCD_voidSetPosition(0,0);
	LCD_voidSendString((u8*)"Enter Your PW:");
	xSemaphoreGive(LCD_Mutex);


	while(1)
	{

		xSemaphoreTake(LCD_Mutex,MAX_TIME);

		if(Local_u8Pressed != NOTPRESSED && Local_u8Pressed != '=')
		{
			xSemaphoreTake(PW_EnterSemaphore,MAX_TIME);
			LCD_voidSetPosition(LCD_ROW1,COL);
			COL++;
			LCD_voidSendData('*');
			Local_u8Number = (Local_u8Pressed - '0');
			if(FIRST_NUMBER == Global_u8RepEnter )
			{
				Local_u16Password = Local_u8Number;

				Global_u8RepEnter = 1;
			}
			else if( OTHER_NUMBER == Global_u8RepEnter && Local_u8Number != 0)
			{
				Local_u16Password = ((Local_u16Password *10) + Local_u8Number);
			}
			else if( OTHER_NUMBER == Global_u8RepEnter && Local_u8Number == 0)
			{
				Local_u16Password *= 10;
			}
			Local_u8Pressed= NOTPRESSED;
			xSemaphoreGive(PW_EnterSemaphore);
		}
		else if(Local_u8Pressed != NOTPRESSED && Local_u8Pressed == '=')
		{
			Local_u8Pressed= NOTPRESSED;
			xQueueSend(PW_Queue,(void*)&Local_pu16Password,0);
			xSemaphoreGive(PW_CheckSemaphore);
		}
		xSemaphoreGive(LCD_Mutex);
	}

}

void PW_Check(void *ptr)
{

	static u16 Local_u16CheckPassword=0;
	static u16 Local_u16Password= 0;
	static u16* Local_pu16Password = &Local_u16Password;


	while(1)
	{

		xSemaphoreTake(PW_CheckSemaphore,MAX_TIME);
		xSemaphoreTake(LCD_Mutex,MAX_TIME);
		if(FIRST_TRY == Global_u8RepPWReq)
		{
			LCD_voidClearScreen();
			LCD_voidSetPosition(LCD_ROW0,0);
			Local_u16CheckPassword = (u16)(EEPROM_u8ReadDataByte(0x21)<<8);
			Local_u16CheckPassword |= EEPROM_u8ReadDataByte(0x20);

			Global_u8RepPWReq = OTHER_TRY;
		}
		else
		{

		}


		xQueueReceive(PW_Queue,(void *)&Local_pu16Password,MAX_TIME);

		if(*Local_pu16Password == Local_u16CheckPassword)
		{

			LCD_voidClearScreen();
			LCD_voidSetPosition(LCD_ROW0,0);
			LCD_voidSendString((u8*)"Welcome Home!");


			vTaskDelay(1000);

			// Wake Up Controllers
			DIO_u8SetPinValue(DIO_PORTD,DIO_PIN4,DIO_PIN_HIGH);
			vTaskDelay(50);
			DIO_u8SetPinValue(DIO_PORTD,DIO_PIN4,DIO_PIN_LOW);


			vTaskDelay(1000);

			USART_u8SendData(SAFE_ENTER);

			vTaskDelete(xEnterHandle);
			vTaskDelete(xKeyHandle);
			vTaskDelete(NULL);
		}
		else if(*Local_pu16Password != Local_u16CheckPassword)
		{
			LCD_voidClearScreen();
			LCD_voidSetPosition(LCD_ROW0,0);
			LCD_voidSendString((u8*)"InCorrect PW");
			vTaskDelay(500);
			if(Global_u8TryCounter<3)
			{
				LCD_voidClearScreen();
				LCD_voidSetPosition(LCD_ROW0,0);
				LCD_voidSendString((u8*)"Max 3 Tries");
				LCD_voidSetPosition(LCD_ROW1,0);
				LCD_voidSendString((u8*)"Try Left ");
				LCD_voidSendNumber((3-Global_u8TryCounter));
				vTaskDelay(500);
				LCD_voidClearScreen();
				LCD_voidSendString((u8*)"Enter PW AGAIN: ");
				Global_u8TryCounter++;
				COL=0;
				Local_u16Password=0;
				xSemaphoreGive(PW_EnterSemaphore);
			}
			else
			{
				LCD_voidClearScreen();
				LCD_voidSetPosition(LCD_ROW0,0);
				LCD_voidSendString((u8*)"Maximum Tries");


				vTaskDelay(1000);

				LCD_voidClearScreen();
				LCD_voidSendString((u8*)"Thief Alert!");


				// Wake Up Controllers
				DIO_u8SetPinValue(DIO_PORTD,DIO_PIN4,DIO_PIN_HIGH);
				vTaskDelay(50);
				DIO_u8SetPinValue(DIO_PORTD,DIO_PIN4,DIO_PIN_LOW);

				vTaskDelay(1000);

				USART_u8SendData(THIEF_ENTER);

				vTaskDelete(xEnterHandle);
				vTaskDelete(xKeyHandle);
				vTaskDelete(NULL);
			}
		}
		xSemaphoreGive(LCD_Mutex);
	}
}


