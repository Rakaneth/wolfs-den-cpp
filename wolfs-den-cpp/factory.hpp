#pragma once

class Factory {
public:
  void init();
  int getCreatureCount() const { return _creatureTemplates.size(); }
  void debugPrintCreatures();

private:
  friend class CreatureParser;
  friend class ItemParser;
  friend class EquipParser;
  void initCreatures();
  void initEquip();
  void initItems();
  static std::vector<CreatureTemplate> _creatureTemplates;
  static std::vector<EquipTemplate> _equipTemplates;
  static std::vector<ItemTemplate> _itemTemplates;
};
