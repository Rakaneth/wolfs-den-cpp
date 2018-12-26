#include "main.hpp"

BaseRoom::BaseRoom(int x, int y, int w, int h)
  : _x1(x), _y1(y), _w(w), _h(h), _x2(x + w - 1), _y2(y + h - 1) {}

Pos BaseRoom::center() { return Pos{(_x1 + _x2) / 2, (_y1 + _y2) / 2}; }

RectDirection BaseRoom::getDirection(int x, int y) {
  if ((x == _x1 || x == _x2) && (y == _y1 || y == _y2))
    return RECT_CORNER;
  else if (x == _x1)
    return RECT_WEST;
  else if (x == _x2)
    return RECT_EAST;
  else if (y == _y1)
    return RECT_NORTH;
  else if (y == _y2)
    return RECT_SOUTH;
  else if (x < _x1 || x > _x2 || y < _y1 || y > _y2)
    return RECT_EXTERIOR;
  else
    return RECT_INTERIOR;
}

PosList BaseRoom::border() {
  PosList results;
  for (int x = _x1; x <= _x2; x++) {
    results.emplace_back(x, _y1);
    results.emplace_back(x, _y2);
  }

  for (int y = _y1 + 1; y <= _y2 - 1; y++) {
    results.emplace_back(_x1, y);
    results.emplace_back(_x2, y);
  }
  return results;
}

PosList BaseRoom::interior() {
  PosList results;
  for (int x = _x1 + 1; x < _x2; x++)
    for (int y = _y1 + 1; y < _y2; y++) 
      results.push_back(Pos{x, y});
  return results;
}

bool BaseRoom::intersect(const BaseRoom& other) {
  if (_x2 < other._x1 || _x1 > other._x2)
    return false;
  if (_y2 < other._y1 || _y1 > other._y2)
    return false;

  return true;
}

void Room::carve(GameMap& map) {
  for (auto& p : interior())
    map.setTile(p, SET_FLOOR);
}