#include "main.hpp"

Message Message::newMessage(std::string text,
                            std::initializer_list<TCODColor> clrs) {

  Message m;
  m.text = "-" + text;
  for (auto color : clrs)
    m.colors.push_back(color);
  return m;
}

int Message::getHeight(TCODConsole& cons, int y, int width) const {
  return cons.getHeightRect(1, y, width, 0, text.c_str());
}

int Message::print(TCODConsole& cons, int y, int width) {
  int s = colors.size();
  const char* msg = text.c_str();
  for (int i = 1; 1 <= 5; i++) {
    if (s >= i)
      TCODConsole::setColorControl((TCOD_colctrl_t)i, colors[i - 1],
                                   TCODColor::black);
    else
      break;
  }
  switch (s) {
  case 1:
    return cons.printRect(1, y, width, 0, msg, TCOD_COLCTRL_1,
                          TCOD_COLCTRL_STOP);
  case 2:
    return cons.printRect(1, y, width, 0, msg, TCOD_COLCTRL_1,
                          TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
  case 3:
    return cons.printRect(1, y, width, 0, msg, TCOD_COLCTRL_1,
                          TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP,
                          TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
  case 4:
    return cons.printRect(1, y, width, 0, msg, TCOD_COLCTRL_1,
                          TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP,
                          TCOD_COLCTRL_3, TCOD_COLCTRL_STOP, TCOD_COLCTRL_4,
                          TCOD_COLCTRL_STOP);
  case 5:
    return cons.printRect(1, y, width, 0, msg, TCOD_COLCTRL_1,
                          TCOD_COLCTRL_STOP, TCOD_COLCTRL_2, TCOD_COLCTRL_STOP,
                          TCOD_COLCTRL_3, TCOD_COLCTRL_STOP, TCOD_COLCTRL_4,
                          TCOD_COLCTRL_STOP, TCOD_COLCTRL_5, TCOD_COLCTRL_STOP);
  default:
    return cons.printRect(1, y, width, 0, msg);
  }
}

World::World(uint32_t seed)
  : _rng(new TCODRandom(seed)),
    _upkeep(new UpkeepManager()),
    _factory(new Factory()),
    _turn(0) {
  _factory->init();
}

World::World()
  : _rng(new TCODRandom()),
    _upkeep(std::make_unique<UpkeepManager>()),
    _factory(new Factory()),
    _turn(0) {
  _factory->init();
}

void World::addMap(std::string mapID, GameMap* map) {
  std::unique_ptr<GameMap> temp(map);
  _maps.insert({mapID, std::move(temp)});
}

int World::addEntity(std::shared_ptr<Entity> ent) {
  int retVal = ent->ID();
  _upkeep->add(ent);
  _things.insert({ent->ID(), ent});
  return retVal;
}

void World::removeEntity(int entID) { _things.erase(entID); }

void World::changeMap(std::string newMapID) {
  _curMapID = newMapID;
  for (auto& pair : _things)
    pair.second->upkeep = (pair.second->mapID == newMapID);
}

std::vector<Entity> World::curThings() {
  std::vector<Entity> results;
  for (auto& pair : _things)
    if (pair.second->upkeep)
      results.push_back(*pair.second);
  return results;
}

void World::setPlayer(int eID) {
  _playerID = eID;
  getPlayer().isPlayer = true;
}

void World::addMessage(Message msg) {
  _messages.push_back(msg);
  msgDirty = true;
}