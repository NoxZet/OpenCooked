#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include "GameLogic/GameLogic.hpp"
#include "Physics/Physics.hpp"
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
	// WPAD_Init();
	
	
	// Setup main controllers
	GameLogic::GameLogic gameLogic = GameLogic::GameLogic();
	Physics::Physics graphics = Physics::Physics(&gameLogic);
	Graphics::Graphics2D graphics = Graphics::Graphics2D(&gameLogic);
	gameLogic.init();
	
	int counter = 0;
	
	while (run) {
		gameLogic.tick();
		physics.tick();
		graphics.tick();

		counter++;

		// Call WPAD_ScanPads each loop, this reads the latest controller states
		// WPAD_ScanPads();

		// WPAD_ButtonsDown tells us which buttons were pressed in this loop
		// this is a "one shot" state which will not fire again until the button has been released
		// u32 pressed = WPAD_ButtonsDown(0);

		// We return to the launcher application via exit
		// if ( pressed & WPAD_BUTTON_HOME ) exit(0);
	}
	
	exit(0);

	return 0;
}
