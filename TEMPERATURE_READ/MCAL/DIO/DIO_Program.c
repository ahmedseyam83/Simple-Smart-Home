/***************************** File Inclusion *****************************************************/
/*************** Library Inclusions ***************/

#include "../../LIB/BIT_Math.h"



#include "DIO_Config.h"
#include "DIO_Private.h"
#include "DIO_Interface.h"

/********************************** FUNCTION Implementation ****************************************/
ReturnType_State_t DIO_u8SetPortValue(u8 copy_u8Port , u8 copy_u8Value)
{
	ReturnType_State_t Local_u8State = E_OK;
	switch(copy_u8Port){
	case DIO_PORTA:
		PORTA = copy_u8Value;
	break;
	case DIO_PORTB:
		PORTB = copy_u8Value;
	break;
	case DIO_PORTC:
		PORTC = copy_u8Value;
	break;
	case DIO_PORTD:
		PORTD = copy_u8Value;
	break;
	default:
		Local_u8State = E_NOK;
		break;
	}
	return Local_u8State;
}

ReturnType_State_t DIO_u8SetPortDirection(u8 copy_u8Port , u8 copy_u8Direction)
{
	ReturnType_State_t Local_u8State = E_OK;
	switch(copy_u8Port){
	case DIO_PORTA:
		DDRA = copy_u8Direction;
	break;
	case DIO_PORTB:
		DDRB = copy_u8Direction;
	break;
	case DIO_PORTC:
		DDRC = copy_u8Direction;
	break;
	case DIO_PORTD:
		DDRD = copy_u8Direction;
	break;
	default:
		Local_u8State = E_NOK;
		break;
	}
	return Local_u8State;
}

ReturnType_State_t DIO_u8GetPortValue(u8 copy_u8Port , u8 *copy_u8Variable)
{
	ReturnType_State_t Local_u8State = E_OK;
	if(copy_u8Variable != NULL)
	{
		switch(copy_u8Port){
		case DIO_PORTA:
			*copy_u8Variable = PINA;
		break;
		case DIO_PORTB:
			*copy_u8Variable = PINB;
		break;
		case DIO_PORTC:
			*copy_u8Variable = PINC;
		break;
		case DIO_PORTD:
			*copy_u8Variable = PIND;
		break;
		default:
			Local_u8State = E_NOK;
			break;
		}
	}
	else
	{
		Local_u8State = E_NOK_NULL_PTR;
	}
	return Local_u8State;
}

ReturnType_State_t DIO_u8SetPinValue(u8 copy_u8Port , u8 copy_u8Pin , u8 copy_u8Value)
{
	ReturnType_State_t Local_u8State = E_OK;

	if((copy_u8Pin >= DIO_PIN0) && (copy_u8Pin <= DIO_PIN7))
	{
		if(copy_u8Value == DIO_PIN_LOW)
		{
			switch(copy_u8Port)
			{
			case DIO_PORTA:
				CLR_BIT(PORTA,copy_u8Pin);
			break;
			case DIO_PORTB:
				CLR_BIT(PORTB,copy_u8Pin);
			break;
			case DIO_PORTC:
				CLR_BIT(PORTC,copy_u8Pin);
			break;
			case DIO_PORTD:
				CLR_BIT(PORTD,copy_u8Pin);
			break;
			default:
			Local_u8State = E_NOK;
			break;
			}
		}
		else if(copy_u8Value == DIO_PIN_HIGH)
		{
			switch(copy_u8Port)
			{
			case DIO_PORTA:
				SET_BIT(PORTA,copy_u8Pin);
			break;
			case DIO_PORTB:
				SET_BIT(PORTB,copy_u8Pin);
			break;
			case DIO_PORTC:
				SET_BIT(PORTC,copy_u8Pin);
			break;
			case DIO_PORTD:
				SET_BIT(PORTD,copy_u8Pin);
			break;
			default:
			Local_u8State = E_NOK;
			break;
			}
		}
	}
	else
	{
		Local_u8State = E_NOK;
	}
	return Local_u8State;
}

