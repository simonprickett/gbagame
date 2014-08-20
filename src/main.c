/*
 *
 * GameBoy Advance Game
 * Simon Prickett
 *
 */

#include "gba.h"
#include "gbakeys.h"
#include "screenmode.h"

/*
 *
 * Front and back video buffers, and track which is current
 *
 */
u16* frontBuffer = (u16*)0x6000000;
u16* backBuffer = (u16*)0x600A000;
u16* videoBuffer;

/*
 *
 * Watch for where the screen drawing is
 *
 */
volatile u16* scanLineCounter = (volatile u16*)0x4000006;

/*
 *
 * Set pixel as x, y to color c
 *
 */
void drawPixel(int x, int y, unsigned short int c)
{
	videoBuffer[(y) *120 + (x)] = (c);
}

/*
 *
 * Flip between the two screen buffers
 *
 */
void flipBuffer(void) {
	if(REG_DISPCNT & BACKBUFFER) {
		// Back buffer is active so switch to front buffer
		REG_DISPCNT &= ~BACKBUFFER;
		videoBuffer = backBuffer;
    } else {
		// Front buffer is active so switch to back buffer
		REG_DISPCNT |= BACKBUFFER;
		videoBuffer = frontBuffer;
	}
}

/*
 *
 * Clear the screen (mode 4)
 *
 */
void clearScreen(void) {
	int x;
	int y;

	for(y = 0; y < 160; y++) {
		for(x = 0; x < 120; x++) {
			drawPixel(x, y, 0x0000);
		}
	}
	waitForVerticalBlank();
	flipBuffer();
}

/*
 *
 * Wait for the Start key to be pressed
 *
 */
void waitForStartKey(void)
{
	while (1) // loops infinitely till they press start
		if (!((*KEYS) & KEY_START)) {
			return;
	}
}

/*
 *
 * Wait for the vertical blank period
 *
 */
void waitForVerticalBlank(void)
{
	while(*scanLineCounter < 160) {
		// Keep waiting and do nothing
	}
}

 /*
  *
  * Entry point
  *
  */

int main(void) {
	// Run in screen mode 4
	setScreenMode(MODE_4 | BG2_ENABLE);
}

