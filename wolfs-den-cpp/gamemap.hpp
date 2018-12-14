#pragma once
class Entity;

class GameMap {
public:
  GameMap(int width, int height, std::string name, bool isLight = true);
  GameMap() = delete;
  bool isLight;
  std::string getName() const { return _name; }
  int getWidth() const { return _width; }
  int getHeight() const { return _height; }
  bool inBounds(int x, int y) const;
  bool inBounds(const Pos& pos) const { return inBounds(pos.x, pos.y); }
  Tile getTile(int x, int y) const;
  Tile getTile(const Pos& pos) const { return getTile(pos.x, pos.y); }
  void setTile(int x, int y, int tileIdx);
  void setTile(const Pos& pos, int tileIdx) { setTile(pos.x, pos.y, tileIdx); }
  bool isExplored(int x, int y) const;
  bool isExplored(const Pos& pos) const { return isExplored(pos.x, pos.y); }
  void explore(int x, int y);
  void explore(const Pos& pos) { explore(pos.x, pos.y); }

private:
  std::vector<int> _tiles;
  std::vector<bool> _explored;
  std::string _name;
  int _width;
  int _height;
  std::unique_ptr<TCODMap> _fovMap;
};
