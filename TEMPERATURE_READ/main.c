
/******************LIB ***********************/
#include "LIB/BIT_Math.h"
#include "LIB/Std_Types.h"



/******************MCAL**********************/
#include "MCAL/GIE/GIE_Interface.h"
#include "MCAL/SPI/SPI_Interface.h"
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/ADC/ADC_Interface.h"
#include "MCAL/EXTI/EXTI_Interface.h"
#include "MCAL/POWERMANAGEMENT/POWERMANAGEMENT_Interface.h"


/*******************HAL*************************/
#include "HAL/LM35/LM35_Interface.h"

/*****************OS***********************/
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/semphr.h"

#define MAX_TIME 0xffff

#define TEMP1_READ				1
#define TEMP1_UNREAD			0

#define TEMP2_READ				2
#define TEMP2_UNREAD			3

xQueueHandle TempState_Queue;


void SPI_Task(void *ptr);
void TempRead_Task(void *ptr);

s32 main(void)
{

	GIE_voidEnable();
	EXTI_voidInit();

	/*POWER ON PIN*/
	DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN4,DIO_PIN_INPUT);
	CPU_Sleep();

	DIO_u8SetPinDirection(DIO_PORTA, DIO_PIN0, DIO_PIN_INPUT);
	DIO_u8SetPinDirection(DIO_PORTA, DIO_PIN1, DIO_PIN_INPUT);




	DIO_u8SetPinDirection(DIO_PORTB, DIO_PIN4, DIO_PIN_INPUT);
	DIO_u8SetPinDirection(DIO_PORTB, DIO_PIN5, DIO_PIN_INPUT);
	DIO_u8SetPinDirection(DIO_PORTB, DIO_PIN6, DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PORTB, DIO_PIN7, DIO_PIN_INPUT);

	DIO_u8SetPinDirection(DIO_PORTC,DIO_PIN0,DIO_PIN_OUTPUT);

	SPI_VoidInit();
	LM35_voidInit();

	TempState_Queue= xQueueCreate(1,sizeof(u16));
	xTaskCreate(&SPI_Task,NULL,250,NULL,1,NULL);
	xTaskCreate(&TempRead_Task,NULL,250,NULL,2,NULL);
	vTaskStartScheduler();


	while(1);

	return 0;
}

void SPI_Task(void *ptr)
{
	u8 Local_u8ReceivedValue = 0,Local_DummySent=0xff;

	while(1)
	{
		SPI_u8Tranceive(Local_DummySent,&Local_u8ReceivedValue);
		xQueueSend(TempState_Queue,(void*)&Local_u8ReceivedValue,0);
	}
}

void TempRead_Task(void *ptr)
{
	u8 Local_u8ReceivedValue = 0,Local_DummyReceived=0xff;
	u8 Local_u8TempValue1=0,Local_u8TempValue2=0 ;
	while(1)
	{
		xQueueReceive(TempState_Queue,(void*)&Local_u8ReceivedValue,MAX_TIME);
		if(Local_u8ReceivedValue == TEMP1_READ)
		{
			Local_u8TempValue1 = LM35_u16GetTempReading(CHANNEL0);
			SPI_u8Tranceive(Local_u8TempValue1,&Local_DummyReceived);
		}
		else if(Local_u8ReceivedValue == TEMP2_READ)
		{
			Local_u8TempValue2 = LM35_u16GetTempReading(CHANNEL1);
			SPI_u8Tranceive(Local_u8TempValue2,&Local_DummyReceived);
		}
		Local_u8ReceivedValue=0;
	}

}

