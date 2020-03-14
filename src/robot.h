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

#define I2C_SDA_PIN						(21) // 32
#define I2C_SCL_PIN						(22) // 33
#define I2C_SPEED						(400000)
#define I2C_CHANNEL						(0)

#define PWM_OMNI_ADDRESS				(0x40)
#define PWM_JOINTS_ADDRESS				(0x41)

Omni omni;
Joints joints;
TwoWire *i2c_motors;

void robot_begin()
{
	/* init I2C bus */
#if defined(ARDUINO_ARCH_ESP32)
	i2c_motors = new TwoWire(I2C_CHANNEL);
	i2c_motors->begin(I2C_SDA_PIN, I2C_SCL_PIN, I2C_SPEED);
#else
	i2c_motors = &Wire;
	i2c_motors->setClock(I2C_SPEED);
#endif

	/* init omni */
	omni.begin(i2c_motors, PWM_OMNI_ADDRESS);

	/* init joints */
	joints.begin(i2c_motors, PWM_JOINTS_ADDRESS);
}

void robot_loop()
{
	/* TODO: add ramp up/down logic here and remove delay() from motors.. */
}

#endif
