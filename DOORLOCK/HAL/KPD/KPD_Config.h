#ifndef HAL_KPD_KPD_CONFIG_H_
#define HAL_KPD_KPD_CONFIG_H_



char KPD_u8Buttons[4][4]= { {'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'?','0','=','+'} };


#define KPD_ROW_INIT	DIO_PIN4
#define KPD_ROW_END		DIO_PIN7

#define	KPD_COL_INIT	DIO_PIN0
#define	KPD_COL_END		DIO_PIN3

#define KPD_PORT		DIO_PORTA

#define KPD_R0			DIO_PIN4
#define KPD_R1			DIO_PIN5
#define KPD_R2			DIO_PIN6
#define KPD_R3			DIO_PIN7

#define KPD_C0			DIO_PIN0
#define KPD_C1			DIO_PIN1
#define KPD_C2			DIO_PIN2
#define KPD_C3			DIO_PIN3




#endif /* HAL_KPD_KPD_CONFIG_H_ */
