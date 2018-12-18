#pragma once
class Entity;

class GameMap {
public:
  GameMap(int width, int height, std::string name,
          std::shared_ptr<TCODRandom> rng, TCODColor wallBG = TCODColor::grey,
          TCODColor floorBG = TCODColor::grey, bool isLight = true);
  GameMap() = delete;
  bool isLight, dirty;
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
  static GameMap* makeCaves(int width, int height, std::string name,
                            std::shared_ptr<TCODRandom>& rng,
                            bool isLight = true);
  bool canWalk(int x, int y) { return getTile(x, y).walk; }
  bool canWalk(Pos p) { return canWalk(p.x, p.y); }
  bool canSee(int x, int y) { return getTile(x, y).see; }
  bool canSee(Pos p) { return canSee(p.x, p.y); }
  Pos randomFloor();
  TCODColor wallBG, floorBG;

private:
  GameMap& allWalls();
  GameMap& allFloors();
  GameMap& wallWrap();
  GameMap& randomTiles(double chance = 0.5);
  std::vector<int> _tiles;
  std::vector<bool> _explored;
  PosList _floors;
  std::string _name;
  int _width;
  int _height;
  std::unique_ptr<TCODMap> _fovMap;
  std::weak_ptr<TCODRandom> _rng;
  
};
