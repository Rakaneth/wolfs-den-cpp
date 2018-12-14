#include "main.hpp"

World::World(uint32_t seed)
  : _rng(new TCODRandom(seed)),
    _upkeep(new UpkeepManager()),
    _factory(new Factory()),
    _turn(0) {
  _factory->init();
}

World::World()
  : _rng(std::make_unique<TCODRandom>()),
    _upkeep(std::make_unique<UpkeepManager>()),
    _factory(new Factory()),
    _turn(0) {
  _factory->init();
}

void World::addMap(std::string mapID, GameMap* map) {
  std::unique_ptr<GameMap> temp(map);
  _maps.insert({mapID, std::move(temp)});
}

