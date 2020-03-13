/*
 * Bluetooth Omni test V1.
 * Use with Dabble app!
 * Moves the robot using the app joystick.
 * 
 * Arad Eizen 04/03/20.
 */
#ifndef _BT_CONTROL_H_
#define _BT_CONTROL_H_

#if defined(ARDUINO_ARCH_ESP32)

#include <DabbleESP32.h>
#include "robot.h"

#define DABBLE_NAME						"robocup2020!"
#define DABBLE_AXIS_MIN					(-7)
#define DABBLE_AXIS_MAX					(7)
#define BT_CONTROL_LOOP_MS				(10)

static uint16_t dabble_axis_to_speed(int8_t value)
{
	return map(value, DABBLE_AXIS_MIN, DABBLE_AXIS_MAX, -MAX_SPEED, MAX_SPEED);
}

void bt_control_begin()
{
	/* start bluetooth app server */
	Dabble.begin(DABBLE_NAME);

	/* print user instructions */
	Serial.printf("Bluetooth started!\t%s\n", DABBLE_NAME);
	Serial.println("    Go to smartphone Dabble app -> Gamepad -> Joystick Mode, and connect!");
}

void bt_control_loop()
{
	static uint32_t last_ms = 0;
	uint32_t cur_ms = millis();

	/* run our loop every BT_CONTROL_LOOP_MS milliseconds */
	if ((cur_ms - last_ms) < BT_CONTROL_LOOP_MS)
		return;
	last_ms = cur_ms;

	/* read joystick value from bluetooth app */
	Dabble.processInput();

	/* read joystick value from bluetooth app */
	int16_t x = dabble_axis_to_speed(GamePad.getx_axis());
	int16_t y = dabble_axis_to_speed(GamePad.gety_axis());
	int16_t r = 0;
	if (GamePad.isCirclePressed())
		r = MAX_SPEED / 2;
	else if (GamePad.isSquarePressed())
		r = -MAX_SPEED / 2;

	/* write x, y, r speeds to motors */
	if (r)
		omni.set_rotate_speed(r);
	else
		omni.set_xy_speeds(x, y);
}

#else
void bt_control_begin() { }
void bt_control_loop() { }
#endif

#endif
