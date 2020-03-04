/*
 * Main robot logic.
 * 
 * Arad Eizen 04/03/20.
 */
#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <Arduino.h>
#include <Wire.h>
#include <omni.h>

#define I2C_CLOCK_HZ					(400000)
#define PWM_OMNI_ADDRESS				(0x40)

Omni omni;

void robot_begin()
{
	/* init I2C bus */
	Wire.setClock(I2C_CLOCK_HZ);

	/* init omni, half speed */
	omni.begin(&Wire, PWM_OMNI_ADDRESS);
	omni.set_speed(MAX_SPEED / 2);    
}

void robot_loop()
{
	/* TODO: add ramp up/down logic here and remove delay() from motors.. */
}

#endif
