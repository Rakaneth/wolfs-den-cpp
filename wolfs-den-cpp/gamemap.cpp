#include "main.hpp"

GameMap::GameMap(int width, int height, std::string name, bool isLight)
	: _width(width), _height(height), isLight(isLight), _name(name) {
	_tiles = std::vector<int>(width * height, 0);
	_explored = std::vector<bool>(width * height, false);
}

bool GameMap::inBounds(int x, int y) const {
	return between(x, 0, _width - 1) && between(y, 0, _height - 1);
}

Tile GameMap::getTile(int x, int y) const {
	static Tile table[]{ FLOOR, WALL, DOOR_CLOSED, DOOR_OPEN,
	STAIRS_DOWN, STAIRS_UP, NULL_TILE };

	if (inBounds(x, y))
		return table[_tiles[x + y * _width]];
	else
		return NULL_TILE;
}

void GameMap::setTile(int x, int y, int tileIdx) {
	_tiles[x + y * _width] = tileIdx;
}

bool GameMap::isExplored(int x, int y) const {
	return _explored[x + y * _width];
}

void GameMap::explore(int x, int y) {
	_explored[x + y * _width] = true;
}
