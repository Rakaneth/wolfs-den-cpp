#include "main.hpp"

GameMap::GameMap(int width, int height, std::string name,
                 std::shared_ptr<TCODRandom> rng, TCODColor wallBG,
                 TCODColor floorBG, bool isLight)
  : _width(width),
    _height(height),
    isLight(isLight),
    _name(name),
    _tiles(std::vector<int>(width * height, 0)),
    _explored(std::vector<bool>(width * height, false)),
    _fovMap(new TCODMap(width, height)),
    _rng(rng),
    wallBG(wallBG),
    floorBG(floorBG) {
  for (int x = 0; x < _width; x++)
    for (int y = 0; y < _height; y++)
      _allPositions.emplace_back(x, y);
}

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
  Pos changedTile = Pos(x, y);
  if (t.walk)
    _floors.push_back(changedTile);
  else
    listRemove(_floors, changedTile);
  dirty = true;
}

bool GameMap::isExplored(int x, int y) const {
  return _explored[x + y * _width];
}

void GameMap::explore(int x, int y) { _explored[x + y * _width] = true; }

GameMap& GameMap::allWalls() {
  std::cout << "Making all walls for " << _name << std::endl;
  for (int x = 0; x < _width; x++)
    for (int y = 0; y < _height; y++)
      setTile(x, y, SET_WALL);
  return *this;
}

GameMap& GameMap::allFloors() {
  std::cout << "Making all floors for " << _name << std::endl;
  for (int x = 0; x < _width; x++)
    for (int y = 0; y < _height; y++)
      setTile(x, y, SET_FLOOR);
  return *this;
}

