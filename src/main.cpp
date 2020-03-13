/*
 * Dancing robot for the Robocup 2020 competition!
 * 	Motors:
 * 		4 wheels omni drive, 14 servo axis arms, 2 linear actuators.
 * 	Sensors:
 * 		Pixy2 camera module, MPU6050 gyroscope + accelerometer module.
 * 
 * Arad Eizen 22/02/20.
 */
#include <Arduino.h>
#include "robot.h"
#include "bt_control.h"
#include "pixy_control.h"


#define UART_BAUDRATE					(115200)


void setup()
{
	/* init UART debug */
	Serial.begin(UART_BAUDRATE);
	Serial.println("Started!");

	/* init robot motors */
	robot_begin();

	/* init pixy control */
	pixy_control_begin();

	/* init bluetooth control */
	bt_control_begin();
}

void loop()
{
	pixy_control_loop();
	bt_control_loop();
	robot_loop();
}
