#pragma once
class GameMap;

enum RectDirection {
  RECT_NORTH,
  RECT_SOUTH,
  RECT_EAST,
  RECT_WEST,
  RECT_INTERIOR,
  RECT_EXTERIOR,
  RECT_CORNER
};

class BaseRoom {
public:
  BaseRoom() = default;
  BaseRoom(int x, int y, int w, int h);
  Pos center();
  Pos pos() { return Pos(_x1, _y1); }
  int getWidth() const { return _w; }
  int getHeight() const { return _h; }
  RectDirection getDirection(int x, int y);
  RectDirection getDirection(Pos& p) { return getDirection(p.x, p.y); }
  virtual void carve(GameMap& map) = 0;

  PosList border();
  PosList interior();
  bool intersect(const BaseRoom& other);

private:
  int _x1, _y1, _x2, _y2, _w, _h;
};

class Room : public BaseRoom {
public:
  Room(int x, int y, int w, int h) : BaseRoom(x, y, w, h) {}
  void carve(GameMap& map) override;
};
