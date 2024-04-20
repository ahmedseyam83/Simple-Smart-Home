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

#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/USART/USART_Interface.h"
#include "../MCAL/SPI/SPI_Interface.h"
#include "../MCAL/TIMERS/TIMERS_Interface.h"
/*****************HAL***********************/

#include "../HAL/LCD/LCD_Interface.h"


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
u8 Global_u8DummyReceived=0x0,Global_u8DummySent=0xff, Global_u8RepEnter1=MULTIPLE_ENTER,Global_u8RepEnter2=MULTIPLE_ENTER;
u8 Global_u8Operation_Flag=HOME_EMPTY;
u8 Global_u8CommunicationFlag=HOME_EMPTY;

portBASE_TYPE pxHigherPriorityTaskWoken= pdFALSE,pxHigherPriorityTaskWoken2= pdFALSE;


extern xSemaphoreHandle BTN1_Semaphore,BTN2_Semaphore,LCD_xMutex,Fan_Semaphore;

extern xQueueHandle Temp_Queue;

void Button_1(void)
{
	Global_u8RepEnter1 = SINGLE_ENTER;
	xSemaphoreGiveFromISR(BTN1_Semaphore,pxHigherPriorityTaskWoken);
	if(pxHigherPriorityTaskWoken==pdTRUE)
		taskYIELD();
}
void Button_2(void)
{
	Global_u8RepEnter2 = SINGLE_ENTER;
	xSemaphoreGiveFromISR(BTN2_Semaphore,pxHigherPriorityTaskWoken2);
	if(pxHigherPriorityTaskWoken==pdTRUE)
		taskYIELD();
}


void ROOM_1(void *ptr)
{
	xSemaphoreTake(BTN1_Semaphore,0);
	static u8 Local_u8TempValue1 = 0;
	xSemaphoreGive(LCD_xMutex);

	while(1)
	{
		xSemaphoreTake(BTN1_Semaphore,MAX_TIME);
		SPI_u8Tranceive(BUTTON1_PRESSED,&Global_u8DummyReceived);

		if(Global_u8Operation_Flag == HOME_ENTERED)
		{
			xSemaphoreTake(LCD_xMutex,0xff);

			LCD_voidClearScreen();
			LCD_voidSetPosition(0,0);
			LCD_voidSendString((u8*)"ROOM 1");
			LCD_voidSetPosition(1,0);
			LCD_voidSendString((u8*)"Temperature: ");
			LCD_voidSetPosition(1,12);

			SPI_u8Tranceive(Global_u8DummySent,&Local_u8TempValue1);

			xQueueSend(Temp_Queue,(void*) (4),0);
			xQueueSend(Temp_Queue,(void*)&Local_u8TempValue1,0);

			if(Local_u8TempValue1<10)
			{
				LCD_voidSetPosition(1,12);
				LCD_voidSendString((u8*)" ");
				LCD_voidSendNumber(Local_u8TempValue1);
			}

			else
			{
				LCD_voidSetPosition(1,12);
				LCD_voidSendNumber(Local_u8TempValue1);
			}


			xSemaphoreGive(LCD_xMutex);
			vTaskDelay(500);
		}
		xSemaphoreGive(Fan_Semaphore);
	}
}

void ROOM_2(void *ptr)
{
	xSemaphoreTake(BTN2_Semaphore,0);
	static u8 Local_u8TempValue2 = 0;
	xSemaphoreGive(LCD_xMutex);

	while(1)
	{

		xSemaphoreTake(BTN2_Semaphore,MAX_TIME);
		SPI_u8Tranceive(BUTTON2_PRESSED,&Global_u8DummyReceived);

		if(Global_u8Operation_Flag == HOME_ENTERED)
		{
			xSemaphoreTake(LCD_xMutex,MAX_TIME);
			LCD_voidClearScreen();
			LCD_voidSetPosition(0,0);
			LCD_voidSendString((u8*)"ROOM 2");
			LCD_voidSetPosition(1,0);
			LCD_voidSendString((u8*)"Temperature: ");
			LCD_voidSetPosition(1,12);

			SPI_u8Tranceive(Global_u8DummySent,&Local_u8TempValue2);

			xQueueSend(Temp_Queue,(void*) (5),0);
			xQueueSend(Temp_Queue,(void*)&Local_u8TempValue2,0);




			if(Local_u8TempValue2<10)
			{
				LCD_voidSetPosition(1,12);
				LCD_voidSendString((u8*)" ");
				LCD_voidSendNumber(Local_u8TempValue2);
			}

			else
			{
				LCD_voidSetPosition(1,12);
				LCD_voidSendNumber(Local_u8TempValue2);
			}

			xSemaphoreGive(LCD_xMutex);
			vTaskDelay(500);
		}
		xSemaphoreGive(Fan_Semaphore);
	}


}

