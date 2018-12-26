#include "main.hpp"

Room::Room(int x, int y, int w, int h)
  : _x1(x), _y1(y), _w(w), _h(h), _x2(x + w - 1), _y2(y + h - 1) {}

Pos Room::center() { return Pos{(_x1 + _x2) / 2, (_y1 + _y2) / 2}; }

RectDirection Room::getDirection(int x, int y) {
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

PosList Room::border() {
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

PosList Room::interior() {
  PosList results;
  for (int x = _x1 + 1; x < _x2; x++)
    for (int y = _y2 + 1; y < _y2; y++)
      results.emplace_back(x, y);
  return results;
}

bool Room::intersect(const Room& other) {
  return !(_y2 < other._y1 || _x2 < other._x1);
}
