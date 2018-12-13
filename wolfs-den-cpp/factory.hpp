#pragma once

class Factory {
public:
  void init();
  size_t getCreatureCount() const { return _creatureTemplates.size(); }
  size_t getItemCount() const { return _itemTemplates.size(); }
  size_t getEquipCount() const { return _equipTemplates.size(); }
  size_t getMatCount() const { return _materials.size(); }
  void debugPrintCreatures();
  void debugPrintEquip();
  void debugPrintItems();
  Material& getMaterial(std::string matID) const {
    return _materials.at(matID);
  }
  void debugPrintMaterials();
  

private:
  friend class CreatureParser;
  friend class ItemParser;
  friend class EquipParser;
  friend class MaterialsParser;
  void initCreatures();
  void initEquip();
  void initItems();
  void initMaterials();
  void printMatStatSet(const MatStatSet& set);
  static std::vector<CreatureTemplate> _creatureTemplates;
  static std::vector<EquipTemplate> _equipTemplates;
  static std::vector<ItemTemplate> _itemTemplates;
  static std::map<std::string, Material> _materials;
};
