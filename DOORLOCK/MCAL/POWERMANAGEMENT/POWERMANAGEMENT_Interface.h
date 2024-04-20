/*
 * POWERMANAGEMENT_Interface.h
 *
 *  Created on: 8 Apr 2024
 *      Author: User
 */

#ifndef MCAL_POWERMANAGEMENT_POWERMANAGEMENT_INTERFACE_H_
#define MCAL_POWERMANAGEMENT_POWERMANAGEMENT_INTERFACE_H_

#ifndef POWER_MANAGEMENT_H_
#define POWER_MANAGEMENT_H_


#define	IDLE_MODE  				0 //ALLOW SPI, USART, Analog Comparator, ADC, Two-wire SerialInterface, Timer/Counters, Watchdog, and the interrupt system to continue operating
#define	ADC_NR_MODE				1 //allowing the ADC, the External Interrupts, the Two-wire Serial Interface address watch, Timer/Counter2 and the Watchdog to continue operating (if enabled)
#define	PWR_DOWN_MODE			2 //External Oscillator is stopped, while the External interrupts, the Two-wire Serial Interface address watch, and the Watchdog continue operating (if enabled).
#define	PWR_SAVE_MODE			3
#define	RESERVED_MODE			4
#define	STANDBY_MODE			5
#define	EXT_STANDBY_MODE		6





void CPU_Sleep(void);
void Set_SleepMode(void);
void CPU_SleepEnable(void);
void CPU_SleepDisable(void);
void Change_SleepMode(u8 SleepMode);






#endif /* POWER_MANAGEMENT_H_ */


#endif /* MCAL_POWERMANAGEMENT_POWERMANAGEMENT_INTERFACE_H_ */
