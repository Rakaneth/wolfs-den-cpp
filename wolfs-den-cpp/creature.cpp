#include "main.hpp"

Creature::Creature(const std::shared_ptr<World>& world,
                   const CreatureTemplate& crTemp, int layer, bool isPlayer)
  : Entity(world, layer, crTemp.name, crTemp.desc, crTemp.glyph),
    _str("Strength", crTemp.str),
    _stam("Stamina", crTemp.stam),
    _spd("Speed", crTemp.spd),
    _skl("Skill", crTemp.skl),
    _sag("Sagacity", crTemp.sag),
    _smt("Smarts", crTemp.smt),
    _vision("Vision", crTemp.vision),
    naturalWeapon(world->getFactory().makeEquip(world, crTemp.unarmed)),
    isPlayer(isPlayer) {
  color = crTemp.color;
  _tags = crTemp.tags;
}

Equipment* Creature::getEquipped(EquipSlot slot) {
  for (auto& eID : _inventory) {
    auto pEQ = _world.lock()->getByID<Equipment>(eID);
    if (pEQ && pEQ->getSlot() == slot)
      return pEQ.get();
  }
  return nullptr;
}

void Creature::equip(Equipment& equip) {
  auto curEQ = getEquipped(equip.getSlot());
  if (curEQ)
    curEQ->equipped = false;
  if (equip.getSlot() == ES_WEAPON)
    getNaturalWeapon().equipped = false;
  equip.equipped = true;
}

void Creature::dequip(Equipment& equip) { 
  equip.equipped = false;
  if (equip.getSlot() == ES_WEAPON)
    getNaturalWeapon().equipped = true;
}

void Creature::pickup(Item& item) { 
  // TODO: add message if player
  if (bagsFull()) 
    return;
  else {
    item.mapID = "none";
    item.move(0, 0);
    _inventory.push_back(item.ID());
  }
}

void Creature::drop(Item& item) { 
  item.mapID = mapID; 
  item.move(_x, _y);
  auto it = std::remove(_inventory.begin(), _inventory.end(), item.ID());
  _inventory.erase(it);
}