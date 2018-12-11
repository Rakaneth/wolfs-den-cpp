#pragma once

struct Tile {
	char glyph;
	bool walk, see;
	TCODColor* color;
};
extern const Tile FLOOR;
extern const Tile WALL;
extern const Tile DOOR_CLOSED;
extern const Tile DOOR_OPEN;
extern const Tile STAIRS_UP;
extern const Tile STAIRS_DOWN;
extern const Tile NULL_TILE;