GameMap& GameMap::randomTiles(double chance) {
  std::cout << "Generating random tiles in " << _name << std::endl;
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
  std::cout << "Wall wrapping " << _name << std::endl;
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

GameMap& GameMap::caveIterations(int times) {
  PosList toWall, toFloor, neis;
  for (int i = 0; i < times; i++) {
    std::cout << "Smoothing caves in " << _name << "; iteration " << i + 1
              << std::endl;
    toWall.clear();
    toFloor.clear();
    for (int x = 0; x < _width; x++) {
      for (int y = 0; y < _height; y++) {
        neis = neighbors(x, y, false);
        int numWalls = std::count_if(neis.begin(), neis.end(),
                                     [&](Pos p) { return !canWalk(p); });
        if (numWalls >= 5)
          toWall.emplace_back(x, y);
        else if (numWalls < 4)
          toFloor.emplace_back(x, y);
      }
    }
    for (auto& wall : toWall)
      setTile(wall, SET_WALL);

    for (auto& floor : toFloor)
      setTile(floor, SET_FLOOR);
  }

  return *this;
}

GameMap& GameMap::makeRooms(int maxRooms, int minRoomDim, int maxRoomDim) {
  std::vector<Room> rooms;
  auto rng = _rng.lock();
  bool add;
  for (int i = 0; i < maxRooms; i++) {
    add = true;
    int x = rng->getInt(1, _width-1);
    int y = rng->getInt(1, _height-1);
    int w = rng->getInt(minRoomDim, maxRoomDim);
    int h = rng->getInt(minRoomDim, maxRoomDim);
    Room r(x, y, w, h);
    if (rooms.size() == 0 && !isRoomFor(r))
      add = false;
    else {
      for (auto& rm : rooms) {
        if (!isRoomFor(r) || r.intersect(rm)) {
          add = false;
          break;
        }
      }
    }
    if (add) {
      rooms.push_back(r);
      r.carve(*this);
    }
  }
  return *this;
}

GameMap* GameMap::makeCaves(int width, int height, std::string name,
                            std::shared_ptr<TCODRandom>& rng, bool isLight) {
  auto map = new GameMap(width, height, name, rng, TCODColor::darkestSepia,
                         TCODColor::darkerSepia, isLight);
  map->randomTiles().caveIterations(4).wallWrap();
  std::cout << "Removing small regions in " << map->getName() << std::endl;
  static const int MIN_REGION_SIZE = 50;
  auto regions = map->findRegions();
  for (auto& region : regions)
    if (region.size() < MIN_REGION_SIZE)
      for (auto& tile : region)
        map->setTile(tile, SET_WALL);

  std::cout << "Connecting remaining regions in " << map->getName()
            << std::endl;
  regions = map->findRegions();
  map->connectRegions(regions);
  return map;
}

GameMap* GameMap::makeUniform(int width, int height, std::string name,
                              std::shared_ptr<TCODRandom>& rng, bool isLight) {
  auto map = new GameMap(width, height, name, rng, TCODColor::grey,
                         TCODColor::darkGrey, isLight);
  map->allWalls().makeRooms(20);
  auto regions = map->findRegions();
  map->connectRegions(regions, true).wallWrap();
  return map;
}

Pos GameMap::randomFloor() {
  auto roll = _rng.lock()->getInt(0, _floors.size()-1);
  return _floors[roll];
}

Pos GameMap::randomFloor(Pos p, int radius) {
  PosList cands;
  std::copy_if(_floors.begin(), _floors.end(), std::back_inserter(cands),
               [&](Pos pt) { return distance(pt, p) <= radius && pt != p; });
  return listRandom(cands, getRNG());
}

PosList GameMap::neighbors(int x, int y, bool skipWalls) {
  PosList results;
  int xmin = std::max(0, x - 1);
  int xmax = std::min(_width - 1, x + 1);
  int ymin = std::max(0, y - 1);
  int ymax = std::min(_height - 1, y + 1);
  bool wall, self;
  for (int xs = xmin; xs <= xmax; xs++) {
    for (int ys = ymin; ys <= ymax; ys++) {
      wall = !canWalk(xs, ys) && skipWalls;
      self = (xs == x && ys == y);
      if (!(wall || self))
        results.emplace_back(xs, ys);
    }
  }
  return results;
}

std::vector<PosList> GameMap::findRegions() {
  std::cout << "Finding regions in " << _name << std::endl;
  std::vector<PosList> regions;
  std::map<int, int> regionMap;
  Pos curPos{0, 0};
  int counter = 0;
  for (int x = 0; x < _width; x++) {
    for (int y = 0; y < _height; y++) {
      if (canWalk(x, y)) {
        curPos = Pos{x, y};
        if (regionMap.count(toIndex(curPos, _width)) == 1)
          continue;
        else
          regions.push_back(flood(curPos, regionMap, counter++));
      }
    }
  }
  return regions;
}

PosList GameMap::flood(Pos p, std::map<int, int>& regionMap, int idx) {
  std::cout << "Flooding " << p << std::endl;
  std::queue<Pos> q;
  PosList results;
  Pos current = p;
  q.push(p);
  if (canWalk(p))
    results.push_back(p);
  while (!q.empty()) {
    current = q.front();
    q.pop();
    for (auto& nei : neighbors(current)) {
      if (contains(results, nei))
        continue;
      else {
        q.push(nei);
        regionMap[toIndex(nei, _width)] = idx;
        results.push_back(nei);
      }
    }
  }
  return results;
}

bool GameMap::isClosedDoor(int x, int y) {
  return _tiles[x + y * _width] == SET_DOOR_CLOSED;
}

bool GameMap::isOpenDoor(int x, int y) {
  return _tiles[x + y * _width] == SET_DOOR_OPEN;
}

bool GameMap::isRoomFor(BaseRoom& rect) {
  Pos rectPos = rect.pos();
  bool inside = inBounds(rectPos);
  bool xRoom = rect.getWidth() + rectPos.x < _width;
  bool yRoom = rect.getHeight() + rectPos.y < _height;
  return inside && xRoom && yRoom;
}

GameMap& GameMap::connectRegions(std::vector<PosList>& regions, bool doors) {
  if (regions.size() > 1) {
    Pos ptA, ptB;
    int px, py;
    TCODPath path(_width, _height, new CaveCallback(), this, 0.0f);
    for (int i = 1; i < regions.size(); i++) {
      ptA = listRandom(regions[i - 1], getRNG());
      ptB = listRandom(regions[i], getRNG());
      if (path.compute(ptA.x, ptA.y, ptB.x, ptB.y)) {
        while (!path.isEmpty()) {
          if (path.walk(&px, &py, true))
            setTile(px, py, SET_FLOOR);
        }
      }
    }
  }
  return *this;
}

float CaveCallback::getWalkCost(int xFrom, int yFrom, int xTo, int yTo,
                                void* userData) const {
  auto pMap = (GameMap*)userData;
  if (pMap->canWalk(xTo, yTo))
    return 10.0f;
  else if (xTo == 0 || yTo == 0 || xTo == pMap->getWidth() - 1 ||
           yTo == pMap->getHeight() - 1)
    return 0.0f;
  else
    return 1.0f;
}