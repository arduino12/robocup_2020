#include "brush_motor.h"


void BrushMotor::begin(Adafruit_PWMServoDriver *pwm, uint8_t a_pin,
		uint8_t b_pin, uint8_t en_pin, uint8_t pwm_pin)
{
	_pwm = pwm;
	_a_pin = a_pin;
	_b_pin = b_pin;
	_en_pin = en_pin;
	_pwm_pin = pwm_pin;

	update();
}

void BrushMotor::update(void)
{
	pwm_write_digital(_a_pin, _dir == BM_DIR_FORWARD);
	pwm_write_digital(_b_pin, _dir == BM_DIR_BACKWARD);
	pwm_write_digital(_en_pin, _dir != BM_DIR_DISABLED);
	pwm_write_analog(_pwm_pin, _speed);
}

void BrushMotor::set_dir(uint8_t dir)
{
	_dir = dir;
	update();
}

void BrushMotor::ramp_up(void)
{
	uint16_t speed = _speed;
	uint16_t steps = speed / (_ramp_up_ms / RAMP_STEP_MS);
	
	for (int16_t i = 0; i < speed; i += steps) {
		set_speed(i);
		delay(RAMP_STEP_MS);
	}
	
	set_speed(speed);
}

void BrushMotor::ramp_down(void)
{
	uint16_t speed = _speed;
	uint16_t steps = speed / (_ramp_up_ms / RAMP_STEP_MS);
	
	for (int16_t i = speed; i > 0; i -= steps) {
		set_speed(i);
		delay(RAMP_STEP_MS);
	}

	set_dir(BM_DIR_STOP);
	set_speed(speed);
}

void BrushMotor::set_speed(uint16_t speed)
{
	if (speed > MAX_SPEED)
		speed = MAX_SPEED;

	_speed = speed;

	update();
}

void BrushMotor::set_speed_with_dir(int16_t speed)
{
	speed = constrain(speed, -MAX_SPEED, MAX_SPEED);
	_dir = (speed >= 0);
	_speed = abs(speed);
	update();
}

void BrushMotor::set_ramp_up_ms(uint16_t ramp_up_ms)
{
	if (ramp_up_ms)
		_ramp_up_ms = ramp_up_ms;
}

void BrushMotor::set_ramp_down_ms(uint16_t ramp_down_ms)
{
	if (ramp_down_ms)
		_ramp_down_ms = ramp_down_ms;
}

void BrushMotor::pwm_write_analog(uint8_t pin, uint16_t value)
{
	_pwm->setPWM(pin, 0, value);
}

void BrushMotor::pwm_write_digital(uint8_t pin, bool value)
{
	pwm_write_analog(pin, value ? PWM_MAX : 0);
}
