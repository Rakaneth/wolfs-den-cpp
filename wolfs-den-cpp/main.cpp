#include "main.hpp"
#include <iostream>

int main() {
  // Init libtcod
  TCODConsole::setCustomFont("terminal16x16_gs_ro.png",
                             TCOD_FONT_LAYOUT_ASCII_INROW | TCOD_FONT_TYPE_GREYSCALE);
  TCODConsole::initRoot(100, 40, "Wolf's Den 2");

  // Set up world
  auto world = std::make_shared<World>(0xDEADBEEF);
  world->addMap("mine",
                GameMap::makeCaves(85, 85, "Mines", world->getRNGPtr()));
  world->changeMap("mine");
  
  /*
  //test stats
  auto dex = std::make_shared<Stat>("Dexterity", 5);
  dex->addFinalBonus(TempStat("Dex Buff", 5, 5));
  dex->addRawBonus(TempStat("Other Dex Buff", 2, 0, 0.2));
  world->getUpkeepManager().add(dex);
  for (int i = 0; i < 6; i++) {
    std::cout << "Turn " << i << ": Dexterity is " << dex->getValue() <<
  std::endl; world->getUpkeepManager().process();
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

  // test equipment
  int staffID = world->getFactory().makeEquip(world, "staff", "oak");
  auto staff = world->getByID<Equipment>(staffID);
  staff->mapID = "mine";
  world->setPlayer(world->getFactory().makeCreature(world, "wolf"));
  world->getPlayer().mapID = "mine";
  world->getPlayer().move(world->getCurMap().randomFloor());

  // set up screens
  ScreenManager manager;
  manager.registerScreen(std::make_shared<MainScreen>(world));
  manager.setScreen("main");
  TCOD_key_t key;

  // main loop
  while (!TCODConsole::isWindowClosed()) {
    manager.getCurScreen().render();
    TCODConsole::flush();
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, false);
    auto playerCmd = manager.getCurScreen().handleKeys(key, key.shift);
    playerCmd->execute(world->getPlayer());
  }
}