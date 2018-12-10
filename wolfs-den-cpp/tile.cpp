#include "main.hpp"

const Tile FLOOR = Tile{ '.', true, true, nullptr};
const Tile WALL = Tile{ '#', false, false, nullptr };
const Tile DOOR_CLOSED = Tile{ '+', false, false, new TCODColor(63,50,31) };
const Tile DOOR_OPEN = Tile{ '/', true, true, new TCODColor(63, 50, 31) };
const Tile STAIRS_UP = Tile{ '<', true, true, new TCODColor(255, 255, 115) };
const Tile STAIRS_DOWN = Tile{ '>', true, true, new TCODColor(255, 255, 115) };

