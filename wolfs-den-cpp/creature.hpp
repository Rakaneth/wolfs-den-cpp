#pragma once

class Creature : public Entity {
public:
  Creature() = delete;
  Creature(const std::shared_ptr<World>& world, const CreatureTemplate& crTemp,
           int layer = 2, bool isPlayer = false);
  Stat& getStr() { return _str; }
  Stat& getStam() { return _stam; }
  Stat& getSpd() { return _spd; }
  Stat& getSkl() { return _skl; }
  Stat& getSag() { return _sag; }
  Stat& getSmt() { return _smt; }
  Stat& getVision() { return _vision; }
  bool hasItem(int eID) { return contains(_inventory, eID); }
  bool hasItem(const Item& item) { return contains(_inventory, item.ID()); }
  bool isPlayer;
  int naturalWeapon;
  int invCapacity;
  bool bagsFull() { return _inventory.size() >= invCapacity; }
  void equip(Equipment& equip);
  void equip(int eID) { equip(*_world.lock()->getByID<Equipment>(eID)); }
  void dequip(Equipment& equip);
  void dequip(int eID) { dequip(*_world.lock()->getByID<Equipment>(eID)); }
  std::weak_ptr<Equipment> getEquipped(EquipSlot slot);
  void pickup(Item& item);
  void drop(Item& item);
  Equipment& getNaturalWeapon() {
    return *_world.lock()->getByID<Equipment>(naturalWeapon);
  }

private:
  std::vector<int> _inventory;
  Stat _str, _stam, _skl, _spd, _sag, _smt, _vision;
};