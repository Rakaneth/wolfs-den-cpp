#pragma once

enum RectDirection {
  RECT_NORTH,
  RECT_SOUTH,
  RECT_EAST,
  RECT_WEST,
  RECT_INTERIOR,
  RECT_EXTERIOR,
  RECT_CORNER
};

class Room {
public:
  Room() = default;
  Room(int x, int y, int w, int h);
  Pos center();
  Pos pos() { return Pos(_x1, _y1); }
  int getWidth() const { return _w; }
  int getHeight() const { return _h; }
  RectDirection getDirection(int x, int y);
  RectDirection getDirection(Pos& p) { return getDirection(p.x, p.y); }

  PosList border();
  PosList interior();
  bool intersect(const Room& other);

private:
  int _x1, _y1, _x2, _y2, _w, _h;
};


