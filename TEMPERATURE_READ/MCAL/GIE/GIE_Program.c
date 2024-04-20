
#include "../../LIB/BIT_Math.h"
#include "../../LIB/Std_Types.h"



#include "GIE_Config.h"
#include "GIE_Private.h"
#include "GIE_Interface.h"


void GIE_voidEnable(void)
{
	SET_BIT(SREG,SREG_I_BIT);
}
void GIE_voidDisable(void)
{
	CLR_BIT(SREG,SREG_I_BIT);
}
