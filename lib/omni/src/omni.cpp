#include "omni.h"

void Omni::begin(TwoWire *i2c_bus, uint8_t address)
{
	/* init PCA9685 - I2C to PWM expender */
	_pwm = Adafruit_PWMServoDriver(address, *i2c_bus);
	_pwm.begin();
	_pwm.setOscillatorFrequency(OMNI_PWM_OSCILLATOR_FREQ);
	_pwm.setPWMFreq(OMNI_PWM_FREQ);
	_pwm.setOutputMode(true);

	/* init brush motors */
	for (uint8_t i = 0; i < OMNI_MOTOR_COUNT; i++) {
		_brush_motors[i].begin(&_pwm, 8 + i, 12 + i, 0 + i, 4 + i);
		_brush_motors[i].set_speed(PWM_MAX);
		_brush_motors[i].set_ramp_up_ms(OMNI_MOTOR_RAMP_MS);
		_brush_motors[i].set_ramp_down_ms(OMNI_MOTOR_RAMP_MS);
	}

	update();
}

void Omni::update(void)
{

}

void Omni::set_dir(uint8_t dir)
{
	_dir = dir;

	for (uint8_t i = 0; i < OMNI_MOTOR_COUNT; i++)
		_brush_motors[i].set_dir(OMNI_DIRS[dir][i]);

	update();
}

void Omni::ramp_up(void)
{
	uint16_t speed = _speed;
	uint16_t steps = speed / (_ramp_up_ms / RAMP_STEP_MS);
	
	for (int16_t i = 0; i < speed; i += steps) {
		set_speed(i);
		delay(RAMP_STEP_MS);
	}
	
	set_speed(speed);
}

void Omni::ramp_down(void)
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

void Omni::move(uint8_t dir, uint16_t ms, bool hard_stop)
{
	set_dir(dir);

	if (dir == OMNI_DIR_STOP || dir == OMNI_DIR_DISABLED)
		return;

	delay(ms);
	set_dir(hard_stop ? OMNI_DIR_STOP : OMNI_DIR_DISABLED);
}

void Omni::move_ramp(uint8_t dir, uint16_t ms)
{
	set_dir(dir);

	if (dir == OMNI_DIR_STOP || dir == OMNI_DIR_DISABLED)
		return;

	ramp_up();
	delay(ms);
	ramp_down();
}

void Omni::set_speed(uint16_t speed)
{
	if (speed > PWM_MAX)
		speed = PWM_MAX;

	_speed = speed;

	for (uint8_t i = 0; i < OMNI_MOTOR_COUNT; i++)
		_brush_motors[i].set_speed(_speed);

	update();
}

void Omni::set_ramp_up_ms(uint16_t ramp_up_ms)
{
	if (ramp_up_ms)
		_ramp_up_ms = ramp_up_ms;
}

void Omni::set_ramp_down_ms(uint16_t ramp_down_ms)
{
	if (ramp_down_ms)
		_ramp_down_ms = ramp_down_ms;
}

void Omni::set_xy_speeds(int16_t x_speed, int16_t y_speed)
{
	_brush_motors[0].set_speed_with_dir(y_speed);
	_brush_motors[1].set_speed_with_dir(x_speed);
	_brush_motors[2].set_speed_with_dir(-y_speed);
	_brush_motors[3].set_speed_with_dir(-x_speed);
}

void Omni::set_rotate_speed(int16_t speed)
{
	_brush_motors[0].set_speed_with_dir(speed);
	_brush_motors[1].set_speed_with_dir(speed);
	_brush_motors[2].set_speed_with_dir(speed);
	_brush_motors[3].set_speed_with_dir(speed);
}
