#include "main.hpp"

bool CreatureParser::parserNewStruct(TCODParser* parser, const TCODParserStruct* str,
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
  }

  return true;
}

bool CreatureParser::parserFlag(TCODParser* parser, const char* name) { return true; }

bool CreatureParser::parserProperty(TCODParser* parser, const char* propname,
                                    TCOD_value_type_t type, TCOD_value_t value) {
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
  else if (strcmp(propname, "color") == 0)
    foetus.color = value.col;

  return true;
}

bool CreatureParser::parserEndStruct(TCODParser* parser, const TCODParserStruct* str,
                                     const char* name) {
  if (strcmp(str->getName(), "creature") == 0)
    Factory::_creatureTemplates.push_back(foetus);

  return true;
}

void CreatureParser::error(const char* msg) {
  std::cout << "Error parsing creature file: " << msg << std::endl;
}

bool ItemParser::parserNewStruct(TCODParser* parser, const TCODParserStruct* str,
                                 const char* name) {
  return false;
}

bool ItemParser::parserFlag(TCODParser* parser, const char* name) { return false; }

bool ItemParser::parserProperty(TCODParser* parser, const char* propname, TCOD_value_type_t type,
                                TCOD_value_t value) {
  return false;
}

bool ItemParser::parserEndStruct(TCODParser* parser, const TCODParserStruct* str,
                                 const char* name) {
  return false;
}

void ItemParser::error(const char* msg) {}

bool EquipParser::parserNewStruct(TCODParser* parser, const TCODParserStruct* str,
                                  const char* name) {
  return false;
}

bool EquipParser::parserFlag(TCODParser* parser, const char* name) { return false; }

bool EquipParser::parserProperty(TCODParser* parser, const char* propname, TCOD_value_type_t type,
                                 TCOD_value_t value) {
  return false;
}

bool EquipParser::parserEndStruct(TCODParser* parser, const TCODParserStruct* str,
                                  const char* name) {
  return false;
}

void EquipParser::error(const char* msg) {}
