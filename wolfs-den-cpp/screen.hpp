#pragma once

class Screen {
public:
	Screen(std::string name, World& world);
	virtual ~Screen();
	virtual void render() = 0;
	virtual void handleKeys(const TCOD_key_t& key, bool shift) = 0;
	virtual void enter();
	virtual void exit();
	std::string getName() const;
	static void border(TCODConsole& cons, std::string caption="");
protected:
	std::string _name;
	World& _world;
};

class MainScreen : public Screen {
public:
	MainScreen(World& world);
	MainScreen(const MainScreen& oldScreen) = delete;
	MainScreen& operator=(const MainScreen& screen) = delete;
	~MainScreen();
	void render();
	void handleKeys(const TCOD_key_t& key, bool shift);
private:
	void drawMap();
	void drawHUD();
	Pos cam(const Pos& pos);
	TCODConsole* _map;
	TCODConsole* _msgs;
	TCODConsole* _skls;
	TCODConsole* _info;
	TCODConsole* _stats;
	bool _gameStarted;
	//void startGame();
};

class ScreenManager {
public:
	ScreenManager();
	~ScreenManager();
	void registerScreen(Screen* screens);
	void setScreen(std::string screenID);
	Screen& getCurScreen();
private:
	Screen* _curScreen;
	std::map<std::string, Screen*> _screenMap;
};