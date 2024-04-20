/*
 * USART_Config.h
 *
 *  Created on: 1 Apr 2024
 *      Author: User
 */

#ifndef MCAL_USART_USART_CONFIG_H_
#define MCAL_USART_USART_CONFIG_H_


/* Set System Frequency*/
#define SYSTEM_FREQUENCY			8000000UL

/* Set Baud Rate */
#define USART_BAUD_RATE				9600UL

/* Set System Mode
 * 1. ASYNCHRONOUS
 * 2. SYNCHRONOUS
 * */
#define USART_MODE 					ASYNCHRONOUS

/* Set System Speed
 * 1. USART_X1
 * 2. USART_X2
 * */
#define USART_SYSTEM_SPEED				USART_X1

/* Set Timeout for your function */
#define USART_TIMEOUT					10000

/* Set Data packet size
 * 1. DATA_SIZE_5_BIT
 * 2. DATA_SIZE_6_BIT
 * 3. DATA_SIZE_7_BIT
 * 4. DATA_SIZE_8_BIT
 * 5. DATA_SIZE_9_BIT
 */
#define USART_DATA_SIZE					DATA_SIZE_8_BIT

/* Set Multi_processor Mode
 * 1. ENABLE
 * 2. DISABLE
 * */
#define USART_MPCM 						DISABLE

/* Set Receiver Enable)
 * 1. ENABLE
 * 2. DISABLE
 */
#define USART_RECEIVER_ENABLE			ENABLE

/* Set Transmitter Enable)
 * 1. ENABLE
 * 2. DISABLE
 */
#define USART_TRANSMITTER_ENABLE			ENABLE



/* Set Parity Mode
 * 1. DISABLE
 * 2. EVEN_PARITY
 * 3. ODD_PARITY
 */
#define USART_PARITY_MODE				DISABLE

/* Set Stop Bits
 * 1. STOP_BIT_1
 * 2. STOP_BIT_2
 */
#define USART_STOP_BIT					STOP_BIT_1

/* Set Clock Polarity (Synchronous mode only)
 * 1. XCK_RISING_TX_XCH_FALLING_RX
 * 2. XCK_RISING_RX_XCH_FALLING_TX
 */
#define USART_CLOCK_POLARITY			XCK_RISING_TX_XCH_FALLING_RX

/* Set RX Complete Interrupt Enable)
 * 1. ENABLE
 * 2. DISABLE
 */
#define USART_RX_COMPLETE_INTERRUPT		DISABLE

/* Set TX Complete Interrupt Enable)
 * 1. ENABLE
 * 2. DISABLE
 */
#define USART_TX_COMPLETE_INTERRUPT		ENABLE

/* Set UDR EMPTY Interrupt Enable)
 * 1. ENABLE
 * 2. DISABLE
 */
#define USART_UDR_EMPTY_INTERRUPT		DISABLE


#endif /* MCAL_USART_USART_CONFIG_H_ */
