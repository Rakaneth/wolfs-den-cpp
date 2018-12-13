#include "main.hpp"

std::vector<CreatureTemplate> Factory::_creatureTemplates;
std::vector<EquipTemplate> Factory::_equipTemplates;
std::vector<ItemTemplate> Factory::_itemTemplates;

void Factory::initCreatures() {
  TCODParser creatureParser;
  auto creature = creatureParser.newStructure("creature");
  auto stats = creatureParser.newStructure("stats");
  creature->addStructure(stats);
  stats->addProperty("str", TCOD_TYPE_INT, false);
  stats->addProperty("stam", TCOD_TYPE_INT, false);
  stats->addProperty("spd", TCOD_TYPE_INT, false);
  stats->addProperty("skl", TCOD_TYPE_INT, false);
  stats->addProperty("sag", TCOD_TYPE_INT, false);
  stats->addProperty("smt", TCOD_TYPE_INT, false);
  stats->addProperty("vision", TCOD_TYPE_INT, false);
  creature->addProperty("name", TCOD_TYPE_STRING, true);
  creature->addProperty("desc", TCOD_TYPE_STRING, true);
  creature->addProperty("type", TCOD_TYPE_STRING, true);
  creature->addProperty("glyph", TCOD_TYPE_CHAR, true);
  creature->addProperty("col", TCOD_TYPE_COLOR, false);
  creature->addProperty("unarmed", TCOD_TYPE_STRING, false);
  creature->addListProperty("tags", TCOD_TYPE_STRING, true);
  creatureParser.run("data/entity/creatures.dat", new CreatureParser());
}

void Factory::initEquip() {}

void Factory::initItems() {}

void Factory::init() {
  initCreatures();
  initEquip();
  initItems();
}

void Factory::debugPrintCreatures() {
  std::cout << "Creature template list has " << getCreatureCount() << " entries"
            << std::endl;
  for (auto& creature : _creatureTemplates) {
    std::cout << "---" << std::endl;
    std::cout << "ID: " << creature.id << std::endl;
    std::cout << "Name: " << creature.name << std::endl;
    std::cout << "Desc: " << creature.desc << std::endl;
    std::cout << "Glyph: " << creature.glyph << std::endl;
    std::cout << "Stats: ";
    std::cout << creature.str << " " << creature.stam << " " << creature.spd << " " << creature.skl
              << " " << creature.sag << " " << creature.smt << std::endl;
    std::cout << "Tags: ";
    for (auto& tag : creature.tags)
      std::cout << tag << ", ";
    std::cout << std::endl;
  }
}