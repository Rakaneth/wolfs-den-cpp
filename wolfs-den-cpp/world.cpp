#include "main.hpp"

World::World(uint32_t seed)
  : _rng(new TCODRandom(seed)),
    _upkeep(new UpkeepManager()),
    _factory(new Factory()),
    _turn(0) {
  _factory->init();
}

World::World()
  : _rng(new TCODRandom()),
    _upkeep(std::make_unique<UpkeepManager>()),
    _factory(new Factory()),
    _turn(0) {
  _factory->init();
}

void World::addMap(std::string mapID, GameMap* map) {
  std::unique_ptr<GameMap> temp(map);
  _maps.insert({mapID, std::move(temp)});
}

int World::addEntity(std::shared_ptr<Entity> ent) {
  int retVal = ent->ID();
  _upkeep->add(ent);
  _things.insert({ent->ID(), ent});
  return retVal;
}

void World::removeEntity(int entID) { _things.erase(entID); }

void World::changeMap(std::string newMapID) { 
  _curMapID = newMapID;
  for (auto& pair : _things)
      pair.second->upkeep = (pair.second->mapID == newMapID);
}

std::vector<Entity> World::curThings() { 
  std::vector<Entity> results; 
  for (auto& pair : _things)
    if (pair.second->upkeep)
      results.push_back(*pair.second);
  return results;
}