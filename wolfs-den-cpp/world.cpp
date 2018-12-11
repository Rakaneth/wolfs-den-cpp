#include "main.hpp"

World::World(uint32_t seed) {
	_rng = std::make_unique<TCODRandom>(seed);
}

World::World() {
	_rng = std::make_unique<TCODRandom>();
}