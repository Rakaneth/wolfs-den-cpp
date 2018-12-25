#pragma once
class Factory;
class Creature;

class Message {
public:
  static Message newMessage(std::string text,
                            std::initializer_list<TCODColor> clrs);
  std::string text;
  std::vector<TCODColor> colors;
  int getHeight(TCODConsole& cons, int y, int width) const;
  int print(TCODConsole& cons, int y, int width);
};

class World {
public:
  World(uint32_t seed);
  World();
  TCODRandom& getRNG() const { return *_rng; }
  std::shared_ptr<TCODRandom>& getRNGPtr() { return _rng; }
  GameMap& getMap(std::string mapID) { return *_maps[mapID]; }
  void addMap(std::string mapID, GameMap* map);
  GameMap& getCurMap() { return getMap(_curMapID); }
  Creature& getPlayer() { return *getByID<Creature>(_playerID); }
  void setPlayer(int eID);
  UpkeepManager& getUpkeepManager() const { return *_upkeep; }
  Factory& getFactory() const { return *_factory; }
  int getTurn() const { return _turn; }
  int addEntity(std::shared_ptr<Entity> ent);
  void removeEntity(int entID);
  void changeMap(std::string newMapID);
  std::vector<Entity> curThings();
  template <class T>
  std::shared_ptr<T> getByID(int eID) {
    return std::dynamic_pointer_cast<T>(_things[eID]);
  }
  void addMessage(Message msg);
  std::vector<Message>& getMessages() { return _messages; }
  bool msgDirty = true;
  bool hudDirty = true;
  std::vector<Entity> thingsAt(int x, int y);
  std::vector<Entity> thingsAt(Pos& pt) { return thingsAt(pt.x, pt.y); }

private:
  std::string _curMapID;
  std::map<std::string, std::unique_ptr<GameMap>> _maps;
  std::shared_ptr<TCODRandom> _rng;
  std::unique_ptr<UpkeepManager> _upkeep;
  std::unique_ptr<Factory> _factory;
  std::map<int, std::shared_ptr<Entity>> _things;
  std::vector<Message> _messages;
  int _turn, _playerID;
};
