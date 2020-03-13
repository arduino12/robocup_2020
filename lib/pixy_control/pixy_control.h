/*
 * Moves the robot legs by the Pixy2 object positions.
 * 
 * Needs to add 2 signatures to Pixy2 using the PixyMon.exe:
 *	  PixyMon.exe -> Action -> Set signature 1...
 *	  PixyMon.exe -> Action -> Set signature 2...
 * 
 * Wiring Pixy2 module to ESP32:
 * 		5V - 5V
 * 		GND - GND
 * 		SPI_SCK - GPIO18
 * 		SPI_MISO - GPIO19
 * 		SPI_MOSI - GPIO23
 * 
 * Arad Eizen 11/03/2020.
 */
#ifndef _PIXY_CONTROL_H_
#define _PIXY_CONTROL_H_

#include <Pixy2.h>
#include "robot.h"

#define PIXY_SCK_PIN					(18)
#define PIXY_MISO_PIN					(19)
#define PIXY_MOSI_PIN					(23)

#define BLOCK_SIG_LEFT					(1)
#define BLOCK_SIG_RIGHT					(2)
#define BLOCK_AGE_MIN					(5)
#define BLOCK_WIDTH_MIN					(20)
#define BLOCK_WIDTH_MAX					(80)
#define BLOCK_HEIGHT_MIN				(20)
#define BLOCK_HEIGHT_MAX				(80)

#define PIXY_CONTROL_LOOP_MS			(5)

typedef struct {
	uint8_t servo_pin;
	uint16_t servo_up_pos;
	uint16_t servo_down_pos;
	uint8_t block_sig;
	uint16_t block_x_min;
	uint16_t block_x_max;
} leg_t;

leg_t legs[] = {
	{JOINTS_LEFT_LEG_ROLL, 400, 100, BLOCK_SIG_LEFT, PIXY_WIDTH / 2, PIXY_WIDTH},
	{JOINTS_RIGHT_LEG_ROLL, 300, 600, BLOCK_SIG_RIGHT, 0, PIXY_WIDTH / 2},
	{0}
};

Pixy2 pixy;

void pixy_control_begin()
{
	pixy.init();
}

void pixy_control_loop()
{
	static leg_t *leg = legs;
	static uint32_t last_ms = 0;
	uint32_t cur_ms = millis();

	/* run our loop every BT_CONTROL_LOOP_MS milliseconds */
	if ((cur_ms - last_ms) < PIXY_CONTROL_LOOP_MS)
		return;
	last_ms = cur_ms;

	/* cheack each leg at a time */
	if (!++leg->block_sig)
		leg = legs;

	/* get a single block with matching sig */
	pixy.ccc.getBlocks(false, _BV(leg->block_sig - 1), 1);
	if (!pixy.ccc.numBlocks)
		return;
	Block *b = pixy.ccc.blocks;
	if (!b)
		return;
	b->print();

	/* check block limits */
	if (b->m_age < BLOCK_AGE_MIN)
		return;
	if (b->m_width < BLOCK_WIDTH_MIN || b->m_width > BLOCK_WIDTH_MAX)
		return;
	if (b->m_height < BLOCK_HEIGHT_MIN || b->m_height > BLOCK_HEIGHT_MAX)
		return;
	if (b->m_x < leg->block_x_min || b->m_x > leg->block_x_max)
		return;

	/* turn leg joint to match the block height */
	joints.set_servo(leg->servo_pin, map(b->m_y, 0, PIXY_HEIGHT, leg->servo_down_pos, leg->servo_up_pos));
}

#endif
