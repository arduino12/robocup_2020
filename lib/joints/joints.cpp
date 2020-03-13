#include "joints.h"

void Joints::begin(TwoWire *i2c_bus, uint8_t address)
{
	/* init PCA9685 - I2C to PWM expender */
	_pwm = Adafruit_PWMServoDriver(address);
	_pwm.begin();
	_pwm.setOscillatorFrequency(JOINTS_PWM_OSCILLATOR_FREQ);
	_pwm.setPWMFreq(JOINTS_PWM_FREQ);
	_pwm.setOutputMode(true);
}

void Joints::set_servo(uint8_t pin, uint16_t pos)
{
	_pwm.setPWM(pin, 0, pos);
}

void Joints::update(void)
{

}
