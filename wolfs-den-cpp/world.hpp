#pragma once
class Factory;

class World {
public:
  World(uint32_t seed);
  World();
  TCODRandom getRNG() const { return *_rng; }
  GameMap& getMap(std::string mapID) { return *_maps[mapID]; }
  void addMap(std::string mapID, GameMap* map);
  // void changeMap(std::string mapID);
  GameMap& getCurMap() { return getMap(curMapID); }
  std::string curMapID;
  Pos player; // TODO: entity
  UpkeepManager& getUpkeepManager() const { return *_upkeep; }
  Factory& getFactory() const { return *_factory; }
  int getTurn() const { return _turn; }

private:
  std::map<std::string, std::unique_ptr<GameMap>> _maps;
  std::unique_ptr<TCODRandom> _rng;
  std::unique_ptr<UpkeepManager> _upkeep;
  std::unique_ptr<Factory> _factory;
  int _turn;
};
