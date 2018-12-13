#pragma once

enum ItemType { HEALING = 0, FOOD, EQUIP };

enum EquipSlot { ARMOR = 0, TRINKET, WEAPON };

class Entity : public ILocatable, public IUpkeep {
public:
  Entity(std::shared_ptr<World> world);
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
  Item(std::shared_ptr<World> world, ItemType type, int uses = INFINITE);
  virtual void use() = 0;
  static const int INFINITE;
  ItemType getItemType() const { return _type; }

private:
  int _uses;
  ItemType _type;
};

class Equipment : public Item {
public:
  Equipment(std::shared_ptr<World> world);
  void use();
  int getAtp() const { return _atp; }
  int getDfp() const { return _dfp; }
  int getDmg() const { return _dmg; }
  int getTou() const { return _tou; }
  int getRes() const { return _res; }
  int getWil() const { return _wil; }
  int getPwr() const { return _pwr; }

private:
  EquipSlot _slot;
  int _atp, _dfp, _dmg, _tou, _res, _wil, _pwr;
};

class Creature : public Entity {
public:
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
  std::string slot;
  int atp, dfp, dmg, res, tou, wil, pwr, vision;
};

struct ItemTemplate : public BaseTemplate {
  std::string type;
  double amt;
};
