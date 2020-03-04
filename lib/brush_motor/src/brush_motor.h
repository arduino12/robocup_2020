/*
 * brush_motor.h - single brash motor class.
 * 
 * Libs:
 *   https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
 *
 * Arad Eizen 22/02/20.
 */
#ifndef BRUSH_MOTOR_H
#define BRUSH_MOTOR_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define RAMP_STEP_MS					(10)
#define PWM_MAX							(4095)
#define MAX_SPEED						(PWM_MAX)

enum {
    BM_DIR_STOP = 0,
    BM_DIR_FORWARD = 1,
    BM_DIR_BACKWARD = 2,
    BM_DIR_DISABLED = 3,
};


class BrushMotor
{
public:
	void begin(Adafruit_PWMServoDriver *pwm, uint8_t a_pin, uint8_t b_pin,
			uint8_t en_pin, uint8_t pwm_pin);
	void ramp_up(void);
	void ramp_down(void);
	void set_dir(uint8_t dir);
	void set_speed(uint16_t speed);
	void set_speed_with_dir(int16_t speed);
	void set_ramp_up_ms(uint16_t ramp_up_ms);
	void set_ramp_down_ms(uint16_t ramp_down_ms);

private:
	void update(void);
	void pwm_write_analog(uint8_t pin, uint16_t value);
	void pwm_write_digital(uint8_t pin, bool value);

	Adafruit_PWMServoDriver *_pwm = NULL;
	uint8_t _a_pin;
	uint8_t _b_pin;
	uint8_t _en_pin;
	uint8_t _pwm_pin;
	
	uint8_t _dir = BM_DIR_STOP;
	uint16_t _speed = PWM_MAX;
	uint16_t _ramp_up_ms = RAMP_STEP_MS;
	uint16_t _ramp_down_ms = RAMP_STEP_MS;
};

#endif
