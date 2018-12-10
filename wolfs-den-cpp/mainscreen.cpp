#include "main.hpp"

MainScreen::MainScreen() : Screen("main") {
	_map = new TCODConsole(100, 100);
	_msgs = new TCODConsole(MSG_W, MSG_H);
	_skls = new TCODConsole(SKL_W, SKL_H);
	_info = new TCODConsole(INFO_W, INFO_H);
	_stats = new TCODConsole(STAT_W, STAT_H);
}

MainScreen::MainScreen(const MainScreen& oldScreen): Screen(oldScreen) {
	*_map = *oldScreen._map;
	*_msgs = *oldScreen._msgs;
	*_skls = *oldScreen._skls;
	*_info = *oldScreen._info;
	*_stats = *oldScreen._stats;
}

MainScreen& MainScreen::operator=(const MainScreen& screen) {
	if (this == &screen)
		return *this;
	
	_map = screen._map;
	_msgs = screen._msgs;
	_skls = screen._skls;
	_info = screen._info;
	_stats = screen._stats;
	return *this;
}

MainScreen::~MainScreen() {
	delete _map;
	delete _msgs;
	delete _skls;
	delete _info;
	delete _stats;
}

void MainScreen::render() {
	border(*_msgs, "Messages");
	border(*_skls, "Skills");
	border(*_info, "Info");
	border(*_stats, "Stats");

	TCODConsole::blit(_map, 0, 0, MAP_W, MAP_H, TCODConsole::root, 0, 0);
	TCODConsole::blit(_msgs, 0, 0, _msgs->getWidth(), _msgs->getHeight(), TCODConsole::root, MSG_X, MSG_Y);
	TCODConsole::blit(_info, 0, 0, _info->getWidth(), _info->getHeight(), TCODConsole::root, INFO_X, INFO_Y);
	TCODConsole::blit(_skls, 0, 0, _skls->getWidth(), _skls->getHeight(), TCODConsole::root, SKL_X, SKL_Y);
	TCODConsole::blit(_stats, 0, 0, _stats->getWidth(), _stats->getHeight(), TCODConsole::root, STAT_X, STAT_Y);
}

void MainScreen::handleKeys(const TCOD_key_t& key, bool shift) {
	std::cout << "Key " << key.text << " was pressed";
	if (shift)
		std::cout << " and shift was down." << std::endl;
	else
		std::cout << "." << std::endl;
}