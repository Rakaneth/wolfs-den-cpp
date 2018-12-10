#pragma once

class Screen {
public:
	Screen(std::string name);
	virtual ~Screen();
	virtual void render() = 0;
	virtual void handleKeys(const TCOD_key_t& key, bool shift) = 0;
	virtual void enter();
	virtual void exit();
	std::string getName() const;
protected:
	std::string _name;
};

class MainScreen : public Screen {
public:
	MainScreen();
	MainScreen(const MainScreen& oldScreen);
	MainScreen& operator=(const MainScreen& screen);
	~MainScreen();
	void render();
	void handleKeys(const TCOD_key_t& key, bool shift);
private:
	TCODConsole* _map;
	TCODConsole* _msgs;
	TCODConsole* _skls;
	TCODConsole* _info;
	TCODConsole* _stats;
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