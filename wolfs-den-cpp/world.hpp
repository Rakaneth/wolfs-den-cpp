#pragma once
class Factory;

class World {
public:
  World(uint32_t seed);
  World();
  TCODRandom& getRNG() const { return *_rng; }
  std::shared_ptr<TCODRandom>& getRNGPtr() { return _rng; }
  GameMap& getMap(std::string mapID) { return *_maps[mapID]; }
  void addMap(std::string mapID, GameMap* map);
  // void changeMap(std::string mapID);
  GameMap& getCurMap() { return getMap(_curMapID); }
  Creature& getPlayer() { return getByID<Creature>(_playerID); }
  void setPlayer(int eID) { _playerID = eID; }
  UpkeepManager& getUpkeepManager() const { return *_upkeep; }
  Factory& getFactory() const { return *_factory; }
  int getTurn() const { return _turn; }
  int addEntity(std::shared_ptr<Entity> ent);
  void removeEntity(int entID);
  void changeMap(std::string newMapID);
  std::vector<Entity> curThings();
  template <class T> T& getByID(int eID) { return (T)*_things[eID]; }

private:
  std::string _curMapID;
  std::map<std::string, std::unique_ptr<GameMap>> _maps;
  std::shared_ptr<TCODRandom> _rng;
  std::unique_ptr<UpkeepManager> _upkeep;
  std::unique_ptr<Factory> _factory;
  std::map<int, std::shared_ptr<Entity>> _things;
  int _turn, _playerID;
};
