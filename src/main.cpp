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
#include <Wire.h>
#include <omni.h>


#define UART_BAUDRATE					(115200)
#define I2C_CLOCK_HZ					(400000)
#define PWM_OMNI_ADDRESS				(0x40)

Omni omni;


void setup()
{
	/* init UART debug */
	Serial.begin(UART_BAUDRATE);
	Serial.println("Started!");

	/* init I2C bus */
	Wire.setClock(I2C_CLOCK_HZ);

	/* init omni, half speed */
	omni.begin(&Wire, PWM_OMNI_ADDRESS);
	omni.set_max_speed(PWM_MAX / 2);
}

void test_move()
{
	const uint16_t MOVE_MS = 1000;

	Serial.println("Forward!");
	omni.move(OMNI_DIR_FORWARD, MOVE_MS);
	Serial.println("Right!");
	omni.move(OMNI_DIR_RIGHT, MOVE_MS);
	Serial.println("Backward!");
	omni.move(OMNI_DIR_BACKWARD, MOVE_MS);
	Serial.println("Left!");
	omni.move(OMNI_DIR_LEFT, MOVE_MS);
	Serial.println("Clockwise!");
	omni.move(OMNI_DIR_CLOCKWISE, MOVE_MS);
	Serial.println("Anticlockwise!");
	omni.move(OMNI_DIR_ANTICLOCKWISE, MOVE_MS);
	Serial.println("Stop!");
	omni.move(OMNI_DIR_STOP, MOVE_MS);
}

void test_move_ramp()
{
	const uint16_t MOVE_MS = 1000;

	Serial.println("Ramp Forward!");
	omni.move_ramp(OMNI_DIR_FORWARD, MOVE_MS);
	Serial.println("Ramp Right!");
	omni.move_ramp(OMNI_DIR_RIGHT, MOVE_MS);
	Serial.println("Ramp Backward!");
	omni.move_ramp(OMNI_DIR_BACKWARD, MOVE_MS);
	Serial.println("Ramp Left!");
	omni.move_ramp(OMNI_DIR_LEFT, MOVE_MS);
	Serial.println("Ramp Clockwise!");
	omni.move_ramp(OMNI_DIR_CLOCKWISE, MOVE_MS);
	Serial.println("Ramp Anticlockwise!");
	omni.move_ramp(OMNI_DIR_ANTICLOCKWISE, MOVE_MS);
}

void loop()
{
	test_move_ramp();
	test_move();
}
