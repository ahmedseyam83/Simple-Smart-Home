
/******************LIB ***********************/
#include "LIB/BIT_Math.h"
#include "LIB/Std_Types.h"

#include <util/delay.h>

/******************MCAL**********************/
#include "MCAL/GIE/GIE_Interface.h"
#include "MCAL/EXTI/EXTI_Interface.h"
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/SPI/SPI_Interface.h"
#include "MCAL/USART/USART_Interface.h"
#include "MCAL/TIMERS/TIMERS_Interface.h"
#include "MCAL/POWERMANAGEMENT/POWERMANAGEMENT_Interface.h"
#include "SystemControl/SystemControl_interface.h"

/*****************HAL***********************/


#include "HAL/LCD/LCD_Interface.h"

/*****************OS***********************/
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/semphr.h"
#include "FreeRTOS/portable.h"


xTaskHandle xUART_Handle = NULL;
xSemaphoreHandle BTN1_Semaphore,BTN2_Semaphore,LCD_xMutex,Fan_Semaphore;
xQueueHandle Temp_Queue=NULL;



s32 main(void){



	GIE_voidEnable();
	EXTI_voidInit();

	/*POWER ON PIN*/
	DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN4,DIO_PIN_INPUT);
	CPU_Sleep();

	TIMER0_voidInit();
	TIMER2_voidInit();

	LCD_voidInit();

	USART_voidInit();


	/*****************************PIN INITIALISATION*********************************/

	/*BUTTON PINS*/
	DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN2,DIO_PIN_INPUT);
	DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN3,DIO_PIN_INPUT);



	/*DIO PINS*/
	DIO_u8SetPinDirection(DIO_PORTA,BUZZER_PIN,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PORTA,ALERT_LED_PIN,DIO_PIN_OUTPUT);

	/*FANS PINS*/
	DIO_u8SetPinDirection(FAN1_PORT,FAN1_PIN,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(FAN2_PORT,FAN2_PIN,DIO_PIN_OUTPUT);




	/*SPI PINS*/
	DIO_u8SetPinDirection(DIO_PORTB,DIO_PIN4,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PORTB,DIO_PIN5,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PORTB, DIO_PIN6, DIO_PIN_INPUT);
	DIO_u8SetPinDirection(DIO_PORTB,DIO_PIN7,DIO_PIN_OUTPUT);

	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW);
	SPI_VoidInit();

	vSemaphoreCreateBinary(BTN1_Semaphore);
	vSemaphoreCreateBinary(BTN2_Semaphore);
	vSemaphoreCreateBinary(LCD_xMutex);
	vSemaphoreCreateBinary(Fan_Semaphore);

	Temp_Queue = xQueueCreate(2,sizeof(u8));


	EXTI_u8INT0SetCallBack(Button_1);
	EXTI_u8INT1SetCallBack(Button_2);

	xTaskCreate(UART_TASK,NULL,50,NULL,3,&xUART_Handle);
	xTaskCreate(ROOM_1,NULL,250,NULL,2,NULL);
	xTaskCreate(ROOM_2,NULL,250,NULL,1,NULL);
	xTaskCreate(FAN,NULL,250,NULL,3,NULL);



	vTaskStartScheduler();

	while(1)
	{





	}


	return 0;
}


