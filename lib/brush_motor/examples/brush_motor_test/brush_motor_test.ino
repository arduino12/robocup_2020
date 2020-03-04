/*
 * Brush motors test V1.
 * Test VNH3SP30 motor driver using PCA9685 I2C to PWM expender.
 * 
 * Libs:
 *   https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
 *
 * Arad Eizen 22/02/20.
 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <brush_motor.h>


#define UART_BAUDRATE					(115200)
#define I2C_CLOCK_HZ					(400000)
#define PWM_BM0_BM4_ADDRESS				(0x40)
#define PWM_OSCILLATOR_FREQ				(27000000)
#define PWM_FREQ						(500)
#define PWM_MAX							(4095)
#define MOTOR_B00_A_PIN					(11)
#define MOTOR_B00_B_PIN					(15)
#define MOTOR_B00_EN_PIN				(3)
#define MOTOR_B00_PWM_PIN				(7)
#define MOTOR_B01_A_PIN					(10)
#define MOTOR_B01_B_PIN					(14)
#define MOTOR_B01_EN_PIN				(2)
#define MOTOR_B02_PWM_PIN				(6)
#define MOTOR_B02_A_PIN					(9)
#define MOTOR_B02_B_PIN					(13)
#define MOTOR_B02_EN_PIN				(1)
#define MOTOR_B03_PWM_PIN				(5)
#define MOTOR_B03_A_PIN					(8)
#define MOTOR_B03_B_PIN					(12)
#define MOTOR_B03_EN_PIN				(0)
#define MOTOR_B03_PWM_PIN				(4)
#define MOTOR_RAMP_MS					(1000)


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PWM_BM0_BM4_ADDRESS);
BrushMotor brush_motor;


void setup()
{
	/* init UART debug */
	Serial.begin(UART_BAUDRATE);
	Serial.println("Started!");
	
	/* init PCA9685 - I2C to PWM expender */
	Wire.setClock(I2C_CLOCK_HZ);
	pwm.begin();
	pwm.setOscillatorFrequency(PWM_OSCILLATOR_FREQ);
	pwm.setPWMFreq(PWM_FREQ);
	pwm.setOutputMode(true);

	/* init brush_motor */
	brush_motor.begin(&pwm, MOTOR_B00_A_PIN, MOTOR_B00_B_PIN, MOTOR_B00_EN_PIN,
			MOTOR_B00_PWM_PIN);
	brush_motor.set_speed(MAX_SPEED);
	brush_motor.set_ramp_up_ms(MOTOR_RAMP_MS);
	brush_motor.set_ramp_down_ms(MOTOR_RAMP_MS);
}

void test_dir()
{
	Serial.println("Forward!");
	brush_motor.set_dir(BM_DIR_FORWARD);
	delay(1000);
	Serial.println("Backward!");
	brush_motor.set_dir(BM_DIR_BACKWARD);
	delay(1000);
}

void test_ramp()
{
	Serial.println("Forward!");
	brush_motor.set_dir(BM_DIR_FORWARD);
	brush_motor.ramp_up();
	brush_motor.ramp_down();

	Serial.println("Backward!");
	brush_motor.set_dir(BM_DIR_BACKWARD);
	brush_motor.ramp_up();
	brush_motor.ramp_down();
}

void loop()
{
	test_ramp();
	// test_dir();
}
