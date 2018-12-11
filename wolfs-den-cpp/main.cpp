#include <iostream>
#include "main.hpp"

int main() {
	//Init libtcod
	TCODConsole::initRoot(100, 40, "Wolf's Den 2");

	//Set up world
	auto world = std::make_shared<World>(0xDEADBEEF);
	GameMap m(30, 30, "Mines", true);
	world->addMap("mine", m);
	world->curMapID = "mine";

	/*test stats
	auto dex = std::make_shared<Stat>("Dexterity", 5);
	dex->addFinalBonus(TempStat("Dex Buff", 5, 5));
	dex->addRawBonus(TempStat("Other Dex Buff", 2, 0, 0.2));
	world->getUpkeepManager().add(dex);
	for (int i = 0; i < 6; i++) {
		std::cout << "Turn " << i << ": Dexterity is " << dex->getValue() << std::endl;
		world->getUpkeepManager().process();
	}
	*/

	//set up screens
	ScreenManager manager;
	manager.registerScreen(std::make_shared<MainScreen>(world));
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