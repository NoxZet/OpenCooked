#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include "Graphics/Graphics2D.hpp"

static int run = 1;

void shutdownReset(unsigned int id, void *ptr) {
	run = 0;
}
void shutdown(void) {
	run = 0;
}

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------
	SYS_SetResetCallback(shutdownReset);
	SYS_SetPowerCallback(shutdown);

	// This function initialises the attached controllers
	WPAD_Init();
	
	

	
	// Setup Graphics controller
	Graphics::Graphics2D graphics = Graphics::Graphics2D();
	


	// Set cursor to row 2, column 0
	//printf("\x1b[2;0H");
	
	int counter = 0;
	
	while(run) {
		graphics.tick();

		//printf("\x1b[2;0H");
		//printf("counter: %d", counter);
		counter++;

		// Call WPAD_ScanPads each loop, this reads the latest controller states
		WPAD_ScanPads();

		// WPAD_ButtonsDown tells us which buttons were pressed in this loop
		// this is a "one shot" state which will not fire again until the button has been released
		u32 pressed = WPAD_ButtonsDown(0);

		// We return to the launcher application via exit
		if ( pressed & WPAD_BUTTON_HOME ) exit(0);
	}
	
	exit(0);

	return 0;
}
