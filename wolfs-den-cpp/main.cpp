#include <iostream>
#include "main.hpp"

int main() {
	//Init libtcod
	TCODConsole::initRoot(100, 40, "Wolf's Den 2");

	//set up screens
	ScreenManager manager;
	manager.registerScreen(new MainScreen());
	manager.setScreen("main");

	//main loop
	while (!TCODConsole::isWindowClosed()) {
		TCOD_key_t key;
		TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, false);
		TCODConsole::root->clear();
		manager.getCurScreen().handleKeys(key, key.shift);
		manager.getCurScreen().render();
		TCODConsole::flush();
	}
}