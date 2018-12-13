#pragma once

class CreatureParser : public ITCODParserListener {
  virtual bool parserNewStruct(TCODParser* parser, const TCODParserStruct* str,
                               const char* name) override;
  virtual bool parserFlag(TCODParser* parser, const char* name) override;
  virtual bool parserProperty(TCODParser* parser, const char* propname, TCOD_value_type_t type,
                              TCOD_value_t value) override;
  virtual bool parserEndStruct(TCODParser* parser, const TCODParserStruct* str,
                               const char* name) override;
  virtual void error(const char* msg) override;

private:
  CreatureTemplate foetus;
};

class ItemParser : public ITCODParserListener {
  // Inherited via ITCODParserListener
  virtual bool parserNewStruct(TCODParser* parser, const TCODParserStruct* str,
                               const char* name) override;
  virtual bool parserFlag(TCODParser* parser, const char* name) override;
  virtual bool parserProperty(TCODParser* parser, const char* propname, TCOD_value_type_t type,
                              TCOD_value_t value) override;
  virtual bool parserEndStruct(TCODParser* parser, const TCODParserStruct* str,
                               const char* name) override;
  virtual void error(const char* msg) override;

private:
  ItemTemplate mould;
};

class EquipParser : public ITCODParserListener {
  // Inherited via ITCODParserListener
  virtual bool parserNewStruct(TCODParser* parser, const TCODParserStruct* str,
                               const char* name) override;
  virtual bool parserFlag(TCODParser* parser, const char* name) override;
  virtual bool parserProperty(TCODParser* parser, const char* propname, TCOD_value_type_t type,
                              TCOD_value_t value) override;
  virtual bool parserEndStruct(TCODParser* parser, const TCODParserStruct* str,
                               const char* name) override;
  virtual void error(const char* msg) override;

private:
  EquipTemplate mould;
};
