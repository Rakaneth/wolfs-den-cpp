#pragma once

enum ItemType { HEALING = 0, FOOD, EQUIP };

enum EquipSlot { ARMOR = 0, TRINKET, WEAPON };
class Creature;

class Entity : public ILocatable, public IUpkeep {
public:
  Entity(const std::shared_ptr<World>& world);
  Entity() = default;
  std::string name;
  std::string desc;
  std::string mapID;
  char glyph;
  TCODColor color;
  virtual void tick() {}
  GameMap& getMap();
  int ID() const { return _id; }
  Pos pos() const { return Pos{_x, _y}; }
  void move(int x, int y);
  void move(const Pos& pos) { move(pos.x, pos.y); }
  void addTag(std::string tag) { _tags.push_back(tag); }
  void removeTag(std::string tag);
  bool hasTag(std::string tag);

protected:
  static int _counter;
  int _x, _y;
  int _id;
  std::vector<std::string> _tags;
  std::weak_ptr<World> _world;
};

class Item : public Entity {
public:
  Item(const std::shared_ptr<World>& world, ItemType type, int uses = INFINITE);
  virtual bool use(Creature& user, const Creature* target = nullptr) = 0;
  static const int INFINITE;
  ItemType getItemType() const { return _type; }

private:
  int _uses;
  ItemType _type;
};

struct BaseTemplate {
  std::string name, type, desc, id;
  char glyph;
  TCODColor color;
  int frequency;
  std::vector<std::string> tags;
};

struct CreatureTemplate : public BaseTemplate {
  std::string type, unarmed;
  int str, stam, spd, skl, sag, smt, vision;
};

struct EquipTemplate : public BaseTemplate {
  std::string slot, equipType, damageType;
  int atp, dfp, dmg, res, tou, wil, pwr, vision;
  bool material;
};

struct ItemTemplate : public BaseTemplate {
  std::string type;
  bool flat;
  double amt;
};

struct MatStatSet {
  int atp = 0, dfp = 0, dmg = 0, res = 0, tou = 0, wil = 0, pwr = 0, vision = 0;
};

struct Material {
  std::string name;
  int hardness;
  MatStatSet axe, sword, staff, rapier, hammer, armor;
  TCODColor color;
};
