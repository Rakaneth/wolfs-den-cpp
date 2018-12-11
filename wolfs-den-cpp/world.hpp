#pragma once

class World {
public:
	World(uint32_t seed);
	World();
	TCODRandom getRNG() const { return *_rng; }
	GameMap& getMap(std::string mapID) { return _maps[mapID]; }
	void addMap(std::string mapID, GameMap map) { _maps[mapID] = map; }
	//void changeMap(std::string mapID);
	GameMap& getCurMap() { return getMap(curMapID); }
	std::string curMapID;
	Pos player; //TODO: entity
private:
	std::map<std::string, GameMap> _maps;
	std::unique_ptr<TCODRandom> _rng;
};
