/*
 * joystick.h
 *
 *  Created on: 24 lut 2023
 *      Author: miqix
 */

#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

//	!NOTE!
//	To init the joystick you have to set your ADC separately
//	and pass pointers to measured values to joystick via init function


#define X_AXIS 0
#define Y_AXIS 1

typedef struct{
	uint16_t* ValX;	//pointers to tab where DMA is writing our pwm values
	uint16_t* ValY;
	uint16_t IdleX;
	uint16_t IdleY;
	int8_t DeviationX;
	int8_t DeviationY;
}Joystick_t;

typedef enum
{
  JOYS_OK       = 0x00,
  JOYS_ERROR    = 0x01,
  JOYS_BUSY     = 0x02,
  JOYS_TIMEOUT  = 0x03
} JOYS_StatusTypeDef;


JOYS_StatusTypeDef JoyS_Init(Joystick_t *Joystick, uint16_t *AdcValueSourceX, uint16_t *AdcValueSourceY);
JOYS_StatusTypeDef JoyS_SetIdleValues(Joystick_t *Joystick);
int8_t Joy_GetDeviationPercent(Joystick_t *Joystick, uint8_t axis);

#endif /* INC_JOYSTICK_H_ */
