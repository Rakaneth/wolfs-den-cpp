#pragma once

enum ItemType { IT_HEALING = 0, IT_FOOD, IT_EQUIP };

enum EquipSlot { ES_ARMOR = 0, ES_TRINKET, ES_WEAPON };
class Creature;

class Entity : public ILocatable, public IUpkeep {
public:
  Entity(const std::shared_ptr<World>& world, int layer,
         std::string name = "No name", std::string desc = "No desc",
         char glyph = 0);
  Entity() = default;
  std::string name;
  std::string desc;
  std::string mapID;
  char glyph;
  TCODColor color;
  virtual void tick() {}
  GameMap& getMap();
  int ID() const { return _id; }
  int getLayer() const { return _layer; }
  World& getWorld() { return *_world.lock(); }

  void move(int x, int y);
  void move(const Pos& pos) { move(pos.x, pos.y); }
  void addTag(std::string tag) { _tags.push_back(tag); }
  void removeTag(std::string tag);
  bool hasTag(std::string tag);
  virtual Pos pos() override;

protected:
  static int _counter;
  int _x, _y;
  int _id;
  int _layer;
  std::vector<std::string> _tags;
  std::weak_ptr<World> _world;
};

class Item : public Entity {
public:
  Item(const std::shared_ptr<World>& world, ItemType type,
       std::string name = "No name", std::string desc = "No desc",
       char glyph = 0, int uses = INFINITE);
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
