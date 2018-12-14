#pragma once

struct Tile {
  char glyph;
  bool walk, see;
  TCODColor* color;
};

enum SetTile {
  SET_NULL_TILE = 0,
  SET_FLOOR,
  SET_WALL,
  SET_DOOR_CLOSED,
  SET_DOOR_OPEN,
  SET_STAIRS_DOWN,
  SET_STAIRS_UP,
};
extern const Tile FLOOR;
extern const Tile WALL;
extern const Tile DOOR_CLOSED;
extern const Tile DOOR_OPEN;
extern const Tile STAIRS_UP;
extern const Tile STAIRS_DOWN;
extern const Tile NULL_TILE;