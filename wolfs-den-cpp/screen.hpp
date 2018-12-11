#pragma once

class Screen {
public:
	Screen(std::string name, std::shared_ptr<World> world);
	virtual ~Screen();
	virtual void render() = 0;
	virtual void handleKeys(const TCOD_key_t& key, bool shift) = 0;
	virtual void enter();
	virtual void exit();
	std::string getName() const;
	static void border(TCODConsole& cons, std::string caption="");
protected:
	std::string _name;
	std::shared_ptr<World> _world;
};

class MainScreen : public Screen {
public:
	MainScreen(std::shared_ptr<World> world);
	void render();
	void handleKeys(const TCOD_key_t& key, bool shift);
private:
	void drawMap();
	void drawHUD();
	Pos cam(const Pos& pos);
	std::unique_ptr<TCODConsole> _map;
	std::unique_ptr<TCODConsole> _msgs;
	std::unique_ptr<TCODConsole> _skls;
	std::unique_ptr<TCODConsole> _info;
	std::unique_ptr<TCODConsole> _stats;
	bool _gameStarted;
	//void startGame();
};

class ScreenManager {
public:
	ScreenManager();
	void registerScreen(std::shared_ptr<Screen> screen);
	void setScreen(std::string screenID);
	Screen& getCurScreen();
private:
	std::shared_ptr<Screen> _curScreen;
	std::map<std::string, std::shared_ptr<Screen>> _screenMap;
};