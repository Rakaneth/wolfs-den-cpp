#pragma once

class Creature : public Entity {
public:
  Creature() = delete;
  Creature(const std::shared_ptr<World>& world, const CreatureTemplate& crTemp);
  Stat& getStr() { return _str; }
  Stat& getStam() { return _stam; }
  Stat& getSpd() { return _spd; }
  Stat& getSkl() { return _skl; }
  Stat& getSag() { return _sag; }
  Stat& getSmt() { return _smt; }
  Stat& getVision() { return _vision; }
  bool isPlayer;

private:
  std::vector<int> _inventory;
  Stat _str, _stam, _skl, _spd, _sag, _smt, _vision;
};