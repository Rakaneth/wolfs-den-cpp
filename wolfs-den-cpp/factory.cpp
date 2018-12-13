#include "main.hpp"

std::vector<CreatureTemplate> Factory::_creatureTemplates;
std::vector<EquipTemplate> Factory::_equipTemplates;
std::vector<ItemTemplate> Factory::_itemTemplates;
std::map<std::string, Material> Factory::_materials;

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

void Factory::initEquip() {
  TCODParser parser;
  auto equip = parser.newStructure("equip");
  auto stats = parser.newStructure("stats");
  equip->addStructure(stats);
  stats->addProperty("atp", TCOD_TYPE_INT, false);
  stats->addProperty("dfp", TCOD_TYPE_INT, false);
  stats->addProperty("dmg", TCOD_TYPE_INT, false);
  stats->addProperty("tou", TCOD_TYPE_INT, false);
  stats->addProperty("res", TCOD_TYPE_INT, false);
  stats->addProperty("wil", TCOD_TYPE_INT, false);
  stats->addProperty("pwr", TCOD_TYPE_INT, false);
  stats->addProperty("vision", TCOD_TYPE_INT, false);
  equip->addProperty("name", TCOD_TYPE_STRING, true);
  equip->addProperty("glyph", TCOD_TYPE_CHAR, false);
  equip->addFlag("material");
  equip->addProperty("desc", TCOD_TYPE_STRING, true);
  equip->addProperty("col", TCOD_TYPE_COLOR, false);
  equip->addProperty("slot", TCOD_TYPE_STRING, true);
  equip->addProperty("frequency", TCOD_TYPE_INT, false);
  equip->addListProperty("tags", TCOD_TYPE_STRING, true);
  equip->addProperty("damageType", TCOD_TYPE_STRING, false);
  equip->addProperty("equipType", TCOD_TYPE_STRING, false);
  parser.run("data/entity/equip.dat", new EquipParser());
}

void Factory::initItems() {
  TCODParser parser;
  auto item = parser.newStructure("item");
  item->addProperty("name", TCOD_TYPE_STRING, true);
  item->addProperty("desc", TCOD_TYPE_STRING, true);
  item->addProperty("glyph", TCOD_TYPE_CHAR, true);
  item->addProperty("col", TCOD_TYPE_COLOR, false);
  item->addProperty("frequency", TCOD_TYPE_INT, false);
  item->addProperty("type", TCOD_TYPE_STRING, true);
  item->addFlag("flat");
  item->addProperty("amt", TCOD_TYPE_FLOAT, false);
  item->addListProperty("tags", TCOD_TYPE_STRING, true);
  parser.run("data/entity/items.dat", new ItemParser());
}

void Factory::initMaterials() { TCODParser parser;
  auto mat = parser.newStructure("material");
  auto stats = parser.newStructure("stats");
  mat->addStructure(stats);
  stats->addProperty("atp", TCOD_TYPE_INT, false);
  stats->addProperty("dfp", TCOD_TYPE_INT, false);
  stats->addProperty("res", TCOD_TYPE_INT, false);
  stats->addProperty("tou", TCOD_TYPE_INT, false);
  stats->addProperty("dmg", TCOD_TYPE_INT, false);
  stats->addProperty("wil", TCOD_TYPE_INT, false);
  stats->addProperty("pwr", TCOD_TYPE_INT, false);
  mat->addProperty("name", TCOD_TYPE_STRING, true);
  mat->addProperty("hardness", TCOD_TYPE_INT, true);
  mat->addProperty("col", TCOD_TYPE_COLOR, true);
  mat->addProperty("frequency", TCOD_TYPE_INT, false);
  parser.run("data/entity/materials.dat", new MaterialsParser());
}

void Factory::init() {
  std::cout << "Loading creatures...";
  initCreatures();
  std::cout << getCreatureCount() << " creature templates loaded." << std::endl;
  std::cout << "Loading equipment...";
  initEquip();
  std::cout << getEquipCount() << " equipment templates loaded." << std::endl;
  std::cout << "Loading items...";
  initItems();
  std::cout << getItemCount() << " item templates loaded." << std::endl;
  std::cout << "Loading materials...";
  initMaterials();
  std::cout << getMatCount() << " material types loaded." << std::endl;
}

