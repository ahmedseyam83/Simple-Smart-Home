
/******************LIB ***********************/
#include "LIB/BIT_Math.h"
#include "LIB/Std_Types.h"

#include <util/delay.h>

/******************MCAL**********************/
#include "MCAL/GIE/GIE_Interface.h"
#include "MCAL/TWI/TWI_Interface.h"
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/USART/USART_Interface.h"

/*****************HAL***********************/
#include "HAL/KPD/KPD_Interface.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/EEPROM/EEPROM_Interface.h"

/****************Services*******************/
#include "SystemControl/SystemControl_Interface.h"

/*****************OS***********************/
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/semphr.h"


xTaskHandle xEnterHandle = NULL;
xTaskHandle xKeyHandle = NULL;


xSemaphoreHandle LCD_Mutex;
xSemaphoreHandle PW_CheckSemaphore;
xSemaphoreHandle PW_EnterSemaphore;




xQueueHandle PW_Queue;



s32 main(void){

	/********************************Periferals Initialisation**************************************/
	LCD_voidInit();
	USART_voidInit();

	KPD_Init();

	DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN4,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PORTC,DIO_PIN0,DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PORTC,DIO_PIN1,DIO_PIN_OUTPUT);
	TWI_voidInitMaster(0);

	vSemaphoreCreateBinary(LCD_Mutex);
	vSemaphoreCreateBinary(PW_CheckSemaphore);
	vSemaphoreCreateBinary(PW_EnterSemaphore);



	PW_Queue= xQueueCreate(1,sizeof(u16));


	xTaskCreate(&PW_Set,NULL,150,NULL,3,NULL);
	xTaskCreate(&Keypad_Task,NULL,50,NULL,3,&xKeyHandle);
	xTaskCreate(&PW_Enter,NULL,250,NULL,1,&xEnterHandle);
	xTaskCreate(&PW_Check,NULL,250,NULL,2,NULL);








	vTaskStartScheduler();

	/***************************************Operation Code******************************************/
		while(1)
		{

		}


	return 0;
}
