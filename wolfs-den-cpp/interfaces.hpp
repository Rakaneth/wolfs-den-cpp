#pragma once

class ILocatable {
public:
  virtual Pos pos() = 0;
};

class IUpkeep {
public:
  IUpkeep() : upkeep(true) {}
  bool upkeep;
  virtual void tick() = 0;
};
