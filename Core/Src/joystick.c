/*
 * joystick.c
 *
 *  Created on: 24 lut 2023
 *      Author: miqix
 */

#include "main.h"
#include "joystick.h"

//Use after starting ADC
JOYS_StatusTypeDef JoyS_Init(Joystick_t *Joystick, uint16_t *AdcValueSourceX, uint16_t *AdcValueSourceY)
{
	if(AdcValueSourceX || AdcValueSourceX)
	{
		Joystick->ValX = AdcValueSourceX;
		Joystick->ValY = AdcValueSourceY;
		return JOYS_OK;
	}
	return JOYS_ERROR;
}

//When this function is called, joystick must be in idle position
JOYS_StatusTypeDef JoyS_SetIdleValues(Joystick_t *Joystick)
{
	uint32_t tick = HAL_GetTick();
	while( (HAL_GetTick() - tick) < 100)
	{
		if( ( *(Joystick->ValX) != 0) || ( *(Joystick->ValY) ) != 0 )
		{
			Joystick->IdleX = *(Joystick->ValX);
			Joystick->IdleY = *(Joystick->ValY);
			return JOYS_OK;
		}
	}
	return JOYS_TIMEOUT;
}

int8_t Joy_GetDeviationPercent(Joystick_t *Joystick, uint8_t axis)
{
	int32_t Deviation;
	uint32_t CurrentValue;
	uint32_t IdleValue;

	if(axis == X_AXIS)
	{
		CurrentValue = *(Joystick->ValX);
		IdleValue = Joystick->IdleX;
	}
	else if(axis == Y_AXIS)
	{
		CurrentValue = *(Joystick->ValY);
		IdleValue = Joystick->IdleY;
	}
	else return 0;


	Deviation = CurrentValue - IdleValue;					//value of deviation (from idle value)
	if(Deviation >= 0)
	{
		return ( Deviation * 100) / (4095 - IdleValue);		//formula for positive deviation percentage
	}
	else
	{
		return - (100-( (CurrentValue * 100) / IdleValue ));	//formula for negative deviation percentage
	}

}


