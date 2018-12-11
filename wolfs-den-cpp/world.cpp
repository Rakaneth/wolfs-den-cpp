#include "main.hpp"

World::World(uint32_t seed) {
	_rng = TCODRandom(seed);
}

World::World() {
	_rng = TCODRandom();
}