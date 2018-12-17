#include "main.hpp"

bool CreatureParser::parserNewStruct(TCODParser* parser,
                                     const TCODParserStruct* str,
                                     const char* name) {
  if (strcmp(str->getName(), "creature") == 0) {
    foetus.color = TCODColor::white;
    foetus.desc = "No description";
    foetus.frequency = 0;
    foetus.glyph = '@';
    foetus.name = "No name";
    foetus.type = "No type";
    foetus.str = 10;
    foetus.stam = 10;
    foetus.skl = 10;
    foetus.smt = 10;
    foetus.sag = 10;
    foetus.spd = 10;
    foetus.id = name;
    foetus.unarmed = "hands";
    foetus.tags.clear();
  }
  return true;
}

bool CreatureParser::parserFlag(TCODParser* parser, const char* name) {
  return true;
}

bool CreatureParser::parserProperty(TCODParser* parser, const char* propname,
                                    TCOD_value_type_t type,
                                    TCOD_value_t value) {
  if (strcmp(propname, "name") == 0)
    foetus.name = value.s;
  else if (strcmp(propname, "type") == 0)
    foetus.type = value.s;
  else if (strcmp(propname, "desc") == 0)
    foetus.desc = value.s;
  else if (strcmp(propname, "unarmed") == 0)
    foetus.unarmed = value.s;
  else if (strcmp(propname, "glyph") == 0)
    foetus.glyph = value.c;
  else if (strcmp(propname, "str") == 0)
    foetus.str = value.i;
  else if (strcmp(propname, "stam") == 0)
    foetus.stam = value.i;
  else if (strcmp(propname, "skl") == 0)
    foetus.skl = value.i;
  else if (strcmp(propname, "spd") == 0)
    foetus.spd = value.i;
  else if (strcmp(propname, "sag") == 0)
    foetus.sag = value.i;
  else if (strcmp(propname, "smt") == 0)
    foetus.smt = value.i;
  else if (strcmp(propname, "col") == 0)
    foetus.color = value.col;
  else if (strcmp(propname, "tags") == 0) {
    for (char** it = (char**)TCOD_list_begin(value.list);
         it != (char**)TCOD_list_end(value.list); it++)
      foetus.tags.push_back(*it);
  }

  return true;
}

bool CreatureParser::parserEndStruct(TCODParser* parser,
                                     const TCODParserStruct* str,
                                     const char* name) {
  if (strcmp(str->getName(), "creature") == 0)
    Factory::_creatureTemplates.push_back(foetus);

  return true;
}

void CreatureParser::error(const char* msg) {
  std::cout << "Error parsing creature file: " << msg << std::endl;
}

bool ItemParser::parserNewStruct(TCODParser* parser,
                                 const TCODParserStruct* str,
                                 const char* name) {

  mould.amt = 0.0;
  mould.name = "No name";
  mould.desc = "No desc";
  mould.color = TCODColor::white;
  mould.glyph = 0;
  mould.frequency = 0;
  mould.id = name;
  mould.type = "No type";
  mould.flat = false;
  mould.tags.clear();
  return true;
}

bool ItemParser::parserFlag(TCODParser* parser, const char* name) {
  if (strcmp(name, "flat") == 0)
    mould.flat = true;
  return true;
}

bool ItemParser::parserProperty(TCODParser* parser, const char* propname,
                                TCOD_value_type_t type, TCOD_value_t value) {
  if (strcmp(propname, "amt") == 0)
    mould.amt = value.f;
  else if (strcmp(propname, "name") == 0)
    mould.name = value.s;
  else if (strcmp(propname, "desc") == 0)
    mould.desc = value.s;
  else if (strcmp(propname, "col") == 0)
    mould.color = value.col;
  else if (strcmp(propname, "type") == 0)
    mould.type = value.s;
  else if (strcmp(propname, "glyph") == 0)
    mould.glyph = value.c;
  else if (strcmp(propname, "frequency") == 0)
    mould.frequency = value.i;
  else if (strcmp(propname, "tags") == 0)
    for (char** it = (char**)TCOD_list_begin(value.list);
         it != (char**)TCOD_list_end(value.list); it++)
      mould.tags.push_back(*it);

  return true;
}

bool ItemParser::parserEndStruct(TCODParser* parser,
                                 const TCODParserStruct* str,
                                 const char* name) {
  Factory::_itemTemplates.push_back(mould);
  return true;
}

void ItemParser::error(const char* msg) {
  std::cout << "Error parsing item file: " << msg << std::endl;
}

bool EquipParser::parserNewStruct(TCODParser* parser,
                                  const TCODParserStruct* str,
                                  const char* name) {
  if (strcmp(str->getName(), "equip") == 0) {
    mould.name = "No name";
    mould.desc = "No desc";
    mould.material = false;
    mould.color = TCODColor::white;
    mould.frequency = 0;
    mould.glyph = 0;
    mould.id = name;
    mould.atp = 0;
    mould.dfp = 0;
    mould.tou = 0;
    mould.res = 0;
    mould.dmg = 0;
    mould.pwr = 0;
    mould.wil = 0;
    mould.vision = 0;
    mould.tags.clear();
  }
  return true;
}

