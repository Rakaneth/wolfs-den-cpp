#include "main.hpp"

MainScreen::MainScreen(World& world) : Screen("main", world) {
	_map = new TCODConsole(MAP_MAX_W, MAP_MAX_H);
	_msgs = new TCODConsole(MSG_W, MSG_H);
	_skls = new TCODConsole(SKL_W, SKL_H);
	_info = new TCODConsole(INFO_W, INFO_H);
	_stats = new TCODConsole(STAT_W, STAT_H);
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

	drawMap();
	drawHUD();

	auto c = cam(_world.player);

	TCODConsole::blit(_map, c.x, c.y, MAP_W, MAP_H, TCODConsole::root, 0, 0);
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

void MainScreen::drawMap() {
	auto m = _world.getCurMap();
	for (int x = 0; x < m.getWidth(); x++) {
		for (int y = 0; y < m.getHeight(); y++) {
			Tile t = m.getTile(x, y);
			if (t.glyph != 0) {
				TCODColor color = (t.color == nullptr) ? TCODColor::white : *t.color;
				_map->putCharEx(x, y, t.glyph, color, TCODColor::black);
			}
		}
	}
}

void MainScreen::drawHUD() {
	//TODO: HUD
}

Pos MainScreen::cam(const Pos& pos) {
	auto m = _world.getCurMap();
	int left = clamp(pos.x - m.getWidth(), 0, (int)fmax(0, m.getWidth() - MAP_W));
	int top = clamp(pos.y - m.getHeight(), 0, (int)fmax(0, m.getHeight() - MAP_H));
	return Pos{ left, top };
}