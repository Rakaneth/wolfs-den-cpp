#include <iostream>
#include "main.hpp"

int main() {
	//Init libtcod
	TCODConsole::initRoot(100, 40, "Wolf's Den 2");

	//Set up world
	World world(0xDEADBEEF);
	GameMap m(30, 30, "Mines", true);
	world.addMap("mine", m);
	world.curMapID = "mine";

	//set up screens
	ScreenManager manager;
	manager.registerScreen(new MainScreen(world));
	manager.setScreen("main");
	TCOD_key_t key;
	
	//main loop
	while (!TCODConsole::isWindowClosed()) {
		TCODConsole::root->clear();
		manager.getCurScreen().render();
		TCODConsole::flush();
		TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, false);
		manager.getCurScreen().handleKeys(key, key.shift);
	}
}