/*
 * SystemControl.h
 *
 *  Created on: 16 Apr 2024
 *      Author: User
 */

#ifndef SYSTEMCONTROL_SYSTEMCONTROL_INTERFACE_H_
#define SYSTEMCONTROL_SYSTEMCONTROL_INTERFACE_H_


/*****************Macros*********************/
#define BUZZER_PIN				DIO_PIN1
#define ALERT_LED_PIN			DIO_PIN0



#define FAN1_PORT				DIO_PORTB
#define FAN2_PORT				DIO_PORTD


#define FAN1_PIN				DIO_PIN3
#define FAN2_PIN				DIO_PIN7




/********************FUNCTIONS PROTOTYPES********************************/
void SemaphoreCreate(void);
void Button_1(void);
void Button_2(void);
void ROOM_1(void *ptr);
void ROOM_2(void *ptr);
void FAN(void *ptr);
void UART_TASK(void *ptr);



#endif /* SYSTEMCONTROL_SYSTEMCONTROL_INTERFACE_H_ */