void UART_TASK(void *ptr)
{

	while(1)
	{
		USART_u8RecevieData(&Global_u8CommunicationFlag);

		if(Global_u8CommunicationFlag == THIEF_ENTER)
		{
			Global_u8Operation_Flag = HOME_UNENTERED;
			DIO_u8TogglePinValue(DIO_PORTA,BUZZER_PIN);
			DIO_u8TogglePinValue(DIO_PORTA,ALERT_LED_PIN);
			vTaskDelay(500);
		}
		else if(Global_u8CommunicationFlag == SAFE_ENTER)
		{
			Global_u8Operation_Flag = HOME_ENTERED;
			vTaskDelete(NULL);
		}
		else
		{
			Global_u8Operation_Flag = HOME_EMPTY;
		}
	}
}

void FAN(void *ptr)
{

	static u8 Local_u8Received = 0;
	static u8 Local_u8Temp1Received=0;
	static u8 Local_u8Temp2Received=0;

	while(1)
	{

		xSemaphoreTake(Fan_Semaphore,MAX_TIME);

		if(Global_u8Operation_Flag == HOME_ENTERED)
		{

			xQueueReceive(Temp_Queue,(void*)&Local_u8Received,MAX_TIME);
			LCD_voidClearScreen();
			xSemaphoreTake(LCD_xMutex,MAX_TIME);

			if(Local_u8Received == 4 )
			{
				if( Global_u8RepEnter1 == SINGLE_ENTER)
				{
					xQueueReceive(Temp_Queue,(void*)&Local_u8Temp1Received,MAX_TIME);

					LCD_voidSetPosition(LCD_ROW0,LCD_COLUMN0);
					LCD_voidSendString((u8*)"Fan 1");

					if((Local_u8Temp1Received >= 14) && (Local_u8Temp1Received < 20) )
					{
						TIMER0_voidSetFastPWM(64);
						LCD_voidSetPosition(LCD_ROW1,LCD_COLUMN0);
						LCD_voidSendString((u8*)"Speed: LOW   ");
						Global_u8RepEnter1 = MULTIPLE_ENTER;
					}
					else if((Local_u8Temp1Received >= 20) && (Local_u8Temp1Received < 30) )
					{
						TIMER0_voidSetFastPWM(128);
						LCD_voidSetPosition(LCD_ROW1,LCD_COLUMN0);
						LCD_voidSendString((u8*)"Speed: MEDIUM");
						Global_u8RepEnter1 = MULTIPLE_ENTER;
					}
					else if((Local_u8Temp1Received >= 30)  )
					{
						TIMER0_voidSetFastPWM(255);
						LCD_voidSetPosition(LCD_ROW1,LCD_COLUMN0);
						LCD_voidSendString((u8*)"Speed: HIGH  ");
						Global_u8RepEnter1 = MULTIPLE_ENTER;

					}
					else
					{
						TIMER0_voidSetFastPWM(0);
						LCD_voidSetPosition(LCD_ROW1,LCD_COLUMN0);
						LCD_voidSendString((u8*)"Stopped      ");
						Global_u8RepEnter1 = MULTIPLE_ENTER;
					}
				}

			}
			else if(Local_u8Received == 5 )
			{
				if(Global_u8RepEnter2 == SINGLE_ENTER)
				{
					xQueueReceive(Temp_Queue,(void*)&Local_u8Temp2Received,MAX_TIME);
					LCD_voidSetPosition(LCD_ROW0,LCD_COLUMN0);
					LCD_voidSendString((u8*)"Fan 2");

					if((Local_u8Temp2Received >= 14) && (Local_u8Temp2Received < 20) )
					{
						TIMER2_voidSetFastPWM(64);
						LCD_voidSetPosition(LCD_ROW1,LCD_COLUMN0);
						LCD_voidSendString((u8*)"Speed: LOW  ");
						Global_u8RepEnter2 = MULTIPLE_ENTER;
					}
					else if((Local_u8Temp2Received >= 20) && (Local_u8Temp2Received < 30) )
					{
						TIMER2_voidSetFastPWM(128);
						LCD_voidSetPosition(LCD_ROW1,LCD_COLUMN0);
						LCD_voidSendString((u8*)"Speed: MEDIUM");
						Global_u8RepEnter2 = MULTIPLE_ENTER;
					}
					else if((Local_u8Temp2Received >= 30) && (Local_u8Temp2Received < 50) )
					{
						TIMER2_voidSetFastPWM(255);
						LCD_voidSetPosition(LCD_ROW1,LCD_COLUMN0);
						LCD_voidSendString((u8*)"Speed: HIGH  ");

						Global_u8RepEnter2 = MULTIPLE_ENTER;
					}
					else
					{
						TIMER2_voidSetFastPWM(0);
						LCD_voidSetPosition(LCD_ROW1,LCD_COLUMN0);
						LCD_voidSendString((u8*)"Stopped      ");
						Global_u8RepEnter2 = MULTIPLE_ENTER;
					}

				}

			}
			else
			{
				/*DO NOTHING*/
		}
		xSemaphoreGive(LCD_xMutex);
	}

}
}
