#include "main.hpp"

World::World(uint32_t seed)
  : _rng(std::make_unique<TCODRandom>(seed)),
    _upkeep(std::make_unique<UpkeepManager>()),
    _turn(0) {}

World::World()
  : _rng(std::make_unique<TCODRandom>()),
    _upkeep(std::make_unique<UpkeepManager>()),
    _turn(0) {}