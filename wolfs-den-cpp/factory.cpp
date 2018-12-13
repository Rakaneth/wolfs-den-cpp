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
  creatureParser.run("data/entity/creatures.dat", new CreatureParser());
}

void Factory::initEquip() {}

void Factory::initItems() {}

void Factory::init() {
  initCreatures();
  initEquip();
  initItems();
}