ReturnType_State_t DIO_u8SetPinDirection(u8 copy_u8Port , u8 copy_u8Pin , u8 copy_u8Direction)
{
	ReturnType_State_t Local_u8State = E_OK;

	if((copy_u8Pin >= DIO_PIN0) && (copy_u8Pin <= DIO_PIN7))
	{
		if(copy_u8Direction == DIO_PIN_INPUT)
		{
			switch(copy_u8Port)
			{
			case DIO_PORTA:
				CLR_BIT(DDRA,copy_u8Pin);
			break;
			case DIO_PORTB:
				CLR_BIT(DDRB,copy_u8Pin);
			break;
			case DIO_PORTC:
				CLR_BIT(DDRC,copy_u8Pin);
			break;
			case DIO_PORTD:
				CLR_BIT(DDRD,copy_u8Pin);
			break;
			default:
			Local_u8State = E_NOK;
			break;
			}
		}
		else if(copy_u8Direction == DIO_PIN_OUTPUT)
		{
			switch(copy_u8Port)
			{
			case DIO_PORTA:
				SET_BIT(DDRA,copy_u8Pin);
			break;
			case DIO_PORTB:
				SET_BIT(DDRB,copy_u8Pin);
			break;
			case DIO_PORTC:
				SET_BIT(DDRC,copy_u8Pin);
			break;
			case DIO_PORTD:
				SET_BIT(DDRD,copy_u8Pin);
			break;
			default:
			Local_u8State = E_NOK;
			break;
			}
		}
	}
	else
	{
		Local_u8State = E_NOK;
	}
	return Local_u8State;
}

ReturnType_State_t DIO_u8GetPinValue(u8 copy_u8Port , u8 copy_u8Pin , u8 *copy_u8Variable)
{
	ReturnType_State_t Local_u8State = E_OK;

	if((copy_u8Pin >= DIO_PIN0) && (copy_u8Pin <= DIO_PIN7))
	{
			switch(copy_u8Port)
			{
			case DIO_PORTA:
				*copy_u8Variable = GET_BIT(PINA,copy_u8Pin);
			break;
			case DIO_PORTB:
				*copy_u8Variable = GET_BIT(PINB,copy_u8Pin);
			break;
			case DIO_PORTC:
				*copy_u8Variable = GET_BIT(PINC,copy_u8Pin);
			break;
			case DIO_PORTD:
				*copy_u8Variable = GET_BIT(PIND,copy_u8Pin);
			break;
			default:
			Local_u8State = E_NOK;
			break;
			}
	}
	else
	{
		Local_u8State = E_NOK;
	}
	return Local_u8State;
}

ReturnType_State_t DIO_u8ConnectPullUP(u8 copy_u8Port , u8 copy_u8Pin , u8 copy_u8ConnectPullUp)
{
	ReturnType_State_t Local_u8State = E_OK;

	if((copy_u8Port <= DIO_PORTD) && (copy_u8Pin <= DIO_PIN7) )
	{
		CLR_BIT(SFIOR,PUD);
		switch(copy_u8Port)
		{
		case DIO_PORTA:
			if(copy_u8ConnectPullUp == DIO_PIN_HIGH)
			{
				CLR_BIT(DDRA,copy_u8Pin);
				SET_BIT(PORTA,copy_u8Pin);
			}
			else
			{
				CLR_BIT(PORTA,copy_u8Pin);
			}
		break;

		case DIO_PORTB:
			if(copy_u8ConnectPullUp == DIO_PIN_HIGH)
			{
				CLR_BIT(DDRB,copy_u8Pin);
				SET_BIT(PORTB,copy_u8Pin);
			}
			else
			{
				CLR_BIT(PORTB,copy_u8Pin);
			}
		break;

		case DIO_PORTC:
			if(copy_u8ConnectPullUp == DIO_PIN_HIGH)
			{
				CLR_BIT(DDRC,copy_u8Pin);
				SET_BIT(PORTC,copy_u8Pin);
			}
			else
			{
				CLR_BIT(PORTC,copy_u8Pin);
			}
		break;

		case DIO_PORTD:
			if(copy_u8ConnectPullUp == DIO_PIN_HIGH)
			{
				CLR_BIT(DDRD,copy_u8Pin);
				SET_BIT(PORTD,copy_u8Pin);
			}
			else
			{
				CLR_BIT(PORTD,copy_u8Pin);
			}
		break;

		}
	}
	else
	{
		Local_u8State = E_NOK;
	}

	return Local_u8State;
}

ReturnType_State_t DIO_u8TogglePinValue(u8 copy_u8Port , u8 copy_u8Pin)
{
	ReturnType_State_t Local_u8State = E_OK;

	if((copy_u8Pin >= DIO_PIN0) && (copy_u8Pin <= DIO_PIN7))
	{
			switch(copy_u8Port)
			{
			case DIO_PORTA:
				TOG_BIT(PORTA,copy_u8Pin);
			break;
			case DIO_PORTB:
				TOG_BIT(PORTB,copy_u8Pin);
			break;
			case DIO_PORTC:
				TOG_BIT(PORTC,copy_u8Pin);
			break;
			case DIO_PORTD:
				TOG_BIT(PORTD,copy_u8Pin);
			break;
			default:
				Local_u8State = E_NOK;
			break;
			}
		}
		else
		{
			Local_u8State = E_NOK;
		}
		return Local_u8State;
}

