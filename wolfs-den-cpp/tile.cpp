#include "main.hpp"

extern const Tile FLOOR = Tile{ ' ', true, true, nullptr};
extern const Tile WALL = Tile{ (char)178, false, false, nullptr };
extern const Tile DOOR_CLOSED = Tile{ '+', false, false, new TCODColor(63,50,31) };
extern const Tile DOOR_OPEN = Tile{ '/', true, true, new TCODColor(63, 50, 31) };
extern const Tile STAIRS_UP = Tile{ '<', true, true, new TCODColor(255, 255, 115) };
extern const Tile STAIRS_DOWN = Tile{ '>', true, true, new TCODColor(255, 255, 115) };
extern const Tile NULL_TILE = Tile{ 0, false, false, nullptr };