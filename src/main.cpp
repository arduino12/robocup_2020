/*
 * 4x4 Omni wheels based robot.
 *
 * Connections:
 *  ________________________________
 * | Arduino	| ESP32	| PWM_BOARD	|
 * |____________|_______|___________|
 * | GND		| GND	| GND		|
 * |____________|_______|___________|
 * | A4			| 33	| SDA		|
 * |____________|_______|___________|
 * | A5			| 32	| SCL		|
 * |____________|_______|___________|
 * 
 * Arad Eizen 22/02/20.
 */
#include <Arduino.h>
#include "robot.h"
#if defined(ARDUINO_ARCH_ESP32)
	#include "bt_control.h"
#endif

#define UART_BAUDRATE					(115200)


void setup()
{
	/* init UART debug */
	Serial.begin(UART_BAUDRATE);
	Serial.println("Started!");

	/* init robot */
	robot_begin();

#if defined(ARDUINO_ARCH_ESP32)
	/* init bluetooth control */
	bt_control_begin();
#endif
}

void loop()
{
#if defined(ARDUINO_ARCH_ESP32)
	bt_control_loop();
#endif
	robot_loop();
}
