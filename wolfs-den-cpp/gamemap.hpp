#pragma once
class Entity;

class GameMap {
public:
  GameMap() = delete;
  GameMap(int width, int height, std::string name,
          std::shared_ptr<TCODRandom> rng, TCODColor wallBG = TCODColor::grey,
          TCODColor floorBG = TCODColor::grey, bool isLight = true);

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
  static GameMap* makeUniform(int width, int hieght, std::string name,
                              std::shared_ptr<TCODRandom>& rng,
                              bool isLight = true);
  bool canWalk(int x, int y) { return getTile(x, y).walk; }
  bool canWalk(Pos p) { return canWalk(p.x, p.y); }
  bool canSee(int x, int y) { return getTile(x, y).see; }
  bool canSee(Pos p) { return canSee(p.x, p.y); }
  bool isClosedDoor(int x, int y);
  bool isClosedDoor(const Pos& p) { return isClosedDoor(p.x, p.y); }
  bool isOpenDoor(int x, int y);
  bool isOpenDoor(const Pos& p) { return isOpenDoor(p.x, p.y);  }
  PosList neighbors(int x, int y, bool skipWalls =true);
  PosList neighbors(Pos p, bool skipWalls = true) {
    return neighbors(p.x, p.y, skipWalls);
  }
  Pos randomFloor();
  Pos randomFloor(Pos p, int radius);
  TCODColor wallBG, floorBG;
  TCODRandom& getRNG() { return *_rng.lock(); }

private:
  GameMap& allWalls();
  GameMap& allFloors();
  GameMap& wallWrap();
  GameMap& randomTiles(double chance = 0.5);
  GameMap& caveIterations(int times);
  GameMap& makeRooms(int maxRooms, int minRoomDim = 5, int maxRoomDim = 20);
  GameMap& connectRegions(std::vector<PosList>& regions, bool doors = false);
  std::vector<PosList> findRegions();
  PosList getFrontier(PosList& region);
  bool isFrontier(Pos& p);
  bool isRoomFor(BaseRoom& rect);
  PosList flood(Pos p, std::map<int, int>& regionMap, int idx);
  std::vector<int> _tiles;
  std::vector<bool> _explored;
  PosList _floors;
  std::string _name;
  int _width;
  int _height;
  std::unique_ptr<TCODMap> _fovMap;
  std::weak_ptr<TCODRandom> _rng;
  PosList _allPositions;
};

class CaveCallback : public ITCODPathCallback {
public:
  virtual float getWalkCost(int xFrom, int yFrom, int xTo, int yTo,
                            void* userData) const override;
};