void Factory::debugPrintCreatures() {
  std::cout << "Creature template list has " << getCreatureCount() << " entries"
            << std::endl;
  for (auto& creature : _creatureTemplates) {
    std::cout << "---Creature: " << creature.id << "---" << std::endl;
    std::cout << "Name: " << creature.name << std::endl;
    std::cout << "Desc: " << creature.desc << std::endl;
    std::cout << "Glyph: " << creature.glyph << std::endl;
    std::cout << "Stats: ";
    std::cout << "Str " << creature.str;
    std::cout << " Stam " << creature.stam;
    std::cout << " Spd " << creature.spd;
    std::cout << " Skl " << creature.skl;
    std::cout << " Sag " << creature.sag;
    std::cout << " Smt " << creature.smt << std::endl;
    std::cout << "Tags: ";
    for (auto& tag : creature.tags)
      std::cout << tag << ", ";
    std::cout << std::endl;
  }
}

void Factory::debugPrintEquip() {
  std::cout << "Equip template list has " << getEquipCount() << " entries"
            << std::endl;
  for (auto& equip : _equipTemplates) {
    std::cout << "---Equipment: " << equip.id << "---" << std::endl;
    std::cout << "Name: " << equip.name << std::endl;
    std::cout << "Desc: " << equip.desc << std::endl;
    std::cout << "Glyph: " << equip.glyph << std::endl;
    std::cout << "Type: " << equip.type << std::endl;
    std::cout << "Damage Type: " << equip.damageType << std::endl;
    std::cout << "Equipment Type: " << equip.equipType << std::endl;
    std::cout << "Stats: ";
    std::cout << "Atp " << equip.atp;
    std::cout << " Dfp " << equip.dfp;
    std::cout << " Dmg " << equip.dmg;
    std::cout << " Tou " << equip.tou;
    std::cout << " Res " << equip.res;
    std::cout << " Wil " << equip.wil;
    std::cout << " Pwr " << equip.pwr;
    std::cout << " Vision " << equip.vision << std::endl;
    if (equip.material)
      std::cout << "This item must be made of a material." << std::endl;
    
    std::cout << "Tags: ";
    for (auto& tag : equip.tags)
      std::cout << tag << ", ";
    
    std::cout << std::endl;
  }
}

void Factory::debugPrintItems() {
  std::cout << "Item template list has " << getItemCount() << " entries"
            << std::endl;
  for (auto& item : _itemTemplates) {
    std::cout << "---Item: " << item.id << "---" << std::endl;
    std::cout << "Name: " << item.name << std::endl;
    std::cout << "Desc: " << item.desc << std::endl;
    std::cout << "Glyph: " << item.glyph << std::endl;
    std::cout << "Type: " << item.type << std::endl;
    std::cout << "Amount recovered: " << item.amt;
    std::cout << (item.flat ? " (flat)" : " (pct)") << std::endl;
    std::cout << "Tags: ";
    for (auto& tag : item.tags)
      std::cout << tag << ", ";

    std::cout << std::endl;
  }
}

void Factory::debugPrintMaterials() {
  std::cout << "Materials map has " << getMatCount() << " entries" << std::endl;
  for (auto& pair : _materials) {
    std::cout << "---Material: " << pair.first << "---" << std::endl;
    std::cout << "Name: " << pair.second.name << std::endl;
    std::cout << "Hardness: " << pair.second.hardness << std::endl;
    std::cout << "Sword Stats: ";
    printMatStatSet(pair.second.sword);
    std::cout << "Rapier Stats: ";
    printMatStatSet(pair.second.rapier);
    std::cout << "Axe Stats: ";
    printMatStatSet(pair.second.axe);
    std::cout << "Hammer Stats: ";
    printMatStatSet(pair.second.hammer);
    std::cout << "Staff Stats: ";
    printMatStatSet(pair.second.staff);
    std::cout << "Armor Stats: ";
    printMatStatSet(pair.second.armor);
  }
}

void Factory::printMatStatSet(const MatStatSet& set) {
  std::cout << "Atp " << set.atp;
  std::cout << " Dfp " << set.dfp;
  std::cout << " Dmg " << set.dmg;
  std::cout << " Tou " << set.tou;
  std::cout << " Res " << set.res;
  std::cout << " Wil " << set.wil;
  std::cout << " Pwr " << set.pwr << std::endl;
}