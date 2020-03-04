/*
 * 4x4 Omni test V1.
 * Test VNH3SP30 motor driver using PCA9685 I2C to PWM expender.
 * Moves the robot in a square pattern.
 * 
 * Libs:
 *   https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
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

	delay(10);
}
