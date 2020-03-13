/*
 * omni.h - 4 Omni Wheel class.
 * 
 * Libs:
 *   https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
 *
 * Arad Eizen 22/02/20.
 */
#ifndef OMNI_H
#define OMNI_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <brush_motor.h>

#define OMNI_MOTOR_COUNT				(4)
#define OMNI_MOTOR_RAMP_MS				(1000)

#define OMNI_PWM_OSCILLATOR_FREQ		(27000000)
#define OMNI_PWM_FREQ					(200)
#define PWM_MAX							(4095)

enum {
    OMNI_DIR_STOP = 0,
    OMNI_DIR_FORWARD,
    OMNI_DIR_BACKWARD,
    OMNI_DIR_LEFT,
    OMNI_DIR_RIGHT,
    OMNI_DIR_CLOCKWISE,
    OMNI_DIR_ANTICLOCKWISE,
    OMNI_DIR_DISABLED,
};

const uint8_t omni_dirs[][OMNI_MOTOR_COUNT] = {
	/* left				front				right				back			*/
	{BM_DIR_STOP,		BM_DIR_STOP,		BM_DIR_STOP,		BM_DIR_STOP},		// OMNI_DIR_STOP
	{BM_DIR_FORWARD,	BM_DIR_STOP,		BM_DIR_BACKWARD,	BM_DIR_STOP},		// OMNI_DIR_FORWARD
	{BM_DIR_BACKWARD,	BM_DIR_STOP,		BM_DIR_FORWARD,		BM_DIR_STOP},		// OMNI_DIR_BACKWARD
	{BM_DIR_STOP,		BM_DIR_BACKWARD,	BM_DIR_STOP,		BM_DIR_FORWARD},	// OMNI_DIR_LEFT
	{BM_DIR_STOP,		BM_DIR_FORWARD,		BM_DIR_STOP,		BM_DIR_BACKWARD},	// OMNI_DIR_RIGHT
	{BM_DIR_FORWARD,	BM_DIR_FORWARD,		BM_DIR_FORWARD,		BM_DIR_FORWARD},	// OMNI_DIR_CLOCKWISE
	{BM_DIR_BACKWARD,	BM_DIR_BACKWARD,	BM_DIR_BACKWARD,	BM_DIR_BACKWARD},	// OMNI_DIR_ANTICLOCKWISE
	{BM_DIR_DISABLED,	BM_DIR_DISABLED,	BM_DIR_DISABLED,	BM_DIR_DISABLED},	// OMNI_DIR_DISABLED
};

class Omni
{
public:
	void begin(TwoWire *i2c_bus, uint8_t address);
	void set_dir(uint8_t dir);
	void ramp_up(void);
	void ramp_down(void);
	void move(uint8_t dir, uint16_t ms, bool hard_stop=true);
	void move_ramp(uint8_t dir, uint16_t ms);
	void set_speed(uint16_t speed);
	void set_ramp_up_ms(uint16_t ramp_up_ms);
	void set_ramp_down_ms(uint16_t ramp_down_ms);
	void set_xy_speeds(int16_t x_speed, int16_t y_speed);
	void set_rotate_speed(int16_t speed);

private:
	void update(void);

	Adafruit_PWMServoDriver _pwm;
	BrushMotor _brush_motors[OMNI_MOTOR_COUNT];

	uint8_t _dir = OMNI_DIR_STOP;
	uint16_t _speed = PWM_MAX;
	uint16_t _ramp_up_ms = OMNI_MOTOR_RAMP_MS;
	uint16_t _ramp_down_ms = OMNI_MOTOR_RAMP_MS;
};

#endif
