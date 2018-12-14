#include "main.hpp"

GameMap::GameMap(int width, int height, std::string name,
                 std::shared_ptr<TCODRandom> rng, bool isLight)
  : _width(width),
    _height(height),
    isLight(isLight),
    _name(name),
    _tiles(std::vector<int>(width * height, 0)),
    _explored(std::vector<bool>(width * height, false)),
    _fovMap(new TCODMap(width, height)),
    _rng(rng) {}

bool GameMap::inBounds(int x, int y) const {
  return between(x, 0, _width - 1) && between(y, 0, _height - 1);
}

Tile GameMap::getTile(int x, int y) const {
  static const Tile _table[] = {NULL_TILE, FLOOR,       WALL,     DOOR_CLOSED,
                                DOOR_OPEN, STAIRS_DOWN, STAIRS_UP};
  if (inBounds(x, y))
    return _table[_tiles[x + y * _width]];
  else
    return NULL_TILE;
}

void GameMap::setTile(int x, int y, int tileIdx) {
  _tiles[x + y * _width] = tileIdx;
  Tile t = getTile(x, y);
  _fovMap->setProperties(x, y, t.see, t.walk);
  dirty = true;
}

bool GameMap::isExplored(int x, int y) const {
  return _explored[x + y * _width];
}

void GameMap::explore(int x, int y) { _explored[x + y * _width] = true; }

GameMap& GameMap::allWalls() {
  for (int x = 0; x < _width; x++)
    for (int y = 0; y < _height; y++)
      setTile(x, y, SET_WALL);
  return *this;
}

GameMap& GameMap::allFloors() {
  for (int x = 0; x < _width; x++)
    for (int y = 0; y < _height; y++)
      setTile(x, y, SET_FLOOR);
  return *this;
}

GameMap& GameMap::randomTiles(double chance) {
  double roll;
  for (int x = 0; x < _width; x++) {
    for (int y = 0; y < _height; y++) {
      roll = _rng.lock()->getDouble(0.0, 1.0);
      if (roll < chance)
        setTile(x, y, SET_WALL);
      else
        setTile(x, y, SET_FLOOR);
    }
  }
  return *this;
}

GameMap& GameMap::wallWrap() {
  for (int x = 0; x < _width; x++) {
    setTile(x, 0, SET_WALL);
    setTile(x, _height - 1, SET_WALL);
  }

  for (int y = 1; y < _height - 2; y++) {
    setTile(0, y, SET_WALL);
    setTile(_width - 1, y, SET_WALL);
  }
  return *this;
}

GameMap* GameMap::makeCaves(int width, int height, std::string name,
                            std::shared_ptr<TCODRandom>& rng, bool isLight) {
  auto map = new GameMap(width, height, name, rng, isLight);
  map->randomTiles().wallWrap();
  return map;
}
