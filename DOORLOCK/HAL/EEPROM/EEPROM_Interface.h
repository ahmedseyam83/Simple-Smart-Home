/*
 * EEPROM_Interface.h
 *
 *  Created on: Apr 4, 2024
 *      Author: Ibrahim
 */

#ifndef HAL_EEPROM_EEPROM_INTERFACE_H_
#define HAL_EEPROM_EEPROM_INTERFACE_H_


void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte);

u8 EEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress);



#endif /* HAL_EEPROM_EEPROM_INTERFACE_H_ */
