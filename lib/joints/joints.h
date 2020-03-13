/*
 * joints.h - single brash motor class.
 * 
 * Libs:
 *   https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
 *
 * Arad Eizen 22/02/20.
 */
#ifndef JOINTS_H
#define JOINTS_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define JOINTS_PWM_FREQ					(50)
#define JOINTS_PWM_OSCILLATOR_FREQ		(27000000)

enum {
	JOINTS_LEFT_LEG_ROLL = 0,
	JOINTS_LEFT_LEG_PITCH,
	JOINTS_LEFT_LEG_PITCH_2,
	JOINTS_03,
	JOINTS_RIGHT_LEG_ROLL,
	JOINTS_RIGHT_LEG_PITCH,
	JOINTS_RIGHT_LEG_PITCH_2,
	JOINTS_06,
	JOINTS_LEFT_ARM_ROLL,
	JOINTS_LEFT_ARM_PITCH,
	JOINTS_LEFT_ARM_YAW,
	JOINTS_LEFT_ARM_PITCH_2,
	JOINTS_RIGHT_ARM_ROLL,
	JOINTS_RIGHT_ARM_PITCH,
	JOINTS_RIGHT_ARM_YAW,
	JOINTS_RIGHT_ARM_PITCH_2,
};

class Joints
{
public:
	void begin(TwoWire *i2c_bus, uint8_t address);
	void set_servo(uint8_t pin, uint16_t pos);

private:
	void update(void);
	Adafruit_PWMServoDriver _pwm;
};

#endif
