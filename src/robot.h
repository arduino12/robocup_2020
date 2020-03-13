/*
 * Main robot logic.
 * 
 * Wiring:
 * 	pwm_module:
 *  	V+ - 5V
 *  	VCC - 5V
 * 		GND - GND
 * 		SDA - GPIO21
 * 		SCL - GPIO22
 * 		0 - left servo
 * 		1 - right servo
 * 
 * Arad Eizen 04/03/20.
 */
#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <Arduino.h>
#include <Wire.h>
#include "omni.h"
#include "joints.h"

#define I2C_SDA							(21)
#define I2C_SCK							(22)
#define I2C_CLOCK_HZ					(400000)

#define PWM_OMNI_ADDRESS				(0x40)
#define PWM_JOINTS_ADDRESS				(0x41)

Omni omni;
Joints joints;

void robot_begin()
{
	/* init I2C bus */
	Wire.setClock(I2C_CLOCK_HZ);

	/* init omni */
	omni.begin(&Wire, PWM_OMNI_ADDRESS);
	omni.set_speed(MAX_SPEED);    

	/* init joints */
	joints.begin(&Wire, PWM_JOINTS_ADDRESS);
}

void robot_loop()
{
	/* TODO: add ramp up/down logic here and remove delay() from motors.. */
}

#endif
