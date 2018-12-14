#include "main.hpp"
#include <iostream>

int main() {
  // Init libtcod
  TCODConsole::initRoot(100, 40, "Wolf's Den 2");

  // Set up world
  auto world = std::make_shared<World>(0xDEADBEEF);
  world->addMap("mine", new GameMap(30, 30, "Mines", true));
  world->curMapID = "mine";
  world->player = Pos{2, 5};
  /*
  //test stats
  auto dex = std::make_shared<Stat>("Dexterity", 5);
  dex->addFinalBonus(TempStat("Dex Buff", 5, 5));
  dex->addRawBonus(TempStat("Other Dex Buff", 2, 0, 0.2));
  world->getUpkeepManager().add(dex);
  for (int i = 0; i < 6; i++) {
    std::cout << "Turn " << i << ": Dexterity is " << dex->getValue() << std::endl;
    world->getUpkeepManager().process();
  }
  */

  /*
  //test name generator
  TCODNamegen::parse("data/names/dwarf.dat", &world->getRNG());
  std::cout << "Male Dwarf names: " << std::endl;
  for (int n = 0; n < 10; n++)
    std::cout << TCODNamegen::generate((char*)"dwarf_male") << std::endl;
  std::cout << "Female Dwarf names:" << std::endl;
  for (int f = 0; f < 10; f++)
    std::cout << TCODNamegen::generate((char*)"dwarf_female") << std::endl;
  */

  /*
  //test parser
  Factory factory;
  factory.init();
  factory.debugPrintCreatures();
  factory.debugPrintEquip();
  factory.debugPrintItems();
  factory.debugPrintMaterials();
  */

  // set up screens
  ScreenManager manager;
  manager.registerScreen(std::make_shared<MainScreen>(world));
  manager.setScreen("main");
  TCOD_key_t key;

  // main loop
  while (!TCODConsole::isWindowClosed()) {
    TCODConsole::root->clear();
    manager.getCurScreen().render();
    TCODConsole::flush();
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, false);
    manager.getCurScreen().handleKeys(key, key.shift);
  }
}