bool EquipParser::parserFlag(TCODParser* parser, const char* name) {
  if (strcmp(name, "material") == 0)
    mould.material = true;
  return true;
}

bool EquipParser::parserProperty(TCODParser* parser, const char* propname,
                                 TCOD_value_type_t type, TCOD_value_t value) {
  if (strcmp(propname, "name") == 0)
    mould.name = value.s;
  else if (strcmp(propname, "desc") == 0)
    mould.desc = value.s;
  else if (strcmp(propname, "glyph") == 0)
    mould.glyph = value.c;
  else if (strcmp(propname, "col") == 0)
    mould.color = value.col;
  else if (strcmp(propname, "frequency") == 0)
    mould.frequency = value.i;
  else if (strcmp(propname, "slot") == 0)
    mould.slot = value.s;
  else if (strcmp(propname, "atp") == 0)
    mould.atp = value.i;
  else if (strcmp(propname, "dfp") == 0)
    mould.dfp = value.i;
  else if (strcmp(propname, "dmg") == 0)
    mould.dmg = value.i;
  else if (strcmp(propname, "tou") == 0)
    mould.tou = value.i;
  else if (strcmp(propname, "res") == 0)
    mould.res = value.i;
  else if (strcmp(propname, "wil") == 0)
    mould.wil = value.i;
  else if (strcmp(propname, "pwr") == 0)
    mould.pwr = value.i;
  else if (strcmp(propname, "vision") == 0)
    mould.vision = value.i;
  else if (strcmp(propname, "equipType") == 0)
    mould.equipType = value.s;
  else if (strcmp(propname, "damageType") == 0)
    mould.damageType = value.s;
  else if (strcmp(propname, "tags") == 0)
    for (char** it = (char**)TCOD_list_begin(value.list);
         it != (char**)TCOD_list_end(value.list); it++)
      mould.tags.push_back(*it);

  return true;
}

bool EquipParser::parserEndStruct(TCODParser* parser,
                                  const TCODParserStruct* str,
                                  const char* name) {
  if (strcmp(str->getName(), "equip") == 0) {
    Factory::_equipTemplates.push_back(mould);
  }
  return true;
}

void EquipParser::error(const char* msg) {
  std::cout << "Error parsing equip file: " << msg << std::endl;
}

bool MaterialsParser::parserNewStruct(TCODParser* parser,
                                      const TCODParserStruct* str,
                                      const char* name) {
  auto curProp = str->getName();
  if (strcmp(curProp, "material") == 0) {
    curSet = {};
    newMat.name = "No name";
    newMat.hardness = 0;
    newMat.color = TCODColor::white;
    newMat.armor = {};
    newMat.axe = {};
    newMat.sword = {};
    newMat.rapier = {};
    newMat.staff = {};
    newMat.hammer = {};
  }
  return true;
}

bool MaterialsParser::parserFlag(TCODParser* parser, const char* name) {
  return true;
}

bool MaterialsParser::parserProperty(TCODParser* parser, const char* propname,
                                     TCOD_value_type_t type,
                                     TCOD_value_t value) {
  if (strcmp(propname, "name") == 0)
    newMat.name = value.s;
  else if (strcmp(propname, "hardness") == 0)
    newMat.hardness = value.i;
  else if (strcmp(propname, "col") == 0)
    newMat.color = value.col;
  else if (strcmp(propname, "atp") == 0)
    curSet.atp = value.i;
  else if (strcmp(propname, "dfp") == 0)
    curSet.dfp = value.i;
  else if (strcmp(propname, "dmg") == 0)
    curSet.dmg = value.i;
  else if (strcmp(propname, "res") == 0)
    curSet.res = value.i;
  else if (strcmp(propname, "tou") == 0)
    curSet.tou = value.i;
  else if (strcmp(propname, "wil") == 0)
    curSet.wil = value.i;
  else if (strcmp(propname, "pwr") == 0)
    curSet.pwr = value.i;
  
  return true;
}

bool MaterialsParser::parserEndStruct(TCODParser* parser,
                                      const TCODParserStruct* str,
                                      const char* name) {
  auto curStruct = str->getName();
  if (strcmp(curStruct, "material") == 0) {
    auto pair = std::make_pair(std::string(name), newMat);
    Factory::_materials.insert(pair);
  } else if (strcmp(curStruct, "stats") == 0) {
    if (strcmp(name, "axe") == 0)
      newMat.axe = curSet;
    else if (strcmp(name, "sword") == 0)
      newMat.sword = curSet;
    else if (strcmp(name, "staff") == 0)
      newMat.staff = curSet;
    else if (strcmp(name, "rapier") == 0)
      newMat.rapier = curSet;
    else if (strcmp(name, "hammer") == 0)
      newMat.hammer = curSet;
    else if (strcmp(name, "armor") == 0)
      newMat.armor = curSet;

    curSet = {};
  }
  return true;
}

void MaterialsParser::error(const char* msg) {
  std::cout << "Error parsing materials file: " << msg << std::endl;
}
