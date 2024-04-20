/*
 * SystemControl.h
 *
 *  Created on: 16 Apr 2024
 *      Author: User
 */

#ifndef SYSTEMCONTROL_SYSTEMCONTROL_INTERFACE_H_
#define SYSTEMCONTROL_SYSTEMCONTROL_INTERFACE_H_


/*****************Macros*********************/




/********************FUNCTIONS PROTOTYPES********************************/

void Keypad_Task(void *ptr);
void PW_Set(void *ptr);
void PW_Enter(void *ptr);
void PW_Check(void *ptr);
void PW_Action(void *ptr);


#endif /* SYSTEMCONTROL_SYSTEMCONTROL_INTERFACE_H_